/*
About the display: Your drawing utility was written by a “Friend”, prototype void draw(int x, int y);. 
draw() will erase the framebuffer, then draw a dot where you specify,
and block until the framebuffer with the dot is given to the display controller. 
The display panel is video mode, 60 Hz constant vsync (vsync interrupt is from the panel, back to the CPU).

Your touch controller is on an 400 KHz I2C bus, and has one interrupt pin coming back to the CPU. 
When the interrupt fires, you have an X and Y position locked into two 16-bit registers at address 0 and 2 in the controller,
and they won’t change until you read them. 

You have a “touch_i2c_read(UINT16 reg, UINT16* val); ” utility. 
The touch interrupt will fire as fast as 120-150 Hz range, the sampling rate of the touch controller is not fixed, 
and it will only clear the interrupts (and give new data) after you’ve read the previous x/y coordinates out.

Part 1) Implement the touch interrupt service routine, and the main task that will draw the dot.

Utilities provided to you:
void draw(int x, int y); blocking until subsequent vsync 
void touch_i2c_read(UINT16 *x, UINT16 *y);
(plus any timers, task creation, locking and signals you need.)
(plus, any initialization you need will happen in a separate thread.
Lock initialization, data structures created ahead of time, task creation, etc,
don't implement that and just assume it's done.)

Your functions to implement (minimally):
void touch_isr(void); // (edge triggerred interrupt service routine 
void draw_task(void); // infinite loop, main task, if you need it 
*/

/*
My notes:
I2C bus is 400KHz i.e. we can transmit 400,000 bits per second
For I2C we need following overhead bits:
8 clocks for 8 bits of each payload bite
1 clock for stop condition
2 clocks for start condition (worse case consideration, since we can have repeated start condition)
1 clock for ACK / NACK
8 clocks for 7 bit addressing mode, 7 bit address and 1 R/W bit
10 clocks for 0 bit addressing mode, 7 bit address and 1 R/W bit

So under 7 bit addressing mode, total overhead clocks are:
1 + 2 (start condition) + 1 + 8 = 12

So under 9 bit addressing mode, total overhead clocks are:
1 + 2 (start condition) + 1 + 10 = 14

We have no sampling, and our payload size is 16 bytes (X co-ordinates) + 16 bytes (Y co-ordinates) = 32 bytes

worse case number of clocks required (assuming 7 bit addressing scheme): 
    32 bytes * 8 bits per byte + 12 overhead clocks = 256 + 12 = 268 bits

worse case number of clocks required (assuming 9 bit addressing scheme): 
    32 bytes * 8 bits per byte + 12 overhead clocks = 256 + 14 = 270 bits

Our capability is 400,000 bits per second:
    so can send around: 400,000 / 268 = 1492 (x and y co-ordinates on I2C bus) / second
    so can send around: 400,000 / 270 = 1480 (x and y co-ordinates on I2C bus) / second

*/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

void touch_isr(void); // (edge triggerred interrupt service routine
extern void draw_task(void); // infinite loop, main task, if you need it
void draw(int x, int y); 
extern void touch_i2c_read(volatile uint16_t *reg, uint16_t* val);

#define BUFFER_SIZE 1500
#define EXIT_SUCCESS (0)
#define EXIT_FAILURE (1)
#define ISR_PORT ((volatile uint16_t *)0x100500)
#define TOUCH_ISR_FLAG *((volatile uint16_t *) 0x100)

sem_t empty, full;
// mutex for shared resource
pthread_mutex_t mutex;

static uint16_t co_ordinate_buffer[BUFFER_SIZE];
static uint16_t touch_co_ordinate_index = 0;
static uint16_t draw_co_ordinate_index = 0;

static bool touch_isr_flag = 0;

void touch_isr(void) {
    if(TOUCH_ISR_FLAG) {
        touch_isr_flag = 1;
        TOUCH_ISR_FLAG = 0x0;
    }
}

void *producer(void *args) {
    // wait for interrupt
    if(1 == touch_isr_flag) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        uint16_t val;
        touch_i2c_read(ISR_PORT, &val);
        co_ordinate_buffer[touch_co_ordinate_index++] = val;
        touch_i2c_read(ISR_PORT+2, &val);
        co_ordinate_buffer[touch_co_ordinate_index] = val;
        touch_co_ordinate_index = (touch_co_ordinate_index+1) % BUFFER_SIZE;
        touch_isr_flag = 0;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *args) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    uint16_t x_co_ordinate, y_co_ordinate;
    x_co_ordinate = co_ordinate_buffer[draw_co_ordinate_index++];
    y_co_ordinate = co_ordinate_buffer[draw_co_ordinate_index];
    draw_co_ordinate_index = (draw_co_ordinate_index+1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex);
    draw(x_co_ordinate, y_co_ordinate);
    sem_post(&empty);
}

int main(void) {
    memset(co_ordinate_buffer, 0, BUFFER_SIZE*sizeof(uint16_t));
    // init mutex
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);

    pthread_t thread_prod, thread_cons;
    int thread_id_prod = 0;
    pthread_create(&thread_prod, 0, producer, &thread_id_prod);

    int thread_id_cons = 0;
    pthread_create(&thread_cons, 0, producer, &thread_id_cons);

    pthread_join(thread_prod, NULL);
    pthread_join(thread_cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}



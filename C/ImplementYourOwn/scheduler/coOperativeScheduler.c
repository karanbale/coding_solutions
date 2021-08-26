#include "../../standardHeaders.h"

static unsigned int jiffies = 0;

#define TASK_WAITING 0
#define TASK_READY 1
#define TASK_RUNNING 2

#define TASK_NAME_MAXLEN 16

struct task_block {
    char name[TASK_NAME_MAXLEN];
    int id;
    int state;
    void (*start)(void *arg);
    void *arg;
    uint8_t *sp;
    uint32_t wakeup_time;
    struct task_block *next;
};

#define MAX_TASKS 8
static struct task_block TASKS[MAX_TASKS];
static int n_tasks = 1;
static int running_task_id = 0;
#define kernel TASKS[0]

/*
The core component of the scheduler consists of the exception handler associated with the system interrupt events, such as PendSV and SVCall.
On Cortex-M, a PendSV exception can be triggered at any time by the software, setting the PENDSET flag,
corresponding to bit 28 of the interrupt control and state register, located in the SCB at address 0xE000ED04
*/
#define SCB_ICSR (*((volatile uint32_t *)0xE000ED04))
#define schedule() SCB_ICSR |= (1 << 28)

static void __attribute__((naked)) store_context(void)
{
    asm volatile("mrs r0, msp");
    asm volatile("stmdb r0!, {r4-r11}");
    asm volatile("msr msp, r0");
    asm volatile("bx lr");
}

static void __attribute__((naked)) restore_context(void)
{
    asm volatile("mrs r0, msp");
    asm volatile("ldmfd r0!, {r4-r11}");
    asm volatile("msr msp, r0");
    asm volatile("bx lr");
}

void __attribute__((naked)) isr_pendsv(void)
{
    store_context();
    asm volatile("mrs %0, msp" : "=r"(TASKS[running_task_id].sp));
    TASKS[running_task_id].state = TASK_READY;
    running_task_id++;
    if (running_task_id >= n_tasks)
        running_task_id = 0;
    TASKS[running_task_id].state = TASK_RUNNING;
    asm volatile("msr msp, %0"::"r"(TASKS[running_task_id].sp));
    restore_context();
    asm volatile("mov lr, %0" ::"r"(0xFFFFFFF9));
    asm volatile("bx lr");
}

/*
In this example implementation, two threads are defined.
Both will turn on an LED and hold the CPU in a busy-loop for one second, then turn off the LED,
and explicitly call the schedule() function to trigger a context switch.
*/
void task_test0(void *arg)
{
    uint32_t now = jiffies;
    blue_led_on();
    while(1) {
        if ((jiffies - now) > 1000) {
            blue_led_off();
            schedule();
            now = jiffies;
            blue_led_on();
        }
    }
}

void task_test1(void *arg)
{
    uint32_t now = jiffies;
    red_led_on();
    while(1) {
        if ((jiffies - now) > 1000) {
            red_led_off();
            schedule();
            now = jiffies;
            red_led_on();
        }
    }
}



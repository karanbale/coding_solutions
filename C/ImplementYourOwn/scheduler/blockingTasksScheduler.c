#include "../../standardHeaders.h"

static unsigned int jiffies = 0;

#define TASK_TIMESLICE (20)

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

struct task_block *tasklist_active = NULL;
struct task_block *tasklist_waiting = NULL;

static void tasklist_add(struct task_block **list,struct task_block *el)
{
    el->next = *list;
    *list = el;
}

static int tasklist_del(struct task_block **list, struct task_block *delme)
{
    struct task_block *t = *list;
    struct task_block *p = NULL;
    while (t) {
        if (t == delme) {
            if (p == NULL)
                *list = t->next;
            else
                p->next = t->next;
            return 0;
        }
        p = t;
        t = t->next;
    }
    return -1;
}

static void task_waiting(struct task_block *t)
{
    if (tasklist_del(&tasklist_active, t) == 0) {
        tasklist_add(&tasklist_waiting, t);
        t->state = TASK_WAITING;
    }
}
static void task_ready(struct task_block *t)
{
    if (tasklist_del(&tasklist_waiting, t) == 0) {
        tasklist_add(&tasklist_active, t);
        t->state = TASK_READY;
    }
}

void sleep_ms(int ms)
{
    if (ms < TASK_TIMESLICE)
        return;
    t_cur->wakeup_time = jiffies + ms;
    task_waiting(t_cur);
    schedule();
}

void task_test0(void *arg)
{
    blue_led_on();
    while(1) {
        sleep_ms(500);
        blue_led_toggle();
    }
}

void task_test1(void *arg)
{
    red_led_on();
    while(1) {
        sleep_ms(125);
        red_led_toggle();
    }
}

static inline struct task_block *tasklist_next_ready(struct task_block *t)
{
    if ((t->next == NULL) || (t->next->state != TASK_READY))
        return tasklist_active;
    return t->next;
}

void __attribute__((naked)) isr_pendsv(void)
{
    store_context();
    asm volatile("mrs %0, msp" : "=r"(t_cur->sp));
    if (t_cur->state == TASK_RUNNING) {
        t_cur->state = TASK_READY;
    }
    t_cur = tasklist_next_ready(t_cur);
    t_cur->state = TASK_RUNNING;
    asm volatile("msr msp, %0" ::"r"(t_cur->sp));
    restore_context();
    asm volatile("mov lr, %0" ::"r"(0xFFFFFFF9));
    asm volatile("bx lr");
}

void main(void) {
    clock_pll_on(0);
    led_setup();
    button_setup();
    systick_enable();
    kernel.name[0] = 0;
    kernel.id = 0;
    kernel.state = TASK_RUNNING;
    kernel.wakeup_time = 0;
    tasklist_add(&tasklist_active, &kernel);
    task_create("test0",task_test0, NULL);
    task_create("test1",task_test1, NULL);
    task_create("test2",task_test2, NULL);
    while(1) {
        struct task_block *t = tasklist_waiting;
        while (t) {
            if (t->wakeup_time && (t->wakeup_time < jiffies)) {
                t->wakeup_time = 0;
                task_ready(t);
                break;
            }
            t = t->next;
        }
        WFI();
    }
}

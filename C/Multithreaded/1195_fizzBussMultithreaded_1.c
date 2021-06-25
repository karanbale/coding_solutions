/*
Write a program that outputs the string representation of numbers from 1 to n, however:

If the number is divisible by 3, output "fizz".
If the number is divisible by 5, output "buzz".
If the number is divisible by both 3 and 5, output "fizzbuzz".
For example, for n = 15, we output: 1, 2, fizz, 4, buzz, fizz, 7, 8, fizz, buzz, 11, fizz, 13, 14, fizzbuzz.

Suppose you are given the following code:

class FizzBuzz {
  public FizzBuzz(int n) { ... }               // constructor
  public void fizz(printFizz) { ... }          // only output "fizz"
  public void buzz(printBuzz) { ... }          // only output "buzz"
  public void fizzbuzz(printFizzBuzz) { ... }  // only output "fizzbuzz"
  public void number(printNumber) { ... }      // only output the numbers
}
Implement a multithreaded version of FizzBuzz with four threads.
The same instance of FizzBuzz will be passed to four different threads:

Thread A will call fizz() to check for divisibility of 3 and outputs fizz.
Thread B will call buzz() to check for divisibility of 5 and outputs buzz.
Thread C will call fizzbuzz() to check for divisibility of 3 and 5 and outputs fizzbuzz.
Thread D will call number() which should only output the numbers.
*/

#include "../standardHeaders.h"

struct rk_sema {
#ifdef __APPLE__
    dispatch_semaphore_t    sem;
#else
    sem_t                   sem;
#endif
};

typedef struct {
    int n;
#ifdef __APPLE__
    struct rk_sema number_;
    struct rk_sema fizz_;
    struct rk_sema buzz_;
    struct rk_sema fizzbuzz_;
#else
    sem_t number_;
    sem_t fizz_;
    sem_t buzz_;
    sem_t fizzbuzz_;
#endif 
} FizzBuzz;

static inline void
rk_sema_init(struct rk_sema *s, uint32_t value)
{
#ifdef __APPLE__
    dispatch_semaphore_t *sem = &s->sem;
    *sem = dispatch_semaphore_create(value);
#else
    sem_init(&s->sem, 0, value);
#endif
}

static inline void
rk_sema_wait(struct rk_sema *s)
{

#ifdef __APPLE__
    dispatch_semaphore_wait(s->sem, DISPATCH_TIME_FOREVER);
#else
    int r;
    do {
            r = sem_wait(&s->sem);
    } while (r == -1 && errno == EINTR);
#endif
}

static inline void
rk_sema_post(struct rk_sema *s)
{

#ifdef __APPLE__
    dispatch_semaphore_signal(s->sem);
#else
    sem_post(&s->sem);
#endif
}

static inline void
rk_sema_destroy(struct rk_sema *s)
{

#ifdef __APPLE__
    dispatch_release(s->sem);
#else
    sem_destroy(&s->sem);
#endif
}

void printFizz(void) {
    printf("Fizz\t");
}

void printBuzz(void) {
    printf("Buzz\t");
}

void printFizzBuzz(void) {
    printf("FizzBuzz\t");
}

void printNumber(int i) {
    printf("%d\t", i);
}

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;

    //initialize the semaphores
    rk_sema_init(&obj->number_, 1);
    rk_sema_init(&obj->fizz_, 0);
    rk_sema_init(&obj->buzz_, 0);
    rk_sema_init(&obj->fizzbuzz_, 0);

    return obj;
}

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj) {
    for(int i = 3; i <= obj->n; i += 3)
    {
        // number not divisible by 5
        if (i%15) {
            rk_sema_wait(&obj->fizz_);
            printFizz();
            //check what should be printed next (next number cannot be divisible by 3)
            if ((i + 1) % 5 == 0)
                rk_sema_post(&obj->buzz_);
            else
                rk_sema_post(&obj->number_);
        }
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    for(int i = 5; i <= obj->n; i += 5)
    {
        // number not divisible by 3
        if (i%15) {
            rk_sema_wait(&obj->buzz_);
            printBuzz();
            //check what should be printed next (next number cannot be divisible by 3)
            if ((i + 1) % 3 == 0)
                rk_sema_post(&obj->fizz_);
            else
                rk_sema_post(&obj->number_);
        }
    }
    
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    for(int i = 15; i <= obj->n; i += 15)
    {
        rk_sema_wait(&obj->fizzbuzz_);
        printFizzBuzz();
        //next number is not divisible by 3 or 5
        rk_sema_post(&obj->number_);
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    for(int i = 1; i <= obj->n; i++)
    {
        //if number is not divisible by 3 and 5
        if(i % 3 && i % 5)
        {
            rk_sema_wait(&obj->number_);
            printNumber(i);
        
            //check what should be printed next
            if ((i+1)%3 == 0 && (i+1)%5 == 0)
            {
                rk_sema_post(&obj->fizzbuzz_);
            }
            else if ((i+1)% 3 == 0)
            {
                rk_sema_post(&obj->fizz_);
            }
            else if ((i+1)% 5 == 0)
            {
                rk_sema_post(&obj->buzz_);
            }
            else
            {
                rk_sema_post(&obj->number_);
            }
        }
    }
}

void fizzBuzzFree(FizzBuzz* obj) {
    //destroy semaphores
    rk_sema_destroy(&obj->number_);
    rk_sema_destroy(&obj->fizz_);
    rk_sema_destroy(&obj->buzz_);
    rk_sema_destroy(&obj->fizzbuzz_);
    
    //free allocated memory
    free(obj);
    obj = NULL;
}

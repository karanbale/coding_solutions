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

typedef struct {
    int n;
    int curr;
    pthread_mutex_t m;
    pthread_cond_t cv;
} FizzBuzz;

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
    obj->curr = 1;
    pthread_mutex_init(&obj->m, NULL);
    pthread_cond_init(&obj->cv, NULL);
    return obj;
}

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj) {
    while (1) {
        pthread_mutex_lock(&obj->m);
        while (obj->curr <= obj->n &&
               (obj->curr % 5 == 0 || obj->curr % 3 != 0)) {
            pthread_cond_wait(&obj->cv, &obj->m);
        }

        if (obj->curr > obj->n) {
            pthread_mutex_unlock(&obj->m);
            return;
        }

        printFizz();
        obj->curr++;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->m);
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    while (1) {
        pthread_mutex_lock(&obj->m);
        while (obj->curr <= obj->n &&
               (obj->curr % 5 != 0 || obj->curr % 3 == 0)) {
            pthread_cond_wait(&obj->cv, &obj->m);
        }

        if (obj->curr > obj->n) {
            pthread_mutex_unlock(&obj->m);
            return;
        }

        printBuzz();
        obj->curr++;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->m);
    }    
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    while (1) {
        pthread_mutex_lock(&obj->m);
        while (obj->curr <= obj->n &&
               (obj->curr % 5 != 0 || obj->curr % 3 != 0)) {
            pthread_cond_wait(&obj->cv, &obj->m);
        }

        if (obj->curr > obj->n) {
            pthread_mutex_unlock(&obj->m);
            return;
        }

        printFizzBuzz();
        obj->curr++;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->m);
    }    
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    while (1) {
        pthread_mutex_lock(&obj->m);
        while (obj->curr <= obj->n &&
               (obj->curr % 5 == 0 || obj->curr % 3 == 0)) {
            pthread_cond_wait(&obj->cv, &obj->m);
        }

        if (obj->curr > obj->n) {
            pthread_mutex_unlock(&obj->m);
            return;
        }

        printNumber(obj->curr);
        obj->curr++;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->m);
    }    
}

void fizzBuzzFree(FizzBuzz* obj) {
    pthread_mutex_destroy(&obj->m);
    pthread_cond_destroy(&obj->cv);
    free(obj);
}

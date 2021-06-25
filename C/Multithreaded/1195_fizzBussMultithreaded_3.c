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
} FizzBuzz;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t n_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t f_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t b_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t fb_cond = PTHREAD_COND_INITIALIZER;
int c1;
int c2;
int c3;
int turn = 4;

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
    return obj;
}

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj) {
    pthread_mutex_lock(&lock);
    c1 = 1;
    for(int i = 3;i <= obj->n;i+=3){
        while(turn!=1){
            pthread_cond_wait(&f_cond,&lock);
        }
        printFizz();
        turn = 4;
        pthread_cond_signal(&n_cond);
        if((i+3)%15 == 0)
            i+=3;
    }
    pthread_mutex_unlock(&lock);
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    pthread_mutex_lock(&lock);
    c2 = 1;
    for(int i = 5;i <= obj->n;i+=5){
        while(turn!=2){
            pthread_cond_wait(&b_cond,&lock);
        }
        printBuzz();
        turn = 4;
        pthread_cond_signal(&n_cond);
        if((i+5)%15 == 0)
            i+=5;
    }
    pthread_mutex_unlock(&lock);
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    pthread_mutex_lock(&lock);
    c3 = 1;
    for(int i = 15;i <= obj->n;i+=15){
        while(turn!=3){
            pthread_cond_wait(&fb_cond,&lock);
        }
        printFizzBuzz();
        turn = 4;
        pthread_cond_signal(&n_cond);
    }
    pthread_mutex_unlock(&lock);
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    while(!((c1==1 && c2 ==1) && c3 ==1) ){
    }
    pthread_mutex_lock(&lock);
    for(int i = 1;i <= obj->n;i++){
        while(turn!=4){
            pthread_cond_wait(&n_cond,&lock);
        }
        if(i%15 == 0){
            turn = 3;
            pthread_cond_signal(&fb_cond);
        }
        else if(i%3 == 0){
            turn = 1;
            pthread_cond_signal(&f_cond);
        }
        else if(i%5 == 0){
            turn = 2;
            pthread_cond_signal(&b_cond);
        }else{
            printNumber(i);
        }
    }
    pthread_mutex_unlock(&lock);
}

void fizzBuzzFree(FizzBuzz* obj) {
    
}

#include "../standardHeaders.h"
#include <pthread.h>

/*

Reference: https://compas.cs.stonybrook.edu/~nhonarmand/courses/fa17/cse306/slides/11-locks.pdf

In order to achieve atomicity and implement sping locks / mutex locks, we need following understanding.

Question: Write a simple bool lock, write functions to initialize, acquire and release this lock:
Answer:
        bool lock = false;
        void initialize_lock(bool lock){
            lock = false;
        }
        void acquire_lock(bool lock){
            if(!lock) lock = true;
        }
        void release_lock(bool lock){
            lock = false;
        }

Question: What are the shortcomings of above lock and why can we not use it?
Answer:
        - There is no atomicity in above lock, so there is no mutual exclusion.
        - As there is no mutual exclusion, anyone can acquire this lock and release it.
        - This lock may cause deadlocks under certain conditions and may be released
        by any process arbitrarily leading to multiple threads entering critical section
        at the same time.

Question: How can you fix it?
Answer:
        We know atomicity instructions are Read, Modify, Write (RMW).
        There are some flavors of RMW such as following:
        - TestAndSet:
            1. Here we take the current value of lock, read it as oldValue, write the newValue to lock,
            and return oldValue.
        - FetchAndAdd:
            1. As the name suggests, we fetch the current value of the lock, add 1 to it and return old or
            fetched value (beforing adding 1 to it) back.
        - CompareAndExchange:
            1. It takes lock, oldValue and newValue as inputs. Compares oldValue and lock's value. If they're
            different, it returns false, else, it updates lock's value to newValue and returns true.
        We can now achieve atomicity if we use one of the above two mechanisms.

Question: Please implement above three atomic instructions.
Answer:
        int TAS(int *lock, int newVal){
            int oldVal = *lock;
            if(oldVal != newVal){
                *lock = newVal;
            }
            return oldVal;
        }

        int FAA(int *lock){
            int oldVal = *lock;
            *lock = oldVal+1;
            return oldVal;
        }

        bool CMPEXCHNG(int *lock, int oldVal, int newVal){
            if(oldVal != *lock){
                return false;
            }
            *lock = newVal;
            return true;
        }
    
Question: How can you use these atomic instructios to achieve atomicity while acquiring locks? Can you write a code for it?
Answer:
        typedef struct{
            int flag;
        }lock_t;

        void initialize_lock(lock_t *lock){
            lock->flag = 0;
        }

        void acquire_lock(lock_t *lock){
            // spin-and-wait until we acquire the lock
            while(TAS(&lock->flag, 1)==1);
        }

        void release_lock(lock_t *lock){
            lock->flag = 0;
        }

Question: What are the problems with above implementation?
Answer:
        Pro's:
        - We have achieved atomicity / mutual exclusion with above code.
        - We have achieved a deadlock free-code, if several threads requests lock, one of them will get it.
        
        Con's:
        - Starvation: There is no guarantee that all the threads will get the lock.
        - Fairness: This implementation will not allow all the waiting threads to acquire lock in order they were requested.
        - Performance: The spin-and-wait will waste precious CPU cycles.

Question: How can you fix the con's and maintain the pro's ? Can you write a code for it?
Answer:
        In order to avoid starvation and achieve fairness, we can implement ticket lock.
        And for ticket lock, we need to use FetchAndAdd to achieve atomicity.

        typedef struct{
            int ticket;
            int turn;
        }lock_t;

        int FAA(int *ptr) {
            int old = *ptr;
            *ptr = old + 1;
            return old;
        }

        void initialize_lock(lock_t *lock){
            lock->ticket = 0; 
            lock->turn = 0; 
        }

        void acquire_lock(lock_t *lock){
            int myTicket = FAA(lock->ticket);
            // spin-and-wait until we acquire the lock
            while(myTicket != lock->turn);    // spin until its your turn
        }

        void release_lock(lock_t *lock){
            lock->turn += 1;
        }

*/

#define THREAD_COUNT 5

typedef struct mutex{
    bool mutexLock;
    int mutexCount;
}mutex_t;

mutex_t mutex;
unsigned int counter = 0;
pthread_mutex_t lock;

int initMutex(mutex_t *mutex){
    mutex->mutexLock = false;
    mutex->mutexCount = 0;
    return 0;
}

bool TestAndSet(bool *mutexLock){
    bool oldValue = *mutexLock;
    *mutexLock = true;
    return oldValue;
}

bool CMPEXCHNG(bool *lock, bool oldVal, bool newVal){
    if(oldVal != *lock){
        return false;
    }
    *lock = newVal;
    return true;
}

int acquireMutex(mutex_t *mutex){
    // while(TestAndSet(&mutex->mutexLock) == true);
    while(!CMPEXCHNG(&mutex->mutexLock,false,true));
    return 0;
}

int releaseMutex(mutex_t *mutex){
    mutex->mutexLock = false;
    return 0;
}

void *threadHandler(void *vargp){
    int *threadId = (int *) vargp;

    // acquire mutex lock
    // acquireMutex(&mutex);
    pthread_mutex_lock(&lock);
    printf("Acquired mutex lock. THREAD_ID: %d\n", *threadId);

    // increment counter
    printf("old count: %d \t", counter);
    counter++;
    printf("current count: %d\n", counter);

    // sleep for 1 sec
    sleep(1);

    // release mutex lock
    printf("Releasing mutex lock.THREAD_ID: %d\n", *threadId);
    // releaseMutex(&mutex);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void){

    // Create an array of threads
    pthread_t THREAD_ID[THREAD_COUNT];
    // create array of args to threads
    int thread_arg[THREAD_COUNT];

    // initialize mutex
    // if(initMutex(&mutex)){
    //     printf("Failed to init mutex.\n");
    // }

    // Initialize threads
    if(pthread_mutex_init(&lock, NULL)){
        printf("Failed to initialize mutex.\n");
    }

    for(int i=0; i<THREAD_COUNT; i++){
        thread_arg[i] = i;
        // create thread
        pthread_create(&THREAD_ID[i], NULL, &threadHandler, (void *)&thread_arg[i]);
    }

    for(int i=0; i<THREAD_COUNT; i++){
        // join thread
        pthread_join(THREAD_ID[i], NULL);
    }

    return 0;
}

// int main() 
// { 
//     pthread_t thread_id; 
//     printf("Before Thread\n"); 
//     pthread_create(&thread_id, NULL, myThreadFun, NULL); 
//     pthread_join(thread_id, NULL); 
//     printf("After Thread\n"); 
//     exit(0); 
// }
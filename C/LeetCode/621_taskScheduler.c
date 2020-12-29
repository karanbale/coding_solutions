/*
Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents a different task.
Tasks could be done in any order.
Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.
However, there is a non-negative integer n that represents the cooldown period between two same tasks (the same letter in the array),
that is that there must be at least n units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.

Example 2:
Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.

Example 3:
Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: 
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A
 
Constraints:

1 <= task.length <= 104
tasks[i] is upper-case English letter.
The integer n is in the range [0, 100].

*/

#include "../standardHeaders.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define ASCII_BASIC_SIZE 128
#define ASCII_EXTENDED_SIZE (ASCII_BASIC_SIZE*2)

int cmp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

int leastInterval(char* tasks, int tasksSize, int n){
    
    // if no idle time, we can run all tasks back to back
    if(n == 0)  return tasksSize;

    // track total number of occurance of a task in a hashSet
    int hashSet[ASCII_EXTENDED_SIZE] = {0};
    for(int i=0; i<tasksSize; i++){
        hashSet[(int)tasks[i]]++;
    }
    
    // sort the hashSet from least number of occurances to max
    qsort((void *)hashSet, ASCII_EXTENDED_SIZE, sizeof(int), cmp);
    
    // find out max occurance of a task, substract 1 from it, since,
    // when this task gets scheduled one last time, there will be no idle slot AFTER it
    int maxSlots = hashSet[ASCII_EXTENDED_SIZE-1] - 1;
    // maxIdleSlots needed in worse case would be
    // max occurances of a task * idle time between two same tasks
    int maxIdleSlots = maxSlots * n;
    
    // iterate over remaining tasks (except the task with max number of occurances)
    for(int i=ASCII_EXTENDED_SIZE-2; i>=0; i--){
        // for each task, substract its occurance from maxIdleSlots,
        // since they will take up this empty space in maxIdleSlots
        maxIdleSlots -= MIN(hashSet[i], maxSlots);
    }
    
    // if maxIdleSlots > 0, then we have max idle slots required,
    // thus return maxIdleSlots + total tasks 
    // if maxIdleSlots <= 0 for whatever reason, we just need tasksSize cycles
    return maxIdleSlots > 0 ? maxIdleSlots + tasksSize : tasksSize;
    
}

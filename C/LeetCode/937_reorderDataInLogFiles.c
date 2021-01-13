/*
You have an array of logs.  Each log is a space delimited string of words.
For each log, the first word in each log is an alphanumeric identifier.  Then, either:

Each word after the identifier will consist only of lowercase letters, or;
Each word after the identifier will consist only of digits.
We will call these two varieties of logs letter-logs and digit-logs. 
It is guaranteed that each log has at least one word after its identifier.

Reorder the logs so that all of the letter-logs come before any digit-log.
The letter-logs are ordered lexicographically ignoring identifier, with the identifier used in case of ties. 
The digit-logs should be put in their original order.\
Return the final order of the logs.

Example 1:
Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]

Constraints:

0 <= logs.length <= 100
3 <= logs[i].length <= 100
logs[i] is guaranteed to have an identifier, and a word after the identifier.
*/

#include "../standardHeaders.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int logCompare(const void *plog1, const void *plog2){
    int i = 0, j = 0;
    while((*(char **)plog1)[i] != ' ') i++; //find the first 'space'
    while((*(char **)plog2)[j] != ' ') j++;
    if(strcmp(*(char **)plog1 + i + 1, *(char **)plog2 + j + 1) == 0){
        // printf("match found: %s\t%s\n",(*plog1 + i + 1), (*plog2 + j + 1));
        return strcmp(*(char **)plog1, *(char **)plog2);
    }
    return strcmp(*(char **)plog1 + i + 1, *(char **)plog2 + j + 1);
}

char** reorderLogFiles(char** logs, int logsSize, int* returnSize) {
    int logIdx, totalDigitStrings;
    // start comparing from last element, since we want to preserve order of deigit-logs
    // if we compare last element with second last element and found digit log at second last position, we can simply swap these two, and move digit log to the end and preserve its order
    // keep running above alogrithm to sort input logs such that digit logs in order on right hand side of the list and letter-logs are on left side
    logIdx = totalDigitStrings = logsSize - 1;
    int spacePos = 0;
    char* tempPtr = NULL;
    while(logIdx >= 0){
        spacePos = 0;
        // find the fist space in the string, so we can check if its digit log or letter log
        while(logs[logIdx][spacePos] != ' ') spacePos++;
        // printf("comparing: %s with %s\n", logs[j], logs[i]);
        // if the first character after identifier is a digit, lets swap it with the last string
        if(isdigit(logs[logIdx][++spacePos])){
            tempPtr = logs[totalDigitStrings];
            logs[totalDigitStrings] = logs[logIdx];
            logs[logIdx] = tempPtr;
            totalDigitStrings--;
        }
        logIdx--;
    }

    // for(int i=0; i<logsSize; i++){
    //     printf("%s\n",logs[i]);
    // }
    // printf("j: %d\n",totalDigitStrings);
    
    qsort(logs, totalDigitStrings + 1, sizeof(logs[0]), logCompare);
    
    *returnSize = logsSize;
    return logs;
}


/*
Sample inputs to test:
["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
["t kvr", "r 3 1", "i 403", "7 so", "t 54"]
["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo","a2 act car"]
*/
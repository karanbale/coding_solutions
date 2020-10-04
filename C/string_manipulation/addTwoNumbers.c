/*
You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

*/

#include "string_manipulation_headers.h"

#define SUM(a,b) ((a) + (b))

 struct ListNode {
     int val;
     struct ListNode *next;
 }ListNode;


struct ListNode* newNode(size_t val);
struct ListNode* addNode(struct ListNode* headNode, struct ListNode* newNode);
struct ListNode* fromNumberToNodes(int num);
int fromNodesToNumber(struct ListNode* headNode);
void printNodes(struct ListNode* headNode);
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);
int addTwoNums(int num1, int num2);
void freeNodes(struct ListNode* headNode);

void freeNodes(struct ListNode* headNode){
    struct ListNode* tempNode = NULL;
    tempNode = headNode;
    while(headNode != NULL){
        headNode = headNode->next;
        free(tempNode);
    }
}

/***********************************************************************************************/
/*************************************** SOLTUION 1 ********************************************/
/*

The reason why following solution will fail is test case:
l1 = [1,9,9,9,9,9,9,9,9,9]
l2 = [9]

Here l1 + l2 goes beyond 32 bit digit addition.
If we set our output to size_t, we may have linked lists, which are, 30/40 digits long.
In such cases, we have native data type size limitations, thus, this solutionf fails.
Solution 2 fixes it easily by simply performing in place digit addition and take the carry over
to next iteration, thus there is no limitation on how many linked list digits one can have.

*/
/***********************************************************************************************/
#define SUM(a, b) ((a) + (b))

struct ListNode* newNode(size_t val){
    struct ListNode* node1 = malloc(sizeof(*node1));
    if((node1 == NULL) || (val > INT32_MAX)){
        printf("returning...\n");
        free(node1);
        return NULL;
    }
    node1->val = (int)val;
    node1->next = NULL;
    return node1;
}

struct ListNode* addNode(struct ListNode* headNode, struct ListNode* newNode){

    struct ListNode* tempNode = headNode;

    // Check if headNode == NULL i.e. if its first node
    if(headNode == NULL){
        headNode = newNode;
        return headNode;
    }

    // otherwise traverese until you find end of the node and then append newNode
    while (tempNode->next != NULL)
    {
        tempNode = tempNode->next;
    }

    tempNode->next = newNode;
    free(tempNode);

    return headNode;
};

size_t retNumFromNodesSolution2(struct ListNode* headNode){
    size_t retNum = 0, tempNum = 0;
    int digit=0;
    struct ListNode* tempNode1 = NULL;
    if(headNode == NULL) return retNum;
    tempNode1 = headNode;
    
    while(tempNode1 != NULL){
        retNum = (((tempNode1->val)*pow(10,digit++)) + retNum) ;
        printf("retNum: %lu digit: %d\n",retNum, digit);
        tempNode1 = tempNode1->next;
        digit++;
    }
    while(retNum != 0){
        tempNum = ((tempNum*10)+(retNum%10));
        retNum = retNum/10;
    }
    printf("nUM: %lu\n",tempNum);
    return tempNum;
}

struct ListNode* retNodesFromNumSolution2(size_t num){
    struct ListNode* tempHeadNode = NULL;
    struct ListNode* tempCurrNode = NULL;
    
    size_t tempNum = num;
    if(tempNum == 0){
        struct ListNode* tempNewNode = malloc(sizeof *tempNewNode);
        tempNewNode->next = NULL;
        tempNewNode->val = 0;
        return tempNewNode;
    }
    while(tempNum != 0){
        struct ListNode* tempNewNode = malloc(sizeof *tempNewNode);
        tempNewNode->next = NULL;
        if(tempNewNode == NULL) {
            printf("returning..");
            return NULL;
        }
        tempNewNode->val = tempNum%10;
        
        if(tempHeadNode == NULL){
            tempHeadNode = tempNewNode;
            tempCurrNode = tempHeadNode;
        }
        else{
            tempCurrNode->next=tempNewNode;
            tempCurrNode = tempNewNode;
        }
        tempNum = tempNum/10;
    }
    
    return tempHeadNode;
    
}

void printNodesSolution2(struct ListNode* headNode){
    struct ListNode* tempNode = NULL;
    tempNode = headNode;
    
    while(tempNode != NULL){
        printf("%d->",tempNode->val);
        tempNode = tempNode->next;
    }
    printf("\n");
}

struct ListNode* addTwoNumbersSolution2(struct ListNode* l1, struct ListNode* l2){
    
    struct ListNode* tempNode1 = NULL;
    struct ListNode* tempNode2 = NULL;
    struct ListNode* tempNode3 = NULL;
    tempNode1 = l1;
    tempNode2 = l2;
    
    size_t num1, num2, num3;
    num1 = retNumFromNodesSolution2(tempNode1);
    num2 = retNumFromNodesSolution2(tempNode2);
    
    printf("num1  : %lu \n",num1);
    printf("num2  : %lu \n",num2);
    num3 = num1+num2;
    if(num3 < 0) printf("its gone bro\n");
    printf("total : %lu \n",num3);
    
    tempNode3 = retNodesFromNumSolution2(num3);
    printNodesSolution2(tempNode1);
    printNodesSolution2(tempNode2);
    printNodesSolution2(tempNode3);
    
    return tempNode3;
}


/***********************************************************************************************/

/***********************************************************************************************/
/*************************************** SOLTUION 1 ********************************************/
/***********************************************************************************************/

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    
    struct ListNode* tempNode1 = NULL;
    struct ListNode* tempNode2 = NULL;
    tempNode1 = l1;
    tempNode2 = l2;

    int carry = 0 ;
    struct ListNode* tempHeadNode = NULL;
    struct ListNode* tempCurrNode = NULL;
    
    while((tempNode1 != NULL) || (tempNode2 != NULL)){
        struct ListNode* tempNewNode = malloc(sizeof *tempNewNode);
        tempNewNode->next = NULL;
        if(tempNewNode == NULL) {
            printf("returning..");
            return NULL;
        }
        int val = 0;
        val += (tempNode1 != NULL ? tempNode1->val : 0);
        val += (tempNode2 != NULL ? tempNode2->val : 0);
        val += carry;
        tempNewNode->val = (val%10);
        carry = val/10;
        if(tempHeadNode == NULL){
            tempHeadNode = tempNewNode;
            tempCurrNode = tempHeadNode;
        }
        else{
            tempCurrNode->next=tempNewNode;
            tempCurrNode = tempNewNode;
        }
        tempNode1 = (tempNode1 != NULL ? tempNode1->next : NULL);
        tempNode2 = (tempNode2 != NULL ? tempNode2->next : NULL);
    }
    if(carry){
        struct ListNode* tempNewNode = malloc(sizeof *tempNewNode);
        if(tempNewNode == NULL) {
            return NULL;
        }
        tempNewNode->next = NULL;
        tempNewNode->val = carry;
        tempCurrNode->next=tempNewNode;
        tempCurrNode = tempNewNode;
    }
    
    return tempHeadNode;
}

/***********************************************************************************************/

struct ListNode* fromNumberToNodesWrapper(char* numArr){
    struct ListNode* tempHeadNode = NULL;
    struct ListNode* tempCurrNode = NULL;
    while(numArr != '\0'){
        //allocate new node on heap and check its not NULL i.e. it was allocated successfully
        struct ListNode* tempNewNode = malloc(sizeof *tempNewNode);
        if(tempNewNode == NULL) {
            return NULL;
        }
        tempNewNode->next = NULL;
        tempNewNode->val = atoi(numArr);
        //*numArr++;
    }
    return tempHeadNode;
}

int main(void){
    
    int num1=2000;
    int num2=1000;

    printf("\n");
    return 0;

}


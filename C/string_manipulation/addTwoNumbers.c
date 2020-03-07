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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>


 struct ListNode {
     int val;
     struct ListNode *next;
 }ListNode;


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){

}

struct ListNode* newNode(size_t val){
    struct ListNode* node1 = malloc(sizeof *node1);
    if((node1 == NULL) || (val > INT32_MAX)){
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

struct ListNode* formNumberToNodes(int num){    
    int headNodeSet=0;
    struct ListNode* headNode;
    while(num != 0){
        int remainder=0;
        remainder = num%10;
        struct ListNode* tempNode = newNode(remainder);
        if(!headNodeSet){
            headNode = tempNode;
            headNodeSet = 1;
        }
        headNode = addNode(headNode, tempNode);
        num = num/10;
    }    

    return headNode;
}

int formNodesToNumber(struct ListNode* headNode){

    int retNumber = 0, digitCount=0;
    struct ListNode* tempNode = headNode;

    if(headNode == NULL) return retNumber;

    while (tempNode!=NULL)
    {
        // overflow since digit is > INT32_MAX
        if(digitCount > 10){
            return 0;
        }
        retNumber = retNumber/10 + tempNode->val;
        tempNode = tempNode->next;
        digitCount++;
    }

    return retNumber;

}


void printNodes(struct ListNode* headNode){
    struct ListNode* tempNode = headNode;

    // Check if headNode == NULL i.e. if its first node
    if(tempNode == NULL){
        printf("no nodes found.\n");
        return;
    }

    while(tempNode->next != NULL){
        printf("Value: %d", tempNode->val);
        tempNode=tempNode->next;
    }

}

int main(void){
    


    return 0;

}


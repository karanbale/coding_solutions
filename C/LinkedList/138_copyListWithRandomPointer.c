/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
Return a deep copy of the list.

The Linked List is represented in the input/output as a list of n nodes.
Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) where random pointer points to,
or null if it does not point to any node.
 
Example 1:
Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

Example 2:
Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]

Example 3:
Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

Example 4:
Input: head = []
Output: []
Explanation: Given linked list is empty (null pointer), so return null.
 

Constraints:

-10000 <= Node.val <= 10000
Node.random is null or pointing to a node in the linked list.
The number of nodes will not exceed 1000.
*/

#include "../standardHeaders.h"

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

 struct Node {
     int val;
     struct Node *next;
     struct Node *random;
};

struct Node *createNode(int data){
    struct Node *node = malloc(sizeof(struct Node));
    if(!node)   return NULL;
    node->val = data;
    node->next = NULL;
    node->random = NULL;
    return node;
}

void print(struct Node *head){
    while(head!=NULL){
        printf("%d->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

struct Node* copyRandomList(struct Node* head) {
	if(head == NULL) return NULL;
    
    struct Node* ptr = head, *newHead = NULL, *tempNewHead = NULL;
    while(ptr != NULL){
        struct Node *node = createNode(ptr->val);
        if(!node)   return NULL;
        node->next = ptr->next;
        ptr->next = node;
        ptr = node->next;
    }
    
    ptr = head;
    while(ptr != NULL){
        ptr->next->random = (ptr->random != NULL) ? ptr->random->next : NULL;
        ptr = ptr->next->next;
    }
    
    ptr = head;
    newHead = head->next;
    tempNewHead = head->next;
    while(ptr!=NULL){
        ptr->next = ptr->next->next;
        tempNewHead->next = (tempNewHead->next != NULL) ? tempNewHead->next->next : NULL;
        ptr = ptr->next;
        tempNewHead = tempNewHead->next;
    }
    return newHead;
    
}

/*
Sample example test cases:
[[7,null],[13,0],[11,4],[10,2],[1,0]]
[[1,1],[2,1]]
[[3,null],[3,0],[3,null]]
[]
*/
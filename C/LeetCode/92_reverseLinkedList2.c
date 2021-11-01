/*
Given the head of a singly linked list and two integers left and right where left <= right,
reverse the nodes of the list from position left to position right, and return the reversed list.

Example 1:
Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]

Example 2:
Input: head = [5], left = 1, right = 1
Output: [5]

Constraints:

The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n

Follow up: Could you do it in one pass?
*/

#include "../standardHeaders.h"

/**
 * Definition for singly-linked list.
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseBetween(struct ListNode* head, int left, int right){
    if(head == NULL)    return NULL;
    struct ListNode *prev = NULL;
    struct ListNode *curr = head;
    while(left>1) {
        prev = curr;
        curr = curr->next;
        --left;
        --right;
    }

    struct ListNode *prev1 = prev;
    struct ListNode *tail = curr;
    struct ListNode *next1 = NULL;
    while(right) {
        next1 = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next1;
        --right;
    }

    if(prev1 != NULL) prev1->next = prev;
    else    head = prev;

    tail->next = curr;
    return head;
}

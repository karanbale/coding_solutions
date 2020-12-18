/*
Reverse a singly linked list.

Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

#include "../standardHeaders.h"

struct ListNode* reverseList(struct ListNode* head){
    
    struct ListNode *prev = NULL;
    struct ListNode *curr = head;
    while(curr!=NULL){
        struct ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;

}

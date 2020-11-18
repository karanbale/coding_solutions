/*

Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

Given a singly linked list, determine if it is a palindrome.

Example 1:
Input: 1->2
Output: false

Example 2:
Input: 1->2->2->1
Output: true

Follow up:
Could you do it in O(n) time and O(1) space?

Sample inputs:
[1,1,1,1]
[1]
[1,2,3,4,3,2,1]
[1,2,3,4,4,3,2,1]
[1,2]
[-129,-129]

*/

#include "../standardHeaders.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

bool isPalindrome(struct ListNode* head){
    
    if((head == NULL) || (head->next == NULL))    return true;
    
    struct ListNode *curr = NULL, *prev = NULL, *next = NULL;
    struct ListNode *fastPtr = head, *slowPtr = head;
    
    // printList(head);
    
    // find the middle node of the linked list
    while((fastPtr->next) && (fastPtr->next->next)){
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
    }
    
    /* Now slowPtr is pointing to the middle node
       We would like to break the linked list at this stage in two halves
    */
    
    // first element after mid-point will be our current element 
    curr = slowPtr->next;
    // we'll break the linked list by simply cutting off the node at mid-point
    slowPtr->next=NULL;
    
    /* After breaking linked list, we want to reverse linked list in only one half */
    
    // iterate over second half until we reach end of it
    while(curr){
        // point next to curr->next
        next = curr->next;
        // point curr-> next to prev i.e. reverse the link
        curr->next = prev;
        // now for next iteration, our current node will be prev node, hence
        prev = curr;
        // for next iteration, our next node will be our current node, hence
        curr = next;
        // printList(prev);
    }
    
    // printList(prev);
    
    // at this point, our prev node is the last node
    // Notice, curr = next, which means, our curr is pointing to NULL at this point
    
    // assign curr to head of the reversed linked list
    curr = prev;
    
    // now compare two linked lists
    while(curr){
        // check for mis-match, if found, return false
        if(head->val != curr->val){
            return false;
        }
        head = head->next;
        curr = curr->next;
    }
    
    // everything matched, return true
    return true;

}
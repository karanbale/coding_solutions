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

// allocate first pointer to NULL and make it global so we can work with it in recursive loop
struct ListNode *fp = NULL;
static bool forceRet = false;

bool isPalindromeRecursive(struct ListNode* head){
    // return when reached end of linked list
    if(head == NULL){
        return true;
    }
    // keep calling recursively until we reach end of linked list
    else if(isPalindromeRecursive(head->next)){
        // if we're inside means we've reached end of linked list and need to travese back to head now
        // start comparing current node aka head node, against first pointer fp
        if(head->val != fp->val){
            // we cant exit function until we return all the calls on stack
            forceRet = true;
            return false;
        }
        fp = fp->next;
    }

    // we need to keep returning false, if we found mismatch, true otherwise
    // this function won't exit until all recursive calls are serviced off the stack
    return ((forceRet == false) ? true : false);
}

bool isPalindromeMethod1(struct ListNode* head){
    
    if((head == NULL) || (head->next == NULL))    return true;
    
    fp = head;
    bool retVal = isPalindromeRecursive(head);
    /*
    Need to restore these global values to default, otherwise if we run test
    in following sequence on Leetcode, they fail for last few but pass for rest.
	
    if I run the only failing tests from following sequence by themselves, they seem to pass.
	Running them AFTER few other tests, forces them to fail. This has to do with LeetCode probably 
    not instantiating new code instance for each input.
    Failing test sequence without reseting static forceRet and fp vars:
        [1,1,1,1]
        [1]
        [1,2,3,4,3,2,1]
        [1,2,3,4,4,3,2,1]
        [1,2]
        [-129,-129]
    
    */
    forceRet = false;
    fp = NULL;
    
    return retVal;

}

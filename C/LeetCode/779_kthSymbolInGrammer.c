/*
On the first row, we write a 0. Now in every subsequent row, 
we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.
Given row N and index K, return the K-th indexed symbol in row N. (The values of K are 1-indexed.) (1 indexed).

Examples:

Input: N = 1, K = 1
Output: 0

Input: N = 2, K = 1
Output: 0

Input: N = 2, K = 2
Output: 1

Input: N = 4, K = 5
Output: 1

Explanation:
row 1: 0
row 2: 01
row 3: 0110
row 4: 01101001
Note:

N will be an integer in the range [1, 30].
K will be an integer in the range [1, 2^(N-1)].

NOTE: Representing above rows in a binary tree format gives us following, each node is of the format (data, index)
Index starts with 1 for simplicity

N=1                                        0(1)
                                    /               \
N=2                        0(1)                            1(2)
                        /        \      /         \    /         \
N=3                0(1)            1(2)            1(3)            0(4)
                 /      \         /     \         /    \          /    \
N=4            0(1)    1(2)     1(3)    0(4)   0(5)   1(6)    1(7)    0(8)
               ODD     EVEN    ODD     EVEN    ODD     EVEN    ODD     EVEN

*/

#include "../standardHeaders.h"

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

int kthGrammarMethod1(int N, int K){
    
    // simple observation tells us we have 2^(N-1) bits per row
    // i.e. row 1 has 1 bit, row 2 has 2, row 3 has 4, row 4 has 8 and so on...
    size_t totalBitsAtNthRow = (1 << (N-1));
    
    // as we can see it is a binary tress structure, where the root node has 2 nodes on either side.
    // and each node on either side can have further 2 nodes 
    // thus this is a balanced binary tree, since all nodes will have children at any given time
    // and all leaf nodes will have no children at the depth of N
    
    // we can traverse binary tree on left or right side. 
    // we know number of bits at row N (or depth N), but we don't know where does Kth bit reside in this tree
    // to find out Kth bit, we can traverse binary tree and find out what value it holds (value will be 0 or 1, as you can imagine)
    // notice, in this binary tree, we start with root node = 0 and node 0 has two children, 0 and 1 (given condition)
    // which means, on the left hand side of the tree, everything will be 0 (you can try drawing a tree to see this)
    // on the right hand side of the tree since, 1 has two children 1 and 0,
    // our bits will flip for every incremental row
    
    size_t left = 1;
    size_t right = totalBitsAtNthRow;
    
    // bit is set to false since our first index is always 0 (given in problem)
    bool bit = false;
    
    // here, bit represents the nature of flip bit on right side of the tree
    size_t mid;
    while(left != right){
        mid = (left + right)/2;
        if(K <= mid){
            // we need to go left, since k <= mid
            right = mid;
        }
        else{
            // we need to go to right, since k > mid
            left = mid+1;
            // flip the bit for every right traversal
            bit = !bit;
        }
    }
    
    return (left == K) ? (int)(bit) : (int)(!bit);
    
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

int kthGrammarMethod2(int N, int K){

    /*
    The whole structure can be viewed a binary tree, when a node is 0, their two children nodes are 0 and 1, similarly, 
    when a node is 1, two children nodes are 1 and 0. 
    
    If we look at the value of K, we can tell, all odd values of K are the LHS children of their parents,
    and all even values of K are the RHS children of their parents.
    We can now know whether the position of K is a left node or a right node by finding if K's value is odd or even. 
    
    If K is even, current node is right child, and its parent is the (K/2)th node in previous row; 

    If K is odd, current node is left child and its parent is the ((K+1)/2)th node in previous row.
    
    The value of current node depends on its parent node, without knowing its parent node value, 
    we still cannot determine current node value. 
    That's why we need recursion, we keep going previous row to find the parent node until reach the first row. 
    Then all the parent node value will be determined after the recursion function returns.
    */

   // for odd value of N, return 0
   if( N == 1 || K == 1){   return 0;   }

   if(K%2 == 0){
       return ((kthGrammarMethod1(N-1, K/2) == 0) ? 1  : 0);            // K is even, its on RHS of tree, so its child is flipped, so if parent = 0, return 1
   }
   else{
       return ((kthGrammarMethod1(N-1, (K+1)/2) == 0) ? 0 : 1);         // K is odd, parent and child both has same value, so return same value as that of parent
   }

}

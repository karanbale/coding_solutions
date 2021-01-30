/*
Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
If possible, output any possible result.  If not possible, return the empty string.

Example 1:
Input: S = "aab"
Output: "aba"

Example 2:
Input: S = "aaab"
Output: ""

Note:
S will consist of lowercase letters and have length in range [1, 500].
 
*/

#include "../standardHeaders.h"

struct heap {
    int *A;
    int idx;
};

struct heap* newHeap(int size){
    struct heap *h = (struct heap *) malloc(sizeof(struct heap));
    // Index starts at 1 to make the math in helper fn's easier.. just for this problem.
    h->idx = 1; 
    h->A = (int *) malloc(sizeof(int)* size);

    return h; 
} 

void insert(struct heap* h, int num){
    int *A = h->A;
    int node = h->idx;
    int parent = node/2;
    
    A[h->idx] = num;

    h->idx++;
    
    while(true){
        if (node == 1){
            A[node] = num;
            break;
        } 
        if (A[parent] >= A[node]){
            break;
        } 
        if (A[node] > A[parent]){
            int temp = A[node];
            A[node]  = A[parent];
            A[parent] = temp;

            node = parent; 
            parent = floor(node/2);                     
        }       
    }    
}

int removeTop (struct heap* h){
    int* A = h->A;
    int ret = A[1];
    int parent = 1;
    int l = parent * 2;
    int r = parent * 2 + 1;

    if (A[l] == 0 && A[r] == 0) return ret;             

    A[1] = A[h->idx-1];

    while(h->idx != 1 && parent < h->idx/2){
        l = parent *2;
        r = l + 1;

        if (r < h->idx && A[l] < A[r]){
            if (A[parent] >= A[r]) break;
            int temp = A[r];
            A[r] = A[parent];
            A[parent] = temp;
            parent = r;
        } else {
            if (A[parent] >= A[l]) break;
            int temp = A[l];
            A[l] = A[parent];
            A[parent] = temp;
            parent = l; 
        }
    }

    h->idx--;

    return ret;
}

void printHeap(struct heap *h){
    for (int q = 0; q < 27; q++){
        printf("%d, ", h->A[q]);
    } 
}

char* reorganizeString(char* S){
    int l = strlen(S);
    int s[26]; 
    struct heap *h = newHeap(100);

    memset(s, 0, sizeof(int) * 26);

    for (int n = 0; n < l; n++) s[S[n]-97] += 100;   

    for (int i = 0; i < 26; ++i) s[i] += i;

    for (int i = 0; i < 26; ++i) {
        if (s[i] >= 100) insert(h, s[i]);       
    }

    int p = 0; 

    int *pq = h->A;

    for (int n = 0; p < l; n++){
        int letter = removeTop(h);
        int ct = letter / 100;
        int chr = 'a' + (letter % 100);

        int letter2 = removeTop(h);
        int ct2 = letter2 / 100;
        int chr2 = 'a' + (letter2 % 100);

        if (ct > (l+1)/2) return "";
        if (ct2 > (l+1)/2) return "";

        if (p==0 || chr != S[p-1]){
            S[p] = chr;
            letter -= 100;
            p++;

            if (p >= l) break;  

            S[p] = chr2;
            letter2 -= 100;
            p++;
        }else {
            S[p] = chr2;
            letter2 -= 100;
            p++;

            if (p >= l) break;  

            S[p] = chr;
            letter -= 100;
            p++;
        }

        if (letter >= 100) insert(h, letter); 
        if (letter2 >= 100) insert(h, letter2); 
    }

    return S;
}
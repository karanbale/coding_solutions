/*
A cafeteria table consists of a row of NN seats, numbered from 11 to NN from left to right.
Social distancing guidelines require that every diner be seated such that KK seats to their left and KK seats to their right remain empty.
There are currently MM diners seated at the table, the iith of whom is in seat S_iS 
i
​
 . No two diners are sitting in the same seat, and the social distancing guidelines are satisfied.
Determine the maximum number of additional diners who can potentially sit at the table without social distancing guidelines being violated for any new or existing diners, assuming that the existing diners cannot move and that the additional diners will cooperate to maximize how many of them can sit down.
Please take care to write a solution which runs within the time limit.
Constraints
1 \le N \le 10^{15}1≤N≤10 
15
 
1 \le K \le N1≤K≤N
1 \le M \le 500,0001≤M≤500,000
1 \le S_i \le N1≤S 
i
​
 ≤N
Sample Test Case #1
N = 10
K = 1
M = 2
S = [2, 6]
Expected Return Value = 3
Sample Test Case #2
N = 15
K = 2
M = 3
S = [11, 6, 14]
Expected Return Value = 1
Sample Explanation
In the first case, the cafeteria table has N = 10N=10 seats, with two diners currently at seats 22 and 66 respectively.
The table initially looks as follows, with brackets covering the K = 1K=1 seat to the left and right of each existing diner that may not be taken.
  1 2 3 4 5 6 7 8 9 10
  [   ]   [   ]
Three additional diners may sit at seats 44, 88, and 1010 without violating the social distancing guidelines.
In the second case, only 11 additional diner is able to join the table, by sitting in any of the first 33 seats.
*/

#include "../standardHeaders.h"

void expandDinerSeatMap(int K, char dinerSeatMap[], long long N, size_t currDinerIndex, size_t *currDinerSeats) {
  bool validWindow = true;
  ssize_t nextDinerRIndex = (currDinerIndex + K) < N ? (currDinerIndex + K) : N;
  ssize_t nextDinerLIndex = ((ssize_t)(currDinerIndex - K) )> 0 ? (currDinerIndex - K) : 0;
  ssize_t currLIndex = currDinerIndex;
  ssize_t currRIndex = currDinerIndex;
  while(currLIndex > nextDinerLIndex && currRIndex < nextDinerRIndex) {
    if('1' == dinerSeatMap[--currLIndex] || '1' == dinerSeatMap[++currRIndex]) {
      validWindow = false;
    }
  }
  currLIndex = currDinerIndex;
  currRIndex = currDinerIndex;
  if(validWindow) {
    dinerSeatMap[currDinerIndex] = '1';
    while(currLIndex > nextDinerLIndex || currRIndex < nextDinerRIndex) {
      dinerSeatMap[--currLIndex] = 'X';
      dinerSeatMap[++currRIndex] = 'X';
    }
  }
  else {
    dinerSeatMap[currDinerIndex] = 'X';
  }
  (*currDinerSeats)++;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

long long getMaxAdditionalDinersCount(long long N, long long K, int M, long long* S) {
  // Write your code here
  // N seats, numbered 1 to N
  // K social distance between diners, on either side of them
  // M diners currently seated
  // Si is ith seat of a diner
  // No two diners are in same seat and M distance between all of them

  // char *dinerSeatMap = (char *) malloc(sizeof(char) * N);
  uint8_t dinerSeatMap[N];
  memset(&dinerSeatMap, 0, N);
  // number of diners equals or exceeds number of seats
  if (M >= N) {
    return M; // or return 0 since social distance guidelines are not met
  }
  size_t currDinerSeats = 0;

  qsort(S, M, sizeof(long long), cmpfunc);
  
  for(int i=0; i<M; i++) {
    int index = S[i] - 1;
    dinerSeatMap[index] = 1;
    int leftWindow = ((index-K) >=0) ? (index-K) : 0;
    int rightWindow = ((index+K) < N) ? (index+K) : N;
    size_t currLIndex = index;
    size_t currRIndex = index;
    while(currLIndex > leftWindow || currRIndex < rightWindow) {
      dinerSeatMap[--currLIndex] = 2;
      dinerSeatMap[++currRIndex] = 2;
    }
    currDinerSeats++;
  }
 
  for(size_t i=0; i<N; i++) {
    if(2 == dinerSeatMap[i]) {
      i = i+(K*2);
    }
    else if(0 == dinerSeatMap[i]) {
      // start expanding from here on either side
      // expandDinerSeatMap(K, &dinerSeatMap[0], N, i, &currDinerSeats);
      bool validWindow = true;
      ssize_t nextDinerRIndex = (i + K) < N ? (i + K) : N;
      ssize_t nextDinerLIndex = ((ssize_t)(i - K) )> 0 ? (i - K) : 0;
      ssize_t currLIndex = i;
      ssize_t currRIndex = i;
      while(currLIndex > nextDinerLIndex && currRIndex < nextDinerRIndex) {
          if((1 == dinerSeatMap[--currLIndex]) || (1 == dinerSeatMap[++currRIndex])) {
              validWindow = false;
              dinerSeatMap[i] = 2;
          }
      }
      if(validWindow) {
          currLIndex = i;
          currRIndex = i;
          dinerSeatMap[i] = 1;
          while(currLIndex > nextDinerLIndex || currRIndex < nextDinerRIndex) {
              dinerSeatMap[--currLIndex] = 2;
              dinerSeatMap[++currRIndex] = 2;
          }
          i = currLIndex-1;
          currDinerSeats++;
      }
    }
  }
  return (currDinerSeats - M);
}

typedef struct {
    long long N;
    long long K;
    int M;
} sampleStruct;

int main(void) {
    sampleStruct  str1 = {.N = 10, .K = 1, .M = 2};
    // long long N = 10, K = 1;
    // int M = 2;
    long long S1[2] = {6,2};
    printf("%lld\n", getMaxAdditionalDinersCount(str1.N, str1.K, str1.M, S1));

    sampleStruct  str2 = {.N = 15, .K = 2, .M = 3};
    long long S2[3] = {11, 6, 14};
    // [0,0,0,X,X,1,X,X,X,X,1,X,X,1,X]
    // [1,X,X,0,0,0]
    // [x,x,x,1,X,x,1,x,x,x,x,1,x,x,1]
    printf("%lld\n", getMaxAdditionalDinersCount(str2.N, str2.K, str2.M, S2));

}

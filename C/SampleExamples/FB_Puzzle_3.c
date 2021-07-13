/*
You're playing Battleship on a grid of cells with RR rows and CC columns.
There are 00 or more battleships on the grid, each occupying a single distinct cell.
The cell in the iith row from the top and jjth column from the left either contains a battleship (G_{i,j} = 1G 
i,j
​
 =1) or doesn't (G_{i,j} = 0G 
i,j
​
 =0).
You're going to fire a single shot at a random cell in the grid.
You'll choose this cell uniformly at random from the R*CR∗C possible cells.
You're interested in the probability that the cell hit by your shot contains a battleship.
Your task is to implement the function getHitProbability(R, C, G) which returns this probability.
Note: Your return value must have an absolute or relative error of at most 10^{-6}10 
−6
  to be considered correct.
Constraints
1 \le R, C \le 1001≤R,C≤100
0 \le G_{i,j} \le 10≤G 
i,j
​
 ≤1
Sample Test Case #1
R = 2
C = 3
G = 0 0 1
    1 0 1
Expected Return Value = 0.50000000
Sample Test Case #2
R = 2
C = 2
G = 1 1
    1 1
Expected Return Value = 1.00000000
Sample Explanation
In the first case, 33 of the 66 cells in the grid contain battleships.
Therefore, the probability that your shot will hit one of them is 3 / 6 = 0.53/6=0.5.
In the second case, all 44 cells contain battleships, resulting in a probability of 1.01.0 of hitting a battleship.
*/

#include "../standardHeaders.h"
#define SIZE 3

double getHitProbability(int R, int C, int** G) {
  // Write your code here
  double totalCells = R*C;
  double totalBattleships = 0;
  for(int i=0; i<R; i++) {
    for(int j=0; j<C; j++) {
      if(G[i][j] == 1) totalBattleships++;
    }
  }
  if(totalBattleships == 0) return 0;
  return (totalBattleships/totalCells);
}

int main(void) {

    int d[][SIZE][SIZE] = {{{0,1,1}, {0,1,1}, {0,1,1}}, {{0,1,1}, {0,1,1}, {0,1,1}}, {{1,1,1}, {1,1,1}, {1,1,1}}};
    int** C = (int **)malloc(SIZE * sizeof(int));
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            C[i][j] = 0;
        }
    }
    // int** C[1] = {d};
    for(int i=0; i<SIZE; i++) {
        printf("%f\n", getHitProbability(SIZE, SIZE, C));
    }

    return 0;
}

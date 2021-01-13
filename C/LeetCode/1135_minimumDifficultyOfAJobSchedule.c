/*
You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days.
The difficulty of a day is the maximum difficulty of a job done in that day.
Given an array of integers jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

Example 1:
Input: jobDifficulty = [6,5,4,3,2,1], d = 2
Output: 7
Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7 

Example 2:
Input: jobDifficulty = [9,9,9], d = 4
Output: -1
Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.

Example 3:
Input: jobDifficulty = [1,1,1], d = 3
Output: 3
Explanation: The schedule is one job per day. total difficulty will be 3.

Example 4:
Input: jobDifficulty = [7,1,7,1,7,1], d = 3
Output: 15

Example 5:
Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
Output: 843

Constraints:

1 <= jobDifficulty.length <= 300
0 <= jobDifficulty[i] <= 1000
1 <= d <= 10
*/

#include "../standardHeaders.h"

#define MAX(A,B) ((A) > (B) ? (A) : (B))
#define MIN(A,B) ((A) < (B) ? (A) : (B))

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

int dfs(int *jobDifficulty, int jobDifficultySize, int days, int idx, int dp[][jobDifficultySize]){
    // base case
    // for last day, just find the max job difficulty, from idx upto last idx of job difficulty
    if(days == 1){
        int max = 0;
        while(idx < jobDifficultySize){
            max = MAX(max, jobDifficulty[idx]);
            idx++;
        }
        return max;
    }
    // if value is not default i.e. it has been changed in the past, just return it and save yourself computations
    if(dp[days][idx] != -1) return dp[days][idx];
    // calculate max of left side of your cut in jobDifficulty and right side of jobDifficulty
    int max = 0;
    int result = INT32_MAX;
    // start making cuts 
    int limit = jobDifficultySize-days;
    for(int i=idx; i<= limit; i++){
        max = MAX(max, jobDifficulty[i]);
        result = MIN(result, max+dfs(jobDifficulty,jobDifficultySize, days-1, i+1, dp));
    }
    return dp[days][idx] = result;
}

int minDifficultyRecursion(int* jobDifficulty, int jobDifficultySize, int d){
    if(d > jobDifficultySize)   return -1;
    int dp[d+1][jobDifficultySize];
    for(int i=0; i<d+1; i++){
        for(int j=0; j<jobDifficultySize; j++){
            dp[i][j] = -1;
        }
    }
    return dfs(jobDifficulty, jobDifficultySize, d, 0, dp);
}
/**********************************************************************************************/


/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/
int minDifficultyNonRecursion(int* jobDifficulty, int jobDifficultySize, int d){
    int n = jobDifficultySize;
    if (d > n) return -1;
    // take an array of size day+1 and jobSizes+1
    int F[d+1][n+1];
    for(int i=0; i<=d; i++){
        for(int j=0; j<=n; j++){
            F[i][j] = 0;
        }
    }
    // FIRST DAY CALCULATIONS (base case calculations):
    // find maximum job difficulty from 0th index upto ith index
    // note: you can only have maximum difficulty of a job at ith index from 0 to i-1th index
    // this is due to the given requirement that for ith job to be completed, all 0 to i-1th job should be completed first
    // you can also think of this as making just 1 cut in jobDifficulty array and finding maximum on the left hand side of your cut and storing it at your current location, to be used for in future
    for (int i = 1; i <= n; i++){
        // find max between previous max and current value
        F[1][i] = MAX(F[1][i-1], jobDifficulty[i-1]);
    }

    // start by making at least 2 cuts, go upto d cuts (since we start with 1 and not 0)
    for (int i = 2; i <= d; i++) {
        // make all possible cuts from 2 until n
        for (int j = i; j <= n; j++) {
            // assume result is MAXIMUM, so we can replace it with first minimum we find
            F[i][j] = INT32_MAX;
            int currMax = 0;
            // go from j until i
            for (int k = j; k >= i; k--) {
                currMax = MAX(currMax, jobDifficulty[k-1]);
                F[i][j] = MIN(F[i][j], F[i-1][k-1] + currMax);
            }
        }
    }
    return F[d][n];
}
/**********************************************************************************************/

/*
[1,2,3,4]
2
[3,4,5,6,1,2,3]
3
[9,9,9]
4
[1,1,1]
3
*/
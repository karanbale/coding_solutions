/*
There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:

Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
Every worker in the paid group must be paid at least their minimum wage expectation.
Return the least amount of money needed to form a paid group satisfying the above conditions.

 

Example 1:

Input: quality = [10,20,5], wage = [70,50,30], K = 2
Output: 105.00000
Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
Example 2:

Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
Output: 30.66667
Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately. 
 

Note:

1 <= K <= N <= 10000, where N = quality.length = wage.length
1 <= quality[i] <= 10000
1 <= wage[i] <= 10000
Answers within 10^-5 of the correct answer will be considered correct.
*/

/*
######################################################################################################################
Input: quality = [10,20,5], wage = [70,50,30], K = 2

ans = INT32_MAX
factor = wage/quality = 7, 2.5, 6
prices.append( if((factor*quality[worker]) >= wage[worker]) )

worker1 relative price: 70, 140, 35
prices = len([70, 140, 35]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(INT32_MAX, sum([35, 70])) = 105.00000

worker2 relative price: 25, 50, 12.5
prices = len([50]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
continue, no answer

worker3 relative price: 60, 120, 30
prices = len([120, 30]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(105.00000, sum([30,120])) = 105.0000000

######################################################################################################################

######################################################################################################################
Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3

ans = INT32_MAX
factor = wage/quality = 1.33, 8, 0.2, 0.2, 7
prices.append( if((factor*quality[worker]) >= wage[worker]) )

worker1 relative price: 4, 1.33, 13.3, 13.3, 1.33
prices = len([4, 13.3, 13.3]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(INT32_MAX, sum([4, 13.3, 13.3])) = 30.6

worker2 relative price: 24, 8, 80, 80, 8
prices = len([24, 8, 80, 80, 8]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([8, 8, 24])) = 30.6

worker3 relative price: 0.6, 0.2, 2, 2, 0.2
prices = len([2, 2]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
continue, no answer

worker4 relative price: 0.6, 0.2, 2, 2, 0.2
prices = len([2, 2]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([2, 2])) = 30.6

worker5 relative price: 21, 7, 70, 70, 7
prices = len([21, 70, 70, 7]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([7, 70, 70])) = 30.6

######################################################################################################################

*/

/*
######################################################################################################################
Input: quality = [10,20,5], wage = [70,50,30], K = 2

ans = INT32_MAX
factor = wage/quality = 7, 2.5, 6
prices.append( if((factor*quality[worker]) >= wage[worker]) )

worker1 relative price: 70, 140, 35
prices = len([70, 140, 35]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(INT32_MAX, sum([35, 70])) = 105.00000

worker2 relative price: 25, 50, 12.5
prices = len([50]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
continue, no answer

worker3 relative price: 60, 120, 30
prices = len([120, 30]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(105.00000, sum([30,120])) = 105.0000000

######################################################################################################################

######################################################################################################################
Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3

ans = INT32_MAX
factor = wage/quality = 1.33, 8, 0.2, 0.2, 7
prices.append( if((factor*quality[worker]) >= wage[worker]) )

worker1 relative price: 4, 1.33, 13.3, 13.3, 1.33
prices = len([4, 13.3, 13.3]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(INT32_MAX, sum([4, 13.3, 13.3])) = 30.6

worker2 relative price: 24, 8, 80, 80, 8
prices = len([24, 8, 80, 80, 8]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([8, 8, 24])) = 30.6

worker3 relative price: 0.6, 0.2, 2, 2, 0.2
prices = len([2, 2]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
continue, no answer

worker4 relative price: 0.6, 0.2, 2, 2, 0.2
prices = len([2, 2]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([2, 2])) = 30.6

worker5 relative price: 21, 7, 70, 70, 7
prices = len([21, 70, 70, 7]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([7, 70, 70])) = 30.6

######################################################################################################################

*/

/*
######################################################################################################################
Input: quality = [10,20,5], wage = [70,50,30], K = 2

ans = INT32_MAX
factor = wage/quality = 7, 2.5, 6
prices.append( if((factor*quality[worker]) >= wage[worker]) )

worker1 relative price: 70, 140, 35
prices = len([70, 140, 35]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(INT32_MAX, sum([35, 70])) = 105.00000

worker2 relative price: 25, 50, 12.5
prices = len([50]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
continue, no answer

worker3 relative price: 60, 120, 30
prices = len([120, 30]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(105.00000, sum([30,120])) = 105.0000000

######################################################################################################################

######################################################################################################################
Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3

ans = INT32_MAX
factor = wage/quality = 1.33, 8, 0.2, 0.2, 7
prices.append( if((factor*quality[worker]) >= wage[worker]) )

worker1 relative price: 4, 1.33, 13.3, 13.3, 1.33
prices = len([4, 13.3, 13.3]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(INT32_MAX, sum([4, 13.3, 13.3])) = 30.6

worker2 relative price: 24, 8, 80, 80, 8
prices = len([24, 8, 80, 80, 8]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([8, 8, 24])) = 30.6

worker3 relative price: 0.6, 0.2, 2, 2, 0.2
prices = len([2, 2]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
continue, no answer

worker4 relative price: 0.6, 0.2, 2, 2, 0.2
prices = len([2, 2]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([2, 2])) = 30.6

worker5 relative price: 21, 7, 70, 70, 7
prices = len([21, 70, 70, 7]) < K ? continue : sort(prices) & find min(sum[prices[:k]], ans)
ans = min(30.6, sum([7, 70, 70])) = 30.6

######################################################################################################################

*/

#include "../../include/MaxHeap/MaxHeap_Header.h"
#include "../common_utils/common.h"
#include "../common_utils/heap.h"

typedef struct worker {
    int quality;
    int wage;
    double wageToQualityRatio;
}worker_t;

void printArr1(worker_t *member, int numOfWorkers) {
    for (int i = 0; i < numOfWorkers; i++){
        TM_PRINTF("%d. Worker quality: %d\n", i, member[i].quality);
        TM_PRINTF("%d. Worker Wage.  : %d\n", i, member[i].wage);
        TM_PRINTF("%d. Worker ratio  : %f\n", i, member[i].wageToQualityRatio);
        TM_PRINTF("\n");
    }
}

void get_dp(worker_t *arr, int qualitySize, int kNumOfWorkers, int *dp) {
    if (kNumOfWorkers == 0)
        return;
    heap_t *h = createHeap((kNumOfWorkers + 1), true);
    int sum = 0;
    // add K-1 workers with minimum wageToQualityRatio to temp heap
    // Note: our members are already sorted as per their wageToQualityRatio, from highest to lowest
    // thus lets just focus on (K-1) workers with minimum wageToQualityRatio
    for (int i = qualitySize - kNumOfWorkers; i < qualitySize ; i++) {
        TM_PRINTF("inserting wage: %d, quality: %d, ratio: %f\n", arr[i].wage, arr[i].quality, arr[i].wageToQualityRatio);
        insertHeap(h, arr[i].quality);
        sum += arr[i].quality;
    }
    TM_PRINTF("final sum: %d\n\n",sum);
    // assign the sum of minimum wageToQualityRatio to dp's last index
    dp[qualitySize - kNumOfWorkers] = sum;
    
    // iterate over remaining member structures from top to bottom (reverse order)
    // we iterate over workers, who were not added to heap in above step
    for (int i = qualitySize - kNumOfWorkers - 1; i >= 0; i--) {
        TM_PRINTF("Considering: %d\n", arr[i].quality);
        // if we find a worker in the heap whose quality is bigger than current, lets remove it 
        // and lets add this new worker
        if (arr[i].quality < peekHeap(h)){
            int poppedItem = removeHeap(h);
            TM_PRINTF("Popped item: %d\n", poppedItem);
            sum = sum - poppedItem;
            sum = sum + arr[i].quality;
            insertHeap(h, arr[i].quality);
        }
        dp[i] = sum;
    }
    destroyHeap(h);
}

int cmpW(const void * a, const void * b) {
    double temp = ((worker_t *)b)->wageToQualityRatio - ((worker_t *)a)->wageToQualityRatio;
    if (temp < 0)
        return -1;
    return 1;
}

double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int K) {
    if (qualitySize == 1)
        return wage[0];
    // initialize member structure
    worker_t * member = (worker_t *) malloc(sizeof(worker_t) * qualitySize);
    for (int i = 0; i < qualitySize; i++){
        member[i].quality = quality[i];
        member[i].wage = wage[i];
        member[i].wageToQualityRatio = (double)wage[i] / quality[i];
    }

    printArr1(member, qualitySize);

    // sort member array, based upon wageToQualityRatio
    qsort(member, qualitySize, sizeof(worker_t), cmpW);
    TM_PRINTF("POST SORTING....\n\n");
    printArr1(member, qualitySize);

    double result = INT32_MAX, cost;
    int dp[qualitySize];
    get_dp(member, qualitySize, K-1, dp);

    for(int i=0; i<qualitySize; i++){
        TM_PRINTF("dp[%d]: %d ",i, dp[i]);
    }
    TM_PRINTF("\n");
    // now iterate over each member
    for (int i = 0; i <= qualitySize - K; i++){
        int total = member[i].quality;
        if (K != 1)
            total += dp[i + 1];
        cost = total * member[i].wageToQualityRatio;
        TM_PRINTF("current cost: %f\n", cost);
        result = fmin(result, cost);
    }
    free(member);
    return result;
}


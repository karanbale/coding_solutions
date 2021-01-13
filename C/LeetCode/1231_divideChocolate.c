/*
You have one chocolate bar that consists of some chunks. 
Each chunk has its own sweetness given by the array sweetness.
You want to share the chocolate with your K friends so you start cutting the chocolate bar into K+1 pieces using K cuts, 
each piece consists of some consecutive chunks.
Being generous, you will eat the piece with the minimum total sweetness and 
give the other pieces to your friends.

Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.

Example 1:
Input: sweetness = [1,2,3,4,5,6,7,8,9], K = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]

Example 2:
Input: sweetness = [5,6,7,8,9,1,2,3,4], K = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.

Example 3:
Input: sweetness = [1,2,2,1,2,2,1,2,2], K = 2
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]
 

Constraints:

0 <= K < sweetness.length <= 10^4
1 <= sweetness[i] <= 10^5
*/

#include "../standardHeaders.h"

int getSum(int *sweetness, int sweetnessSize){
    int count = 0;
    for(int i=0; i<sweetnessSize; i++){
        count += sweetness[i];
    }
    return count;
}

int getMinSweetness(int *sweetness, int sweetnessSize){
    int minSweetness = 0;
    for(int i=0; i<sweetnessSize; i++){
        if(minSweetness > sweetness[i]){
            minSweetness = sweetness[i];
        }
    }
    return minSweetness;
}

int maximizeSweetnessSolution1(int* sweetness, int sweetnessSize, int K){
    int minimumSweetness, medianSweetness;
    minimumSweetness = 1;
    // find median sweetness per person
    // our target sweetness level is going to be in and around this median sweetness
    medianSweetness = getSum(sweetness, sweetnessSize)/(K+1);
    
    while(minimumSweetness <= medianSweetness){
        // find currentSweetnessLevel in the range from minimumSweetness to medianSweetness
        int currentSweetnessLevel = (minimumSweetness + medianSweetness)/2;
        // printf("currentSweetnessLevel: %d, medianSweetness:%d\n",currentSweetnessLevel, medianSweetness);
        
        // current sweetness sum and number of cuts
        int currentSweetnessSum = 0, chocolateCuts = 0;
        
        // iterate over sweetness levels and calculate total sweetness
        // untilwe hit a sweet spot, that is just below our target median value
        for(int i=0; i<sweetnessSize; i++){
            currentSweetnessSum += sweetness[i];
            // printf("cuts: %d, currentSweetnessSum: %d\n", chocolateCuts, currentSweetnessSum);
            // if sum of sweetness exceeds the currentSweetnessLevel, stop and cut the chocolate
            if(currentSweetnessSum >= currentSweetnessLevel){
                chocolateCuts++;
                currentSweetnessSum = 0;
            }
            // if number of cuts more than number of shares, stop
            if(chocolateCuts > K)   break;
        }
        
        // if there are more cuts than number of friends, our sweetnessLevel is low
		// search for a higher sweetness with less cuts
        if(chocolateCuts > K){
            minimumSweetness = currentSweetnessLevel+1;
        }
        // if there are less cuts than number of friends, our sweetness is too high
		// search for a lower sweetness with more cuts
        else{
            medianSweetness = currentSweetnessLevel - 1;
        }
    }
    
    // at the end of our binary search, we will have converged on a sweetness level
	// which will have K cuts yield medianSweetness as a lower bound
	// this will be the chunk that you eat
    return medianSweetness;
}

int maximizeSweetness(int* sweetness, int sweetnessSize, int K){
    int minimumSweetness, totalSweetness;
    minimumSweetness = getMinSweetness(sweetness, sweetnessSize);
    // find median sweetness per person
    // our target sweetness level is going to be in and around this median sweetness
    totalSweetness = getSum(sweetness, sweetnessSize);
    
    while(minimumSweetness < totalSweetness){
        // find currentSweetnessLevel in the range from minimumSweetness to totalSweetness
        int currentSweetnessLevel = (minimumSweetness + totalSweetness)/2;
        // printf("currentSweetnessLevel: %d, totalSweetness:%d\n",currentSweetnessLevel, totalSweetness);
        
        // current sweetness sum and number of cuts
        int currentSweetnessSum = 0, chocolateCuts = 0;
        
        // iterate over sweetness levels and calculate total sweetness
        // untilwe hit a sweet spot, that is just below our target median value
        for(int i=0; i<sweetnessSize; i++){
            currentSweetnessSum += sweetness[i];
            // printf("cuts: %d, currentSweetnessSum: %d\n", chocolateCuts, currentSweetnessSum);
            // if sum of sweetness exceeds the currentSweetnessLevel, stop and cut the chocolate
            if(currentSweetnessSum > currentSweetnessLevel){
                chocolateCuts++;
                currentSweetnessSum = 0;
            }
            // if number of cuts more than number of shares, stop
            if(chocolateCuts > K)   break;
        }
        
        // if there are more cuts than number of friends, our sweetnessLevel is low
		// search for a higher sweetness with less cuts
        if(chocolateCuts > K){
            minimumSweetness = currentSweetnessLevel+1;
        }
        // if there are less cuts than number of friends, our sweetness is too high
		// search for a lower sweetness with more cuts
        else{
            totalSweetness = currentSweetnessLevel;
        }
    }
    
    // at the end of our binary search, we will have converged on a sweetness level
	// which will have K cuts yield totalSweetness as a lower bound
	// this will be the chunk that you eat
    return totalSweetness;
}
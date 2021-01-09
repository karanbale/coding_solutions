/*
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
        if(minSweetness < sweetness[i]);
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
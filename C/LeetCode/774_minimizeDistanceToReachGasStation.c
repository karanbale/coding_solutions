/*
On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.
Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.
Return the smallest possible value of D.

Example:
Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
Output: 0.500000
Note:

stations.length will be an integer in range [10, 2000].
stations[i] will be an integer in range [0, 10^8].
K will be an integer in range [1, 10^6].
Answers within 10^-6 of the true value will be accepted as correct.
*/

#include "../standardHeaders.h"

double minmaxGasDist(int* stations, int stationsSize, int K){
    // left is 0 because, first gas station is at distance 0 from it self
    // we cannot take the distance between first two gas stations as left, since 
    // that distance is not guaranteed to be the minimum in the array
    // e.g. if array is like 1,6,7,8,9 then first distance is obviously not the smallest
    double left = 0;
    // right is the maximum distance between two farthest place gas stations
    // I'm making an assumption that given array is sorted, so this works, but if given array 
    // is not sorted, we need to sort it and find distance between first and last gas station
    double right = stations[stationsSize-1] - stations[0];
    
    // we need to add 1e-6 as precision to left, since answer can be upto 6 locations after decimal
    while((left+(1e-6)) < right){
        // take a guess
        // between left and right, start with their mid as the guess
        double mid = left+(right-left)/2;
        double numberOfGasStationsAdded = 0;
        for(int i=0; i<stationsSize-1; i++){
            // distance between two gas stations is (stations[i+1] - stations[i])
            // we need to place one or more gas station in between these two stations and minimize the distance between them
            // lets divide this current distance (stations[i+1] - stations[i]), by our guess and take ceil of the answer
            // ceil will return the smallest integer that is greater than or equal to x, where x is the integer being passed
            // e.g. ceil(1.6) returns 1.600000
            // keep the count of all the distances calculated using our guess
            numberOfGasStationsAdded += ceil((stations[i+1]-stations[i])/mid)-1;
        }
        // if number of gas stations required to minimize the distances are more than given K gas stations
        // then we know, our guess was too small, thus we need to increase our guess
        // the guess we take and the number of gas stations required (those we calculated in for loop), are inversely proportional
        // dividing by smaller guess value will yield more gas stations and
        // dividing by larger guess value will yeild less gas stations
        // thus, for number of gas stations > K, we need to increase our guess so we can have less gas stations
        if(numberOfGasStationsAdded > K) left = mid;
        // thus, for number of gas stations <= K, we need to reduce our guess so we can have more gas stations
        else right = mid;
    }
	// return either left or right, doesn't matter, since we will end up with left = right at the end
    return left;
}
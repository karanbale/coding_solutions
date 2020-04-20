/*
When migrating data from a source storage system to a target storage system, 
the number one focus is avoiding data corruption at all cost. 
In order to meet these high standards, various rounds of tests are run checking for corrupted blocks,
as well as successfully migrated lengthy regions.
We are going to represent the source storage system and target storage system as sequential arrays,
 sourceArray and destinationArray respectively, where sourceArray[i] represents binary data 
 of the ith source block as an integer, and destinationArray[i] represents binary data 
 of the ith destination block, where the data should be migrated, also as an integer. 
 Given the content of the source and the migrated content of the target, 
 find the length and the starting block of the longest uncorrupted data segment (segment = subsequent blocks).

If there is no uncorrupted segment, return an array containing 0 and 0 respectively.

Example

For sourceArray = [33531593, 96933415, 28506400, 39457872, 29684716, 86010806] and 
destinationArray = [33531593, 96913415, 28506400, 39457872, 29684716, 86010806], 
the output should be
longestUncorruptedSegment(sourceArray, destinationArray) = [4, 2].

The only corrupted element is located by index 1, where 
sourceArray[1] = 96933415 != 96913415 = destinationArray[1], 
all other data blocks were transfered uncorrupted. 
So the longest uncorrupted segment starts on second index and goes to the end of the array, thus having length 4.

Input/Output

[execution time limit] 0.5 seconds (c)

[input] array.integer sourceArray

The source data as sequential array.

Guaranteed constraints:
1 ≤ sourceArray.length ≤ 105,
107 ≤ sourceArray[i] < 108.

[input] array.integer destinationArray

The migrated data as sequential array.

Guaranteed constraints:
destinationArray.length = sourceArray.length,
107 ≤ destinationArray[i] < 108.

[output] array.integer

An array of two elements - first is the length of the longest uncorrupted data segment and second is the starting block.

Input 1:
sourceArray: [33531593, 96933415, 28506400, 39457872, 29684716, 86010806]
destinationArray: [33531593, 96913415, 28506400, 39457872, 29684716, 86010806]
Expected output: 
[4, 2]

Input 2:
sourceArray: [10000000]
destinationArray: [99999999]
Expected Output:
[0, 0]

Input 3:
sourceArray: [20800440, 98256958, 64277103, 40475664, 98589505, 31621824, 84322264, 58283379, 15631261, 35464021]
destinationArray: [20800440, 95256958, 64276103, 40475664, 98589505, 31621824, 84322264, 58283379, 15631261, 35464021]
Expected Output:
[7, 3]

Input 4:
sourceArray: [92988800, 80253955, 17396563, 91682092, 77708269, 97587946, 23889892, 20661856, 21013095, 92028000, 
17562863, 86804822, 17819093, 97941923, 64955308]
destinationArray: [92988800, 80253955, 17396563, 91682092, 77708229, 97587946, 23889892, 20661866, 21013095, 
92928000, 17962863, 86804822, 14819093, 97241923, 62955308]
Expected Output:
[4, 0]

Input 5:
sourceArray: [99919628, 77504204, 18846830, 86785029, 86230362, 96953294, 53208680, 95327090, 68996760, 26366538, 
90490275, 62583792, 87514087, 96921389, 21309822]
destinationArray: [99919628, 77503204, 18546830, 86785029, 86230362, 96953264, 53208680, 95327090, 68996760, 
26366538, 90420275, 62583792, 87514087, 39692139, 21303822]
Expected Output:
[4, 6]

*/

#include "../../C/standardHeaders.h"

typedef struct {
int size;
int *arr;
} arr_integer;


arr_integer longestUncorruptedSegment(arr_integer sourceArray, arr_integer destinationArray) {
    printf("size: %d\n",destinationArray.arr);

    arr_integer returnData;
    returnData.size = 2;
    int *arr = malloc(sizeof(int)*returnData.size);
    returnData.arr = arr;
    
    if(sourceArray.size != destinationArray.size) return returnData;
    int count = 0, newIndex = 1, currIdx=0;
    for(int i=0; i< sourceArray.size; i++){
        if(sourceArray.arr[i] == destinationArray.arr[i]){
            // printf("%d %d\n", sourceArray.arr[i],destinationArray.arr[i]);
            ++count;
            if(newIndex){
                currIdx = i;
                newIndex = 0;
            }
        }
        else {
            // for each data mis-match, check if count needs to be 
            // updated 
            if(count > returnData.arr[0]){
                returnData.arr[0] = count;
                returnData.arr[1] = currIdx;
            }
            count = 0;
            newIndex = 1;
        }
    }

    // handle the condition where you match until end of the array
    // in that case we need to update returnData
    if(count > returnData.arr[0]){
        returnData.arr[0] = count;
        returnData.arr[1] = currIdx;
    }
    return returnData;
}

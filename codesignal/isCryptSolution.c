/*

A cryptarithm is a mathematical puzzle for which the goal is to find the correspondence between letters and digits, 
such that the given arithmetic equation consisting of letters holds true when the letters are converted to digits.

You have an array of strings crypt, the cryptarithm, and an an array containing the mapping of letters and digits, solution. 
The array crypt will contain three non-empty strings that follow the structure: [word1, word2, word3], 
which should be interpreted as the word1 + word2 = word3 cryptarithm.

If crypt, when it is decoded by replacing all of the letters in the cryptarithm with digits using the mapping in solution, 
becomes a valid arithmetic equation containing no numbers with leading zeroes, the answer is true. 
If it does not become a valid arithmetic solution, the answer is false.

Note that number 0 doesn't contain leading zeroes (while for example 00 or 0123 do).

Example

For crypt = ["SEND", "MORE", "MONEY"] and

solution = [['O', '0'],
            ['M', '1'],
            ['Y', '2'],
            ['E', '5'],
            ['N', '6'],
            ['D', '7'],
            ['R', '8'],
            ['S', '9']]
the output should be
isCryptSolution(crypt, solution) = true.

When you decrypt "SEND", "MORE", and "MONEY" using the mapping given in crypt, you get 9567 + 1085 = 10652 which is correct and a valid arithmetic equation.

For crypt = ["TEN", "TWO", "ONE"] and

solution = [['O', '1'],
            ['T', '0'],
            ['W', '9'],
            ['E', '5'],
            ['N', '4']]
the output should be
isCryptSolution(crypt, solution) = false.

Even though 054 + 091 = 145, 054 and 091 both contain leading zeroes, meaning that this is not a valid solution.

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef struct {
int size;
char *arr[];
} arr_string;

typedef struct {
int size;
arr_string *arr;
} arr_arr_char;

arr_arr_char alloc_arr_arr_integer(int len) {
  arr_arr_char a = {len, len > 0 ? malloc(sizeof(arr_string) * len) : NULL};
  return a;
}

long myatoi(const char* str){
    long res = 0;
    // for all leading '0's in the str, 
    // just return 0, since equation is false anyway
    if(str[0] == '0'){
        return res;
    }
    for(int i=0; str[i] != '\0'; ++i){
        res = res*10 + str[i] - '0';
    }
    return res;
}

int get_char_int(const arr_arr_char solution, const char * letter){
    for(int i=0; i<solution.size; i++){
        if(solution.arr[i].arr[0] == letter){
            //printf("sol: %c\t", solution.arr[i].arr[1]);
            return *solution.arr[i].arr[1];
        }
    }
    return '0';
}

bool isCryptSolution(arr_string crypt, arr_arr_char solution) {
    // take long as sum, since some hidden tests have long ints
    long sum[crypt.size];
    
    // form numbers using digit to letters mapping given in solution
    for(int i=0; i<crypt.size; i++){
        int char_len = strlen(crypt.arr[i]);
        char dst[char_len];
        for(int j=0; crypt.arr[i][j]!='\0'; j++){
            dst[j] = get_char_int(solution, &crypt.arr[i][j]);
            dst[j+1] = '\0';
        }
        // following condition takes care of the note given in problem
        // if there is a leading 0, its invalid equation however
        // if it is just 0, it is still valid equation 
        // since 0 does not have leading 0 to it
        if(dst[0] == '0' && strlen(dst) > 1){
            printf("returning False");
            return false;
        }
        sum[i] = myatoi(dst);
        //printf("\nword: %s sum: %d str_sum:%s len:%d\n",crypt.arr[i],sum[i], dst, strlen(dst));
        //printf("\nword: %s sum: %s atoi:%d\n",crypt.arr[i],dst,myatoi(dst));
    }

    // take long as sum, since some hidden tests have long ints
    long total_sum = 0;

    // iteratively calculat the sum, except last idex
    for(long i=0; i<crypt.size-1; i++){
        printf("\nword: %s sum: %ld\n", crypt.arr[i], sum[i]);
        total_sum += sum[i];
    }
    // printf("\nTotal Sum: %d Last sum: %d", total_sum, sum[crypt.size-1]);

    return (total_sum == sum[crypt.size - 1]);    
}


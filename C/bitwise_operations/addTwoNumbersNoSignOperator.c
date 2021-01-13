/*
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:
Input: a = 1, b = 2
Output: 3

Example 2:
Input: a = -2, b = 3
Output: 1

Following solution was obtained from:
https://leetcode.com/problems/sum-of-two-integers/discuss/573229/c-0ms-one-line-address-ofsubscript-operators-simple-and-short/502214
*/

#include "../standardHeaders.h"

/*
Here, &((char *)a)[b] is nothing but (a + b) since address-of and subscript operations when applied together,
results in no-op and sizeof(char) == 1. 
So, for anyone who might be wondering, there is no illegal memory dereference here.
The only integer types that can correctly represent a generic pointer in C is uintptr_t and intptr_t. 
Thus we need to type cast given integer to uintptr_t -> void * -> char * to access 1 byte of the address.
Rest of the casting in below solution is for portability and correctness.
*/

int getSum_Method1(int a, int b){
    return (uintptr_t)&((char *)(void *)(uintptr_t)a)[b];
    // return (uintptr_t)&((char *)(void *)(uintptr_t)a)[b]; 
}

int getProd(int a, int b){
    return (uintptr_t)&((char (*) [a])0x0)[b];
}

/*
return printf("%*c%*c",  x, ' ',  y, ' ');
The * in the printf format means that the field width used to print the character is taken from an argument of printf, 
in this case, x and y. The return value of printf is the number of characters printed. 
So it's printing one ' ' with a field-width of x, and one with a field-width of y, makes x + y characters in total.

In other words:
return printf("%*c%*c",  x, ' ',  y, ' ');

Well what happens in above return statement this: 
the * before c tells printf that:
The width of argument is not specified in the format string, but as an additional integer value argument, which is, 
preceding the argument, that has to be formatted.

Hence this means that the first space character will be printed with a width of x and the second one with a width of y. 
At the same time printf returns the number of characters printed, which is actually a + b characters.

*/
int getSum_Method2(int a, int b){
    return printf("%*c%*c",a,' ',b,' '); 
}

/*
we can simply add two numbers using Full adder logic from Digital Electronics class.
Truth Table for a full adder looks like this:

A   B   Cin     Sum     Carry
0   0    0       0       0
0   0    1       1       0
0   1    0       1       0
0   1    1       0       1
1   0    0       1       0
1   0    1       0       1
1   1    0       0       1
1   1    1       1       1

From above truth table we can deduce Sum and Carry in terms of (A, B, Cin) as following:
Sum   = Cin.A'.B' + B.A'.Cin' + A.B'.Cin' + A.B.Cin
      = Cin(A'.B'+A.B) + Cin'(A'.B + B'.A)
      = Cin XOR (A XOR B)

Carry = A'.B.Cin + A.B'.Cin + A.B.Cin' + A.B.Cin
      = A.B + B.Cin + A.Cin

*/
int getSum_FullAdder_Method3(int a, int b){
    int carry_bit = 0, sum = 0;
    for(int i=0; i<32; i++){
        int a_bit = (a >> i)&1 ;
        int b_bit = (b >> i)&1 ;
        sum |= (((a_bit ^ b_bit) ^ carry_bit)<<i);
        carry_bit = ((a_bit & b_bit) | (a_bit & carry_bit) | (b_bit & carry_bit));
    }

    return sum;
}

/*
we can simply add two numbers using 1-bit half adder logic from Digital Electronics class.
Truth Table for a full adder looks like this:

A   B     Sum     Carry
0   0      0       0
0   1      1       0
1   0      1       0
1   1      0       1

From above truth table we can deduce Sum and Carry in terms of (A, B, Cin) as following:
Sum   = A'.B + A.B'     
      = A XOR B

Carry = A.B

*/
int getSum_HalfAdder_Method3(int a, int b){    
    while(b){
        int carry_bit = (a & b);
        a = (a ^ b);
        b = (carry_bit << 1) ;
    }

    return a;
}

int main(void){

    int nums[4] = {1,2,INT32_MAX,INT32_MIN};
    for (int i = 0; i < 4; i=i+2)
    {
        printf("Sum of a: %d, b: %d is:\n",nums[i],nums[i+1]);
        printf("Method 1: %d\n",getSum_Method1(nums[i], nums[i+1]));
        printf("Method 2: %d\n",getSum_Method2(nums[i], nums[i+1]));
        printf("Method 3: %d\n",getSum_FullAdder_Method3(nums[i], nums[i+1]));
        printf("\n");
    }
    return 0;
}

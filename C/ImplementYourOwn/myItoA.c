/*

*/

#include "../standardHeaders.h"

void swap(char *idx1, char *idx2){
    char temp = *idx1;
    *idx1 = *idx2;
    *idx2 = temp;
}

/* A utility function to reverse a string  */
void reverse(char str[], int start, int end)
{
    while (start < end)
    {
        swap(&str[start++], &str[end--]);
    }
}

// Implementation of itoa()
char* my_itoa(int num, char* str, int base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return str;
    }

    int i = 0;
    bool isNegative = false;
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
  
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
  
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
  
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
  
    str[i] = '\0'; // Append string terminator
  
    // Reverse the string
    reverse(str, 0, i-1);
  
    return str;
}

int main(void) {
    char str[100];
    printf("1567: %s\n", my_itoa(1567, str, 10));
    printf("-1567: %s\n", my_itoa(1567, str, 10));
    printf("1567: %s\n", my_itoa(1567, str, 2));
    printf("1567: %s\n", my_itoa(1567, str, 8));
    printf("1567: %s\n", my_itoa(1567, str, 16));

    my_itoa(1567, str, 10);
    assert(strcmp(str, "1567") == 0);
    my_itoa(-1567, str, 10);
    assert(strcmp(str, "-1567") == 0);
    my_itoa(1567, str, 2);
    assert(strcmp(str, "11000011111") == 0);
    my_itoa(1567, str, 8);
    assert(strcmp(str, "3037") == 0);
    my_itoa(1567, str, 16);
    assert(strcmp(str, "61f") == 0);
    return 0;
}
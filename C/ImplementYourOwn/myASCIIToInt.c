#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static bool isNumericVal(const char *ptr) {
        return (*ptr >= '0' && *ptr <= '9') ? true : false;
}

size_t myAtoI(const char *ptr, int base) {
        
        // ignore white spaces
        while(*ptr == ' ') ptr++;
        
        // sign
        int sign = 1;
        if((*ptr == '-') || (*ptr == '+')) {
                sign = 1 - 2 * (*ptr == '-');
                ptr++;
        }
        
        size_t retNum = 0;
        
        // base case
        while(isNumericVal(ptr)) {
                // handle overflow condition
                if ((retNum > (INT32_MAX/10)) || ((retNum == (INT32_MAX/10)) && (*ptr - '0' > 7))) {
                        if(sign == 1) return INT32_MAX;
                        else return INT32_MIN;
                }
                retNum = (retNum * base) + (*ptr - '0');
                ptr++;
        }
        
        return retNum * sign;
}

int main()
{
    printf("Hello World\n");
    printf("num_str: %s, num_int: %ld\n", " 1001", myAtoI(" 1001", 2));
    printf("num_str: %s, num_int: %ld\n", "1001", myAtoI("1001", 2));
    printf("num_str: %s, num_int: %ld\n", "1001", myAtoI("1001", 10));
    printf("num_str: %s, num_int: %ld\n", "2147483649", myAtoI("2147483649", 10));
    printf("num_str: %s, num_int: %ld\n", "-2147483649", myAtoI("-2147483649", 10));
    printf("num_str: %s, num_int: %ld\n", "-1001", myAtoI("-1001", 10));
    printf("num_str: %s, num_int: %ld\n", "1001", myAtoI(" 1001a ", 10));
    printf("num_str: %s, num_int: %ld\n", "1001", myAtoI(" -1001a ", 16));
    printf("num_str: %s, num_int: %ld\n", "1001", myAtoI("1001", 16));
    printf("num_str: %s, num_int: %ld\n", "1001", myAtoI(" 1001a ", 16));

    return 0;
}

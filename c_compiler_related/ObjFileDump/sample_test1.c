/* testprog1.c */

#include <stdint.h>
#include <stdio.h>

static void display(int i, int *ptr);

int main(void)

{

      int x = 5;

      int *xptr = &x;

      printf("In main() program:\n");

      printf("x value is %d and is stored at address %p.\n", x, &x);

      printf("xptr pointer points to address %p which holds a value of %d.\n", xptr, *xptr);

    `  display(x, xptr);

      return 0;

}

void display(int y, int *yptr)

{

      char var[7] = "ABCDEF"; 

      printf("In display() function:\n");

      printf("y value is %d and is stored at address %p.\n", y, &y);

      printf("yptr pointer points to address %p which holds a value of %d.\n", yptr, *yptr);

}


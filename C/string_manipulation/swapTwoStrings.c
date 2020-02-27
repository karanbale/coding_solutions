

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>


void swap_arr(char *str1, char *str2){
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
}

void swap_str(char **str1, char **str2){
  char *temp = *str1;
  *str1 = *str2;
  *str2 = temp;
}

int main() 
{ 
  char *str1 = "geeks"; 
  char *str2 = "forgeeks";
  char str3[10] = "geeks" ;
  char str4[10] = "forgeeks";

  printf("str1 is %s, str2 is %s\n", str1, str2); 
  swap_str(&str1, &str2); 
  printf("str1 is %s, str2 is %s\n", str1, str2); 

  printf("str3 is %s, str4 is %s\n", str3, str4); 
  swap_arr(str3, str4); 
  printf("str3 is %s, str4 is %s\n", str3, str4); 

  getchar();  
  return 0; 
} 

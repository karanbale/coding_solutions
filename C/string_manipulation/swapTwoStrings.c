

#include "../standardHeaders.h"

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

  char str5[3][10] = {};
  // print out invalid assignment
  // since we are assigning string literal (a pointer) to a constant pointer
  // NOTE: Arrays are non modifiable lvalue
  // while to assign a value, we need something that is modifiable lvalue on LHS
  printf("following assignment is invalid: str5[0] = 'jack'\n");

  *(*(str5+0)+0) = 'a';
  *(*(str5+0)+1) = '\0';
  printf("%s\n", str5[0]);

  // following assignment however is valid
  strcpy(str5[0], "jack");
  printf("%s\n", str5[0]);

  //getchar();  
  return 0; 
} 

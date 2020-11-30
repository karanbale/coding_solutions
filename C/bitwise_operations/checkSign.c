#include "utilities.h"
  
bool oppositeSigns(int x, int y) 
{ 
    printf("%d\n", x^y);
    return ((x ^ y) < 0); 
} 
  
int checkSignOfGivenNumber(void){ 
    int x = 0, y = 0; 
    if (oppositeSigns(x, y) == true) 
       printf ("Signs are opposite\n"); 
    else
      printf ("Signs are not opposite\n"); 
    return 0; 
} 

int main(void){

  checkSignOfGivenNumber();
  return 0;

}

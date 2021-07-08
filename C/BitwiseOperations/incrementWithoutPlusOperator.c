
#include "../standardHeaders.h"

// function that increment the value. 
int increment(unsigned int i) 
{ 
    // Invert bits and apply negative sign 
    i = -(~i); 
  
    return i; 
} 
  
// Driver code 
int main() 
{ 
    int n = 3; 
    printf("%d\n",increment(n)); 
    return 0; 
}

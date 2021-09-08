
#include "../standardHeaders.h"

char* ItoA(int x)
{
	int remainder;
	char Num_str[33];
	Num_str[32]='\0';
	char *ptr = &Num_str[32];
	
	do
	{
		remainder = x % 10;
		x /= 10;
		*--ptr = (unsigned char)remainder + 48; 	// Add zero(0 = 48<ASCII>) to convert in proper ASCII value			
	}while(x!=0);
	
	return (ptr);
}

int main()
{
	int i=12345;
	
	printf("%s", ItoA(i) );
	
	return 0;
}

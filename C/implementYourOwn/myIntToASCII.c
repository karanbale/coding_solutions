
#include "../standardHeaders.h"

char* ItoA(int x, char *Num_str)
{
	int remainder;
	
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
	int i=123;
	char *Num_str = (char *) malloc (sizeof(char)*33);
	char *val = ItoA(i, Num_str);
	printf("%s", val);
	free(Num_str);
	
	return 0;
}


#include "../standardHeaders.h"

void stack(int *local_1)
{
	int local_2;
	
	printf("\n Address of local_2 : [%u]", &local_2);
	
	if(local_1 < &local_2)
	{
		printf("\n\n Stack is growing downwards.\n");
	}
	else
	{
		printf("\n\n Stack is growing upwards.\n");
	}
}
 
int main( )
{
	int local_1;
	
	printf("\n Address of local_1 : [%u]", &local_1);
	
	stack(&local_1);
	
	return 0;
}

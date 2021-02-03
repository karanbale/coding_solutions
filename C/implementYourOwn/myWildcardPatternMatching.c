
#include "../standardHeaders.h"

bool WildCmp(char *pattern, char *string);
 
int main()
{
	if(WildCmp("f?rmc*","firmcodes"))
	{
			printf("! Match Found");
	}
	else
	{
			printf("! Match Not Found");
	}
	
	return 0;
}

 
bool WildCmp(char *pattern, char *string)
{
	if(*pattern=='\0' && *string=='\0')		// Check if string is at end or not.
		return true;
		
	if(*pattern=='?' || *pattern==*string)		//Check for single character missing or match
		return WildCmp(pattern+1,string+1);
		
	if(*pattern=='*')
		return WildCmp(pattern+1,string) || WildCmp(pattern,string+1);		// Check for multiple character missing
		
	return false;
}

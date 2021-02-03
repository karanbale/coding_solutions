
#include "../standardHeaders.h"

void myStrrev(void){
    char str[10],temp;
    int i,len;

    printf("Enter String : ");
    scanf("%s",str);

    len=strlen(str)-1;

    for(i=0;i<strlen(str)/2;i++)
    {
        temp=str[i];
        str[i]=str[len];
        str[len--]=temp;
    }
    printf("\nReverse string :%s",str);
}


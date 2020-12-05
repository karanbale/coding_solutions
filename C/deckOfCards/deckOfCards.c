
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
int *initialArr = NULL, *deckArr = NULL, numOfCards = 0, *superInitialArr = NULL;

int comparedecks(int *deckArrPassed)
{
	int i = 0;
	for(i = 1; i <= numOfCards; i++)
	{
		if(superInitialArr[i] != deckArrPassed[i])
			return FALSE;
	}
	return TRUE;
}

void display(int *display, char *name)
{
	int j = 0;
	printf("\n%s : ", name);
	for (j = 1; j <= numOfCards; j++)
	{
		printf("%d", deckArr[j]);
	}

}

int main(int argc, char **argv)
{
	int count = 0, index = 0, start = 1, i = 0, j = 0, ret = 0;
	if(argc >  1)
	{
		numOfCards = atoi(argv[1]);
	}
	else
	{
		printf("Enter the number of cards in a deck: Max to be 52!\n");
		scanf("%d", &numOfCards);
	}
	if(numOfCards < 1 || numOfCards > 52)
	{
		printf("Please enter a valid number in range 1 - 52 \n");
		exit(0);
	}
	initialArr = (int *) malloc ( (sizeof(int) * (numOfCards + 1)));
	deckArr = (int *) malloc ( (sizeof(int) * (numOfCards + 1)));
	superInitialArr = (int *) malloc ( (sizeof(int) * (numOfCards + 1)));
	for(i = 0; i <= numOfCards; i++)
	{
		initialArr[i] = i;
		superInitialArr[i] = i;
	}
	

	while(TRUE)
	{
		i = 0;
		index = 0;
		start = 1;
		/* Iterating over multiple of 2, 4, 8, 16 ... indexex of array */
		while (index < numOfCards)
		{
			i = start;
			while (i <= numOfCards)
			{
				deckArr[numOfCards - index] = initialArr[i];
				i += start * 2;
				index += 1;
			}
			start *= 2;
		}
		ret = comparedecks(deckArr);
		if(ret)
		{
			count++;
			break;
		}
//		display(initialArr, "Intial Array");
//		display(deckArr, "Deck Array");
		count += 1;
		free(initialArr);
		initialArr = (int *) malloc (sizeof(int) * (numOfCards + 1));
		for (j = 0; j <= numOfCards; j++)
		{
			initialArr[j] = deckArr[j];
		}
		
	}
	free(initialArr);
	free(superInitialArr);
	free(deckArr);

//	display(superInitialArr, "Super Intial Array");
//	display(deckArr, "Final Array");
	fprintf(stdout, "%d\n", count);

	return 0;
}
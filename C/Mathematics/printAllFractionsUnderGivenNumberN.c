
#include "../standardHeaders.h"

#define SIZE 100

typedef struct fractions{
	int numerator;
	int denominator;
}fractions_t;

// euclidean method
int getGCD(int numerator, int denominator){

	int remainder = 0;
	while(denominator){
		remainder = numerator % denominator;
		numerator = denominator;
		denominator = remainder;
	}
	return numerator;
}

int getLCM(int numerator, int denominator){
	int max;
	// start with the biggest numerator 
    max = (numerator > denominator) ? numerator : denominator;
    while (1) {
		// find the first biggest number that is divisible by both
		// numerator and denominator
        if (max % numerator == 0 && max % denominator == 0)
            break;
        ++max;
    }
    return max;
}

int compare(const void *a, const void *b){
    const fractions_t *f1 = *(fractions_t **)a;
    const fractions_t *f2 = *(fractions_t **)b;\
    double xx = ((double)f1->numerator/f1->denominator);
    double yy = ((double)f2->numerator/f2->denominator);\
    if(xx > yy){
        return 1;
    }
    if(xx < yy){
        return -1;
    }
    return 0;
}

fractions_t *createFractions(int numerator, int denominator){
	fractions_t *node = malloc(sizeof(fractions_t));
	assert(node != NULL);
	node->numerator = numerator;
	node->denominator = denominator;
	return node;
}

int main()
{
    printf("Hello World\n");
    fractions_t **fractionsArr = malloc(SIZE * sizeof(fractions_t *));
    assert(fractionsArr != NULL);
    int N = 5;
	int idx = 0;
	for(int i = 0; i<=N; i++){
		for(int j = 1; j<=N; j++){
			// fractional division of  j > i will not satisfy condition 1
			if((getGCD(i,j) <= 1) && (j >= i))
			{
			    fractionsArr[idx++] = createFractions(i, j);
			    if(idx >= SIZE){
				    printf("size limit reached\n");
			    }
			}
		}
	}

	qsort(fractionsArr, idx, sizeof(fractionsArr[0]), compare);

	for(int i=0; i<SIZE; i++){
		if(fractionsArr[i]){
			fractions_t *node = fractionsArr[i];
			printf("%d/%d\n",node->numerator, node->denominator);
			free(node);
		}
	}
	free(fractionsArr);
    return 0;
}

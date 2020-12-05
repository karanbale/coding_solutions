
#include "deckOfCards.h"


void printDeck(uint32_t deckNum, cardDeck_t *deckRoot){
    
    if(deckRoot == NULL){
        printf("Cannot print empty deck !\n");
        return;
    }

    card_t *tempPtr = deckRoot->head;
    while(tempPtr != NULL){
        printf("%d -> ", tempPtr->cardNum);
        tempPtr = tempPtr->next;
    }
    printf("NULL\n");
}

void freeMem(cardDeck_t *deckRoot){
    if(deckRoot == NULL){
        printf("Nothing to free !\n");
        return;
    }
    card_t *tempPtr = deckRoot->head;
    while(tempPtr != NULL){
        deckRoot->head = deckRoot->head->next;
        free(tempPtr);
        tempPtr = deckRoot->head;
    }
    free(deckRoot);
}

card_t *createCard(uint32_t cardNum, uint32_t deckNum){
    
    card_t *card = malloc(sizeof(card_t));
    
    // heap allocation success / not
    if(!card){
        return NULL;
    }

    card->cardNum = cardNum;
    card->deckNumber = deckNum;
    card->next = NULL;
    
    return card;
}

cardDeck_t *initializeDeck(uint32_t numberOfCards, bool incOrderOfCards){
    
    // Can't create a deck with 0 cards
    if(numberOfCards == 0){
        return NULL;
    }

    card_t *tempPtr = NULL;
    cardDeck_t *root = malloc(sizeof(cardDeck_t));
    
    // heap allocation success / not
    if(!root){
        return NULL;
    }

    root->numberOfCards = numberOfCards;
    root->next = NULL;
    root->head = NULL;

    for(int i = 0; i<numberOfCards; i++){
        // create card and add it to the deck, assign it to default deck
        card_t *newCard = createCard(i+1, DEFAULT_DECK);
        if(!root->head){
            root->head = newCard;
            tempPtr = newCard;
        }
        else{
            tempPtr->next = newCard;
            tempPtr = tempPtr->next;
        }
    }

    //TODO: reverse linked-list if incOrderOfCards is false

    return root;
}

int main(int argc, char **argv)
{
	int count = 0, index = 0, start = 1, i = 0, j = 0, ret = 0, numberOfCards = 0;
    cardDeck_t *deckRoot = NULL;
	if(argc >  1)
	{
		numberOfCards = atoi(argv[1]);
	}
	else
	{
		printf("Enter the number of cards in a deck: Max to be 52!\n");
	}

    // initialize deck
    deckRoot = initializeDeck(numberOfCards, false);
    printDeck(DEFAULT_DECK, deckRoot);
    freeMem(deckRoot);

	// while(1)
	// {
	// 		// some code here
	// }
//	display(superInitialArr, "Super Intial Array");
//	display(deckArr, "Final Array");
	fprintf(stdout, "%d\n", count);

	return 0;
}


#include "deckOfCards.h"

void printPlayerDeck(void){
    // dummy player's cardHead will always be NULL as he wont be dealt any cards ever
    if(dummyPlayer->next->cardHead == NULL){
        printf("No player's have cards with them. \n");
        return;
    }
    playerHand_t *tempPlayerPtr = dummyPlayer->next; // skip the dummy player
    while(tempPlayerPtr!=NULL){
        card_t *tempPtr = tempPlayerPtr->cardHead;
        if(tempPtr == NULL){
            printf("This player has no more cards.\n");
        }
        else{
            printf("Number of cards with this player: %d\n", (int)tempPlayerPtr->numberOfCards);
            while(tempPtr!= NULL){
                printf("(%d)%d -> ", tempPtr->currentHandIndexNumber, tempPtr->cardNum);
                tempPtr = tempPtr->next;
            }
            printf("NULL\n");
        }
        tempPlayerPtr = tempPlayerPtr->next;    // go to next player
    }
    printf("\n");
}

void printDeck(uint32_t deckNum, cardDeck_t *const deckRoot){
    
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

void freeMemDeck(cardDeck_t *deckRoot){
    if(deckRoot == NULL){
        printf("Nothing to free !\n");
        return;
    }
    card_t *tempPtr = deckRoot->head;
    if(tempPtr != NULL){
        while(tempPtr != NULL){
            deckRoot->head = deckRoot->head->next;
            free(tempPtr);
            tempPtr = deckRoot->head;
        }
    }
    free(deckRoot);
}

void freeMemPlayers(void){
    if(dummyPlayer->cardHead == NULL){
        printf("Nothing to free !\n");
        return;
    }

    card_t *tempPtr = dummyPlayer->cardHead;
    if(tempPtr != NULL){
        while(tempPtr != NULL){
            dummyPlayer->cardHead = dummyPlayer->cardHead->next;
            free(tempPtr);
            tempPtr = dummyPlayer->cardHead;;
        }
    }
    free(dummyPlayer);
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
        newCard->currentHandIndexNumber = 0;    // this is not a hand, this is deck composition
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

void initializePlayers(const uint32_t numberOfPlayers){
    // if number of players is invalid value, we cannot proceed
    if(numberOfPlayers == 0){   return; }

    // playerHand_t *dummyPlayer = NULL;
    dummyPlayer = malloc(sizeof(playerHand_t));
    dummyPlayer->cardHead=NULL;
    dummyPlayer->next=NULL;
    dummyPlayer->numberOfCards = 0;

    playerHand_t *tempPtr = dummyPlayer;
    // create structures for each player
    for(int i=0; i<numberOfPlayers; i++){
        playerHand_t *newPlayer = malloc(sizeof(playerHand_t));
        if(newPlayer == NULL)   {   return; }

        newPlayer->numberOfCards = 0;
        newPlayer->next = NULL;
        newPlayer->cardHead = NULL;
        newPlayer->numberOfCards = 0;    // track # of cards a player has

        if(dummyPlayer->next == NULL){          // if this is first player, store its address in default player's memory 
            dummyPlayer->next = newPlayer;
        }
        else
        {
            tempPtr->next = newPlayer;
        }
        tempPtr = tempPtr->next;
    }
}

void dealHand(cardDeck_t *deckRoot, const uint32_t numberOfPlayers){

    // if deck root is empty we cannot proceed
    if(deckRoot == NULL){   return; }
    // if number of players is invalid value, we cannot proceed
    if(numberOfPlayers == 0){   return; }

    uint32_t cardCounter = 0, deckCounter = 0;
    playerHand_t *currPlayer = dummyPlayer->next;
    // Deal 1 card each to every player starting with player 1 and wrap around back to first player
    while((deckRoot != NULL) && (deckRoot->head != NULL)){
        // take one card out from deckRoot
        card_t *currCardPtr = deckRoot->head;
        if((deckRoot->head->next != NULL)){
            deckRoot->head = deckRoot->head->next;
        }
        else{
            deckRoot->head = NULL;
        }
        
        currCardPtr->next = NULL;
        // if this is first time giving out card, store it as head of card list
        if(currPlayer->cardHead == NULL){
            printf("1. current index: %d, current card: %d\n", currCardPtr->currentHandIndexNumber, currCardPtr->cardNum);
            currPlayer->cardHead = currCardPtr;
            currPlayer->numberOfCards = 1;
            currPlayer->cardHead->deckNumber = deckCounter++;
        }
        else
        {
            card_t *tempPtr = NULL;
            currPlayer->numberOfCards +=1;
            // advance tempPtr to the end of the current player's card list
            tempPtr = currPlayer->cardHead;
            while(tempPtr->next != NULL){
                tempPtr = tempPtr->next;
            }
            printf("    2. Curr index: %d, Curr card: %d\n", tempPtr->currentHandIndexNumber, tempPtr->cardNum);
            tempPtr->next = currCardPtr;
            printf("    2. Next index: %d, Next card: %d\n", currCardPtr->currentHandIndexNumber, currCardPtr->cardNum);
        }
        currCardPtr->currentHandIndexNumber = ++cardCounter;

        // go to next card
        // currCardPtr = deckRoot->head;
        // go to next player
        if(currPlayer->next == NULL){   // wrap around back to first player
            currPlayer = dummyPlayer->next;
            deckCounter = 0;            // wrap around deckCounter
        }
        else{
            currPlayer = currPlayer->next;  // next player found, deal him a card in next iteration
        }
    }

}

cardDeck_t *reinitializeDeckUsingCardsFromPlayers(uint32_t numberOfPlayers){
    playerHand_t *currPlayer = dummyPlayer->next;
    playerHand_t *nextPlayer = currPlayer->next;
    cardDeck_t *nextCard = NULL;
    cardDeck_t *deckRoot = malloc(sizeof(cardDeck_t));
    cardDeck_t *deckRootPtr = NULL;

    for(int i=0; i<numberOfPlayers; i++){
        card_t *currCard = currPlayer->cardHead;
        while(currCard != NULL){
            deckRoot->head = currCard;
            currCard = currCard->next;
        }
    }

    for(int i = 0; i<numberOfPlayers; i++){
        // create card and add it to the deck, assign it to default deck
        // card_t *newCard = createCard(i+1, DEFAULT_DECK);
        card_t *currCard = currPlayer->cardHead;
        card_t *tempCardPtr = currCard;
        while(currCard != NULL){
            (deckRoot->head == NULL) ? (deckRoot->head = currCard) : (tempCardPtr = currCard);
            // if(deckRoot->head == NULL){
            //     deckRoot->head = currCard;
            // }
            // else{
            //     tempCardPtr = currCard;
            // }
            currCard = currCard->next;
        }
        currPlayer = currPlayer->next;
    }
    printDeck(DEFAULT_DECK, deckRoot);
    return deckRoot;
}

int main(int argc, char **argv)
{
	int count = 0, index = 0, start = 1, i = 0, j = 0, ret = 0;
    uint32_t numberOfCards = 10;
    uint32_t numberOfPlayers = 4;
    cardDeck_t *deckRoot = NULL;
	if(argc >  1)
	{
		numberOfCards = atoi(argv[1]);
        numberOfPlayers = atoi(argv[2]);
        if((numberOfCards > MAX_NUM_CARD) || (numberOfPlayers > MAX_NUM_PLAYERS)){
            printf("Card number/Player number cannot exceed 52!\n");
            return 0;
        }
	}
	// else
	// {
	// 	printf("Must enter the number of cards and players: Max to be 52!\n");
    //     return 0;
	// }

    // initialize deck
    deckRoot = initializeDeck(numberOfCards, false);
    printDeck(DEFAULT_DECK, deckRoot);
    // initialize players
    initializePlayers(numberOfPlayers);
    printPlayerDeck();
    dealHand(deckRoot, numberOfPlayers);
    printPlayerDeck();
    // deckRoot = reinitializeDeckUsingCardsFromPlayers(numberOfPlayers);
    printDeck(DEFAULT_DECK, deckRoot);
    freeMemPlayers();
    freeMemDeck(deckRoot);

	// while(1)
	// {
	// 		// some code here
	// }
//	display(superInitialArr, "Super Intial Array");
//	display(deckArr, "Final Array");
	fprintf(stdout, "%d\n", count);

	return 0;
}

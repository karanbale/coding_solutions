
#include "deckOfCards.h"

void printPlayerDeck(void){
    // dummy player's cardHead will always be NULL as he wont be dealt any cards ever
    if((dummyPlayer->next == NULL) || (dummyPlayer->next->cardHead == NULL)){
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

void printDeck(const uint32_t deckNum, cardDeck_t *const deckRoot){
    
    if(deckRoot == NULL){
        printf("Cannot print empty deck !\n");
        return;
    }

    card_t *tempPtr = deckRoot->head;
    while(tempPtr != NULL){
        if((deckNum == DEFAULT_DECK)||(deckNum == tempPtr->deckNumber)){
            printf("%d -> ", tempPtr->cardNum);
        }
        tempPtr = tempPtr->next;
    }
    printf("NULL\n");
}

bool validateDeck(cardDeck_t *const deckRoot){
    
    if(deckRoot == NULL){
        printf("Cannot validate empty deck !\n");
        return false;
    }

    card_t *tempPtr = deckRoot->head;
    while(tempPtr != NULL){
        if(tempPtr->firstHandIndex != tempPtr->currentHandIndexNumber){
            return false;
        }
        tempPtr = tempPtr->next;
    }
    
    return true;
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

void freePlayers(void){
    if(dummyPlayer->next == NULL){
        printf("Nothing to free !\n");
        return;
    }

    playerHand_t *currPlayerPtr = dummyPlayer->next;
    playerHand_t *prevPlayerPtr = currPlayerPtr;
    card_t *currCardPtr = currPlayerPtr->cardHead;
    card_t *prevCardPtr = currCardPtr;
    
    dummyPlayer->next = currPlayerPtr->next;    // advance dummy before we free current player
    currPlayerPtr->next = NULL;                 // break the link
    while(currPlayerPtr != NULL){
        if(currCardPtr != NULL){
            while(currCardPtr != NULL){
                currCardPtr = currCardPtr->next;    // advance to next card
                free(prevCardPtr);
                prevCardPtr = currCardPtr;
            }
        }
        currPlayerPtr = currPlayerPtr->next;
        free(prevPlayerPtr);
        prevPlayerPtr = currPlayerPtr;
    }
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

cardDeck_t *initializeDeck(uint32_t numberOfCards, bool shuffleCards){
    
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

    for(uint32_t i = 0; i<numberOfCards; i++){
        // create card and add it to the deck, assign it to default deck
        card_t *newCard = createCard(i+1, DEFAULT_DECK);
        newCard->currentHandIndexNumber = 0;    // this is not a hand, this is deck composition
        newCard->firstHandIndex = i+1;
        if(!root->head){
            root->head = newCard;
            tempPtr = newCard;
        }
        else{
            tempPtr->next = newCard;
            tempPtr = tempPtr->next;
        }
    }

    //TODO: shuffle (reverse for simplicity) linked-list if shuffleCards is false

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
    for(uint32_t i=0; i<numberOfPlayers; i++){
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

    uint32_t deckCounter = 0;
    playerHand_t *currPlayer = dummyPlayer->next;
    // Deal 1 card each to every player starting with player 1 
    // then card 2, to player 2, card 3 to player 3 and so on
    // and wrap around back to first player when we reach our max number of players
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
            // printf("1. current index: %d, current card: %d\n", currCardPtr->currentHandIndexNumber, currCardPtr->cardNum);
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
            // printf("    2. Curr index: %d, Curr card: %d\n", tempPtr->currentHandIndexNumber, tempPtr->cardNum);
            tempPtr->next = currCardPtr;
            // printf("    2. Next index: %d, Next card: %d\n", currCardPtr->currentHandIndexNumber, currCardPtr->cardNum);
        }

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
    cardDeck_t *deckRoot = malloc(sizeof(cardDeck_t));
    // heap allocation success / not
    if(!deckRoot){
        return NULL;
    }
    deckRoot->next = NULL;
    deckRoot->head = NULL;

    card_t *tempPtr = deckRoot->head;
    uint32_t cardCounter = 0;

    playerHand_t *currPlayer = dummyPlayer->next;

    for(uint32_t i=0; i<numberOfPlayers; i++){
        card_t *currCard = currPlayer->cardHead;
        card_t *prevCard = currCard;
        while(currCard != NULL){
            if(deckRoot->head == NULL){
                deckRoot->head = currCard;       // add value back to the deck
                tempPtr = currCard;
            }
            else{
                tempPtr->next = currCard;
                tempPtr = tempPtr->next;
            }
            currCard->currentHandIndexNumber = ++cardCounter;
            currCard = currCard->next;          // advance current card
            prevCard->next = NULL;              // shallow-copying side effect
            prevCard = currCard;
            currPlayer->cardHead = currCard;
        }
        currPlayer = currPlayer->next;
    }

    // printDeck(DEFAULT_DECK, deckRoot);          // check if deck is assembled

    return deckRoot;
}

int main(int argc, char **argv)
{
	size_t count = 0;
    bool deckNotRestored = true;
    uint32_t numberOfCards = 10;
    uint32_t numberOfPlayers = 2;
    cardDeck_t *deckRoot = NULL;
	if(argc >  1)
	{
		numberOfCards = atoi(argv[1]);
        if((numberOfCards > MAX_NUM_CARD) || (numberOfCards < MIN_NUM_CARD)){
            printf("Card number cannot exceed %ld OR be less than %ld!\n", MAX_NUM_CARD, MIN_NUM_CARD);
            return 0;
        }
	}
	else
	{
        printf("Please enter number of cards (MAX number set to %ld): \n",MAX_NUM_CARD);
        scanf("%d", &numberOfCards);
        if(numberOfCards > MAX_NUM_CARD){
            printf("Must enter the number of cards: Max to be %ld OR Min to be %ld!\n",MAX_NUM_CARD, MIN_NUM_CARD);
            return 0;
        }
		
	}

    // initialize deck
    deckRoot = initializeDeck(numberOfCards, false);
    // printDeck(DEFAULT_DECK, deckRoot);

    // until deck is restored, do not stop
    while(deckNotRestored)
    {
        // wrap around to 3, whenever we've reached 5
        if(numberOfPlayers >= 5){
            numberOfPlayers = 2;
        }
        numberOfPlayers++;
        // printf("Current Player count: %d\n",numberOfPlayers);

        // initialize players
        initializePlayers(numberOfPlayers);
        // printPlayerDeck();
        dealHand(deckRoot, numberOfPlayers);
        // printPlayerDeck();
        deckRoot = reinitializeDeckUsingCardsFromPlayers(numberOfPlayers);
        // printDeck(DEFAULT_DECK, deckRoot);
        
        if(validateDeck(deckRoot)){
            // printf("#########################################\n");
            // printf("    Restored successfully  \n");
            // printf("#########################################\n");
            deckNotRestored = false;
        }
        freePlayers();
        count++;
    }

    // clean up to avoid memory leaks
    freeMemDeck(deckRoot);
    free(dummyPlayer);

	fprintf(stdout, "Total rounds require to restore original order: %ld\n", count);

	return 0;
}

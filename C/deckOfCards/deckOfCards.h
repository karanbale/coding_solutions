#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_DECK    0UL
#define MIN_NUM_CARD    0UL
#define MAX_NUM_CARD    52UL
#define INVALID_DATA    0xFFUL

/**
 * @brief   : This structure holds information about how a card would look like. 
*/
typedef struct card{
    uint32_t cardNum;                // each card is unique, we'll just assign incremental numbers per card
    uint32_t deckNumber;             // 0 when in a deck, greater than 0, when held by person
    uint32_t currentHandIndexNumber; // update this index for every time this card is handed out
    uint32_t firstHandIndex;         // update this index only during first round and don't touch this again.
    struct card *next;
} card_t;

/**
 * @brief   :   This structure holds information about how a card deck would look like. 
*/
typedef struct cardDeck{
    size_t numberOfCards;
    card_t *head;
    struct cardDeck *next;
}cardDeck_t;

/**
 * @brief   : This structure holds information about how a player data would look like.
*/
typedef struct playerHand{
    size_t numberOfCards;           // how many cards does this player hold
    card_t *cardHead;               // Pointer to first card this player holds
    struct playerHand *next;        // pointer to next player, daisy chain of players in sequential order
}playerHand_t;

/**
 * @brief   : This is a default player, who does not play, just tracks few things internally for us.
*/
playerHand_t *dummyPlayer = NULL;

/**
 * @brief           : Function to print values in given deck
 * @param deckNum   : Deck number from which, we want to print cards
 * @param deckRoot  : pointer to the root of deck
 * @return          : void
*/
void printDeck(const uint32_t deckNum, cardDeck_t *const deckRoot);

/**
 * @brief                       : Function to print values in given player's deck
 * @return                      : void
*/
void printPlayerDeck(void);

/**
 * @brief         : Function to create individual card and allocate deck number
 * @param cardNum : number of the card we're going to create.
 * @param deckNum : deck number, the card will belong to
 * @return        : Return pointer to the card that was created
*/
card_t *createCard(uint32_t cardNum, uint32_t deckNum);

/**
 * @brief                   : Function to initialize a deck of cards from scratch
 * @param numberOfCards     : Number of cards present in this deck
 * @param incOrderOfCards   : True keeping card deck intact, False for shuffling cards (can reverse them for simplicity)
 * @return                  : Return pointer to head of the cardDeck
*/
cardDeck_t *initializeDeck(uint32_t numberOfCards, bool incOrderOfCards);

/**
 * @brief                   : Function to initialize a structures for given number of players
 * @param numberOfPlayers   : total number of players in the game
 * @return                  : void
*/
void initializePlayers(const uint32_t numberOfPlayers);

/**
 * @brief                   : Function to initialize deck order
 * @param deckRoot          : pointer to the head of cardDeck_t, begin traversing from here
 * @param incOrderOfCards   : True for incremental order (0 down to N), False for decremental order (N down to 0)
 * @return                  : True if deck is reset to orderOfCards order, False otherwise
*/
bool isDeckResetToOriginal(cardDeck_t *deckRoot, bool incOrderOfCards);

/**
 * @brief                   : Function to distribute cards amongst given number of players
 * @param deckRoot          : pointer to the head of cardDeck_t, being distribution from here
 * @param numberOfPlayers   : total number of players in the game
 * @return                  : void
*/
void distributeCards(cardDeck_t *deckRoot, uint32_t numberOfPlayers);

/**
 * @brief           : Function to free up memory allocated on heap for deck of cards
 * @param deckRoot  : Pointer to the root of deck of cards
*/
void freeMemDeck(cardDeck_t *deckRoot);

/**
 * @brief           : Function to free up memory allocated on heap for players
 * @param deckRoot  : Pointer to the root of deck of cards
*/
void freePlayers(void);

/**
 * @brief                   : Function to hand out/deal cards to the players
 * @param deckRoot          : pointer to the head of cardDeck_t, being distribution from here
 * @param numberOfPlayers   : Number of players this hand needs to be dealt in between
 * @return                  : void
*/
void dealHand(cardDeck_t *deckRoot, uint32_t numberOfPlayers);

/**
 * @brief                   : Function to re-initialize card deck by collecting cards from players and piling them up on 
 *                            top of each other in sequential manner i.e. P1<-P2<P3 (P1 is on top, P3 is at bottom)
 * @param deckRoot          : pointer to the head of cardDeck_t, being distribution from here
 * @param numberOfPlayers   : Number of players this hand needs to be dealt between
 * @return                  : Return pointer to head of the cardDeck
*/
cardDeck_t *reinitializeDeckUsingCardsFromPlayers(uint32_t numberOfPlayers);

/**
 * @brief                   : Function to validate if current deck has returned to its original position
 * @param deckRoot          : pointer to the head of cardDeck_t, being distribution from here
 * @return                  : Return pointer to head of the cardDeck
*/
bool validateDeck(cardDeck_t *const deckRoot);
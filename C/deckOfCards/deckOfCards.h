#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils/hashMap.h"

#define DEFAULT_DECK    0UL
#define MAX_NUM_CARD    52UL
#define MAX_NUM_PLAYERS 52UL
#define INVALID_DATA    0xFFUL

char const *suits_str[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
char const *faces_str[13] = {"2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K", "A"};

typedef struct card{
    int cardNum;
    int deckNumber;             // 0 when in a deck, greater than 0, when held by person
    // char *cardNameStr[1];   // since "Diamonds" is 8 char long, limit to 9 char
    // char *suitNameStr[9];
    int currentHandIndexNumber; // update this index for every time this card is handed out
    struct card *next;
} card_t;

typedef struct cardDeck{
    size_t numberOfCards;
    card_t *head;
    struct cardDeck *next;
}cardDeck_t;

/**
 * @brief   : This is a default player, who does not play, just tracks few things internally for us.
*/
typedef struct playerHand{
    size_t numberOfCards;
    card_t *cardHead;
    struct playerHand *next;
}playerHand_t;

playerHand_t *dummyPlayer = NULL;

typedef struct playerTracker{
    struct playerHand *head;
}playerTracker_t;

playerTracker_t *rootPlayerTrackerPtr;
/**
 * @brief           : Function to print values in given deck
 * @param deckNum   : Deck number from which, we want to print cards
 * @param deckRoot  : pointer to the root of deck
 * @return          : void
*/
void printDeck(uint32_t deckNum, cardDeck_t *const deckRoot);

/**
 * @brief                       : Function to print values in given player's deck
 * @param playerNumber          : Deck number from which, we want to print cards
 * @param rootPlayerTrackerPtr  : pointer to the root of player's deck
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
 * @param incOrderOfCards   : True for incremental initialization (0 down to N), False for decremental initialization (N down to 0)
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
 * @brief                   : Function to distribute cards amongst given number of people
 * @param deckRoot          : pointer to the head of cardDeck_t, being distribution from here
 * @param numberOfPlayers   : total number of players in the game
 * @return                  : void
*/
void distributeCards(cardDeck_t *deckRoot, uint32_t numberOfPlayers);

/**
 * @brief           : Function to free up memory allocated on heap for deck
 * @param deckRoot  : Pointer to the root deck
*/
void freeMemDeck(cardDeck_t *deckRoot);

/**
 * @brief           : Function to free up memory allocated on heap for players
 * @param deckRoot  : Pointer to the root deck
*/
void freeMemPlayers(void);

/**
 * @brief                   : Function to hand out cards to players
 * @param deckRoot          : pointer to the head of cardDeck_t, being distribution from here
 * @param numberOfPlayers   : Number of players this hand needs to be dealt between
 * @return                  : void
*/
void dealHand(cardDeck_t *deckRoot, uint32_t numberOfPlayers);

/**
 * @brief                   : Function to re-initialize card deck by collecting cards from players
 * @param deckRoot          : pointer to the head of cardDeck_t, being distribution from here
 * @param numberOfPlayers   : Number of players this hand needs to be dealt between
 * @return                  : Return pointer to head of the cardDeck
*/
cardDeck_t *reinitializeDeckUsingCardsFromPlayers(uint32_t numberOfPlayers);

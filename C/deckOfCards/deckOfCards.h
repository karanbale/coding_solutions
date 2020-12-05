#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_DECK    0

char const *suits_str[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
char const *faces_str[13] = {"2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K", "A"};

typedef struct card{
    int cardNum;
    int deckNumber;             // 0 when not held by a person, greater than 0, when held by person
    // char *cardNameStr[1];   // since "Diamonds" is 8 char long, limit to 9 char
    // char *suitNameStr[9];
    struct card *next;
} card_t;

typedef struct cardDeck{
    size_t numberOfCards;
    card_t *head;
    struct cardDeck *next;
}cardDeck_t;

/**
 * @brief   : Function to print values in given deck
 * @param deckNum   : Deck number from which, we want to print cards
 * @param deckRoot  : pointer to the root of deck
*/
void printDeck(uint32_t deckNum, cardDeck_t *deckRoot);

/**
 * @brief   : Function to create individual card and allocate deck number
 * @param cardNum : number of the card we're going to create.
 * @param deckNum : deck number, the card will belong to
 * @return        : Return pointer to the card that was created
*/
card_t *createCard(uint32_t cardNum, uint32_t deckNum);

/**
 * @brief : Function to initialize a deck of cards from scratch
 * @param numberOfCards     : Number of cards present in this deck
 * @param incOrderOfCards   : True for incremental initialization (0 down to N), False for decremental initialization (N down to 0)
 * @return                  : Return pointer to head of the cardDeck
*/
cardDeck_t *initializeDeck(uint32_t numberOfCards, bool incOrderOfCards);

/**
 * @brief   : Function to initialize deck order
 * @param deckRoot          : pointer to the head of cardDeck_t, begin traversing from here
 * @param incOrderOfCards   : True for incremental order (0 down to N), False for decremental order (N down to 0)
 * @return                  : True if deck is reset to orderOfCards order, False otherwise
*/
bool isDeckResetToOriginal(cardDeck_t *deckRoot, bool incOrderOfCards);

/**
 * @brief   : Function to distribute cards amongst given number of people
 * @param deckRoot          : pointer to the head of cardDeck_t, being distribution from here
 * @param numberOfPlayers   : total number of players in the game
*/
void distributeCards(cardDeck_t *deckRoot, uint32_t numberOfPlayers);

/**
 * @brief   : Function to free up memory allocated on heap
 * @param deckRoot  : Pointer to the root deck
*/
void freeMem(cardDeck_t *deckRoot);
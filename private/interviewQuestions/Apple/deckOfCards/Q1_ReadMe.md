How to run code:
    - Please make sure you have gcc / clang compiler installed before running this program.
    - Copy deckOfCards.h / deckOfCards.c / Makefile to a local directory and simply run make in the directory at the level of Makefile.
    - This Makefile will generate an output file called "deckOfCards", you can run that on your shell, pass argument requested and observe the output.
    - Here is a sample output from my local machine:
            make clean; make
            rm -f *.o deckOfCards
            gcc -g -c -Wall -Wfatal-errors -Wextra -Wformat=2 -Wmisleading-indentation deckOfCards.c
            deckOfCards.c:123:57: warning: unused parameter 'incOrderOfCards' [-Wunused-parameter]
            cardDeck_t *initializeDeck(uint32_t numberOfCards, bool shuffleCards){
                                                                    ^
            1 warning generated.
            gcc -o deckOfCards -g deckOfCards.o

            ls
            Makefile        Notes           deckOfCards     deckOfCards.c   deckOfCards.h   deckOfCards.o   question2.c     utils

            ./deckOfCards 
            Please enter number of cards (MAX number set to 52): 
            40
            Total rounds require to restore original order: 72    
    
    - In case you do not have gcc compiler installed but have clang installed, you can simply run following command line, that generates a.out file.
            /usr/bin/clang -g /Users/karansinghbale/Documents/projectEuler/C/deckOfCards/deckOfCards.c 
    - Simply run a.out on your shell, pass argument requested and observe the output.

Assumptions Made about given problem:
    - There is NO shuffling of the cards in between any of the rounds, until the deck is restored back to its original order.
    - Card shuffling is permitted only before or after the rounds are finished and deck is back to its original order.
    - All N cards are distributed among all the people i.e. no card is left behind on the table.
    - Since number of people can vary, not every person may get equal number of cards.
        i.e. if we have 10 cards and 4 people, 2 people get 3 cards each, and 2 people get 2 cards each. 
        (Distributing 1 card each in round robin fashion.)
    - Cards being held by each person, are not swapped with other person holding cards / are not passed around. 
      Everyone holds their cards and returns them, in the order they were given to each person, to conclude the round.
    - Cards are not shuffled by the person holding the cards. The person holding cards, 
      maintains the order of cards in the way it was received.
    - The final answer count only increments per round and is initialized to 0. It will not account for starting state of the deck.
    - Since the Problem does not include upper bounds / lower bounds for number of cards i.e. N, I've set the upper bound at 52,
    (because we have 52 cards in a deck, but I've tested it for random values greater than 52).
    - I've set the lower bound for input to be 0, to cover lowest input corner case.

Core Algorithm:
    1. Take number of cards as input from user. Create nodes in heap memory = number of cards. Create a deck of cards i.e. list of card nodes in incremental order, each smaller card pointing to next bigger card. e.g. 1->2->3->4->5 and so on...
    2. Create nodes for players in heap memory = number of players (this is done during run time, so changes from round to round).
    3. Deal cards to players. i.e. take pointers from card deck, and assign them to player's deck, until card deck is empty. Do this in incremental fashion, i.e. assign card 1 to player 1, card 2 to player 2 and so on...
        a. If this is first time dealing cards, store each card's current index in card's node, never update this index ever again.
    4. Collect cards back from players i.e. re-compose your deck from player's cards by re-assigning card's node pointers to
    card deck in orderly fashion. 
        a. Assign a incremental index to each card in order it was collected from players. This index is separate from 3.a index. This index keeps updating for each round.
    5. Check if card deck formed in step 4 is orderly fashion by comparing 3.a index with 4.a index. i.e. if index of cards at first round == index of cards at current round, we've got our cards in orderly fashion.
    6. Free player nodes.
    7. Repeat step 2 - 6 for 3 players, 4 players, 5 players and back to 3 and so on, until step 5 is met.
    8. When step 5 condition is satisfied, stop, clean up (i.e. free up all the nodes cards/players etc) and exit.

Algorithm Notes:
    - Since we cannot use arrays, I have presumed, I cannot use stack / queue either. 
    - In my opinion, though arrays and stacks are two different data structures, 
    they both perform index based operations, both require traversing for accessing/updating elements, 
    so they are quite similar in more ways than few.
    - Thus I decided to simply use linked-lists and shallow copy of these linked-lists,
    while allocating/deallocating cards to/from players and to/from deck.
    - Using shallow copy enables my algorithm to run in constant space / memory, since it involves only moving pointers around.
    - I've ran this code with my brute-force algorithm, the output is quite different for different inputs, and thus I cannot
    use DP on it to enhance my algorithm. I've ran this algorithm with an input of N=19, I get the output as 154 but for 
    N = 20, output is 10, N = 11 output 2 and thus there is no pattern to introduce DP.

Key code structures to be aware of:
    - card_t:
        This structure holds information about how a card would look like. 
    - cardDeck_t:
        This structure holds information about how a card deck would look like.
    - playerHand_t:
        This structure holds information about how a player's data would look like.

Scalability:
    - This code can not be scaled for inputs which are in really high, since the core algorithm runs in O(N) space complexity and ON(N * M) time complexity .
    - In order to scale this code, if we can use arrays / stacks, code can handle larger inputs with better time complexity.
    - We can introduce threading / parallel processing to speed up the computations.
    - I've added an argument incOrderOfCards for future purpose, when we wish to shuffle cards.

Worse case Time Complexity:
    - There is a little gotcha with this algorithm, since number of shuffles can swing between N and 1 for any given number N.
    - Thus even though each iteration is worse case O(N), we're still running say M iterations of shuffles.
    - Below is an explanation of O(N) time complexity analysis
    - Although this code has several nested for / while loops, the time complexity never exceeds N simply because of the outerloop limitation.
    - We either iterate over N items, to add / remove them from linked list, and assign them to players (max number of player = 5).
    - When we assign cards to the players cards are split between players, so O(N/(number of players)) is max iteration count per nested loop,
    which sums up to O(N).
    - When we reform the deck by collecting cards from players or vice versa, we're still running a loop of N cards.
    - Now, the total number of shuffles in worse case are assumed to be M, thus our complexity would be O(N*M)
    - Final Time Complexity: O(N*M), where N = number of inputs and M = number of shuffles requred

Worse case Space Complexity:
    - The space complexity here is O(N) since I'm using shallow copies to move data around and never allocate extra memory.
    - The only memory needed is for allocating 1 linked-list per input, thus N linked lists for N inputs.
    - Final Space Complexity: O(N)

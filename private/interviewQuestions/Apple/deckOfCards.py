import math
import copy
from copy import deepcopy

try:
    numOfCards = int(raw_input('Enter number of cards:'))
except ValueError:
    print "Not a number"

print numOfCards

superInitialCards = []

initialCards = []

for i in range(numOfCards + 1):
    initialCards.append(i)

superInitialCards = deepcopy(initialCards)

deckCards = deepcopy(initialCards)

def comparedecks(deckCards):
    for i in range(numOfCards):
        if deckCards[i] != superInitialCards[i]:
            return False
    return True

count = 0
while(1):
    index = 0
    i = 1
    start = 1
    # print "initial ", initialCards[1:]
    while index < numOfCards:
        i = start
        while i <= numOfCards:
            deckCards[numOfCards - index] = initialCards[i]
            i += start * 2
            index += 1
        start *= 2

    ret = comparedecks(deckCards)
    if ret:
        break;

    print "initial " , initialCards[1:]
    print "Final ", deckCards[1:]
    count += 1
    initialCards = []
    initialCards = deepcopy(deckCards)



print superInitialCards[1:]
print deckCards[1:]
print count+1
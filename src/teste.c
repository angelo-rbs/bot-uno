
#include "types.h"
#include <string.h>

void printaCarta(Card card) {
  printf("num: %s; suit: %s;\n", card.num, card.suit);
}

void printaMao(Hand hand) {

  for (int i = 0; i < hand.howManyCards; i++)
    printf("a %dª carta eh %s %c.\n", i+1, hand.handCards[i].num, hand.handCards[i].suit);
}
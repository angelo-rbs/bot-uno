#ifndef HAND
#define HAND

#include "definitions.h"

Card createCard(char *input);

Card getBestDiscard(Card card, Hand hand);

void shuffle(Hand hand);

void insertCardOnHand(Card card, Hand *hand);

void buy(int quant, Hand *hand);

void discard(Card card, Hand *hand);

#endif
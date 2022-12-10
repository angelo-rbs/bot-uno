#ifndef HAND
#define TYPES
#include "types.h"


void shuffle(Hand hand);

void insertCardOnHand(Card card, Hand *hand);

void discard(Hand *hand);

void buy(int quant, Hand hand);

void say(char* msg, int msg_size);

#endif
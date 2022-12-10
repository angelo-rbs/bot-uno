#ifndef TYPES
#define TYPES

typedef struct {

  char num[5]; // a gnt pode receber a carta  de valor 10, ai precisa de 2 espaços
  char *suit; // naipe

} Card;

typedef struct Hand {

  int howManyCards;
  Card *handCards;

} Hand;

typedef struct Pile {

  int howManyCards;
  Card *pileCards;

} Pile;

#endif
/** Constantes para as strings a serem lidas */
#ifndef DEFS
#define DEFS

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

// ---------------------------- DEFINIÇÕES ----------------------------



typedef struct Card {

  char num[5];
  char *suit;

} Card;

typedef struct Hand {

  int howManyCards;
  Card *handCards;

} Hand;

#endif
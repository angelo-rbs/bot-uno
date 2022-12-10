
//typedef struct Suit {

//  char suitName[3]; // eu dei um strlen nos naipes e todos tem 3 de tamanho
//} 

// eu achei melhor nao usar o struct Suit, oq tu acha?

typedef struct {

  char num[2]; // a gnt pode receber a carta  de valor 10, ai precisa de 2 espaços
  char *suit; // naipe

} Card;

typedef struct Hand {

  int *howManyCards;
  Card *handCards;

} Hand;

typedef struct Pile {

  int howManyCards;
  Card *pileCards;

} Pile;
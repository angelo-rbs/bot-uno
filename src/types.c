
typedef struct Suit {

  char suitName;
}

typedef struct Card {

  char num;
  Suit suit; // naipe

} Card;

typedef struct Hand {

  int howManyCards;
  Card *handCards;

} Hand;

typedef struct Pile {

  int howManyCards;
  Card *pileCards;

} Pile;
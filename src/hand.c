// include types
#include <string.h>

void shuffle(Hand hand) {

}

void discard(Card card, ) {

}

void insertCardOnHand(Card card, Hand hand) {
  hand.handCards[*(hand.howManyCards)] = card; // coloca a nova carta na mao
  *(hand.howManyCards) += 1; // aumenta a quantidade de cartas
  hand.handCards = realloc(hand.handCards, sizeof(Card)*(*(hand.howManyCards)+1)); // realoca deixando 1 lugar vago
}

void buy(int quant, Hand hand) {
  char input[10];
  Card auxCard;

  auxCard.suit = calloc(3, sizeof(char));

  printf("BUY %d\n", quant);
  for (int i=0; i<quant; i++) {
    scanf("%[^\n]", input);
    if (input[1] == '0') { // verifica se recebeu uma carta com valor 10
      strcpy(auxCard.num, "10");
      for (int j=2; j<5; j++) {
        auxCard.suit[j-2] = input[j];
      }
    } else {
      auxCard.num[0] = input[0];
      auxCard.num[1] = '\0';
      for (int j=1; j<4; j++) {
        auxCard.suit[j-1] = input[j];
      }
    }

    insertCardOnHand(auxCard, hand); // bota na mão
  }
}

void say(char* msg, int msg_size) {

}
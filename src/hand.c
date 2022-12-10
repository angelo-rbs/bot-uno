#include "types.h"
#include <string.h>
#include <stdlib.h>
#include "strategy.h"

void sort(Hand hand) {

}

Card createCard() {
  char input[10];
  Card auxCard;

  auxCard.suit = calloc(3, sizeof(char));

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
    return auxCard;
}

Card *discard(Card card, Hand hand) {
  Card aux;
  int indiceAux;
  aux = getBestDiscard(card, hand);

  if (!strcmp(aux.num, "12")) {
    hand.handCards = buy(1, hand); // se não tiver carta p descartar, chama a funcao de compra ## >>NÃO SEI SE FUNCIONARIA :(<<
    return hand.handCards;
  }
  for (int i=0; i<(*(hand.howManyCards)); i++) { 
    if (!strcmp(hand.handCards[i].suit, aux.suit) && !strcmp(hand.handCards[i].num, aux.num)) { // procura a carta descartada
      indiceAux = i;
      break;
    }
  }
  
  strcpy(hand.handCards[indiceAux].num, hand.handCards[(*(hand.howManyCards))-1].num);
  strcpy(hand.handCards[indiceAux].suit, hand.handCards[(*(hand.howManyCards))-1].suit);

  hand.handCards[(*(hand.howManyCards))-1].num[0] = '\0';
  hand.handCards[(*(hand.howManyCards))-1].suit[0] = '\0';
  *(hand.howManyCards) -= 1;
  hand.handCards = realloc(hand.handCards, sizeof(Card)*((*(hand.howManyCards))+1));
  return hand.handCards;
}

Card *insertCardOnHand(Card card, Hand hand) {
  hand.handCards[*(hand.howManyCards)] = card; // coloca a nova carta na mao
  *(hand.howManyCards) += 1;
  hand.handCards = realloc(hand.handCards, sizeof(Card)*(*(hand.howManyCards)+1)); // realoca deixando 1 lugar vago
  return hand.handCards;
}

Card *buy(int quant, Hand hand) {
  Card auxCard;

  printf("BUY %d\n", quant);
  for (int i=0; i<quant; i++) {
    auxCard = createCard();
    hand.handCards = insertCardOnHand(auxCard, hand); // bota na mão
    return hand.handCards;
  }
}

void say(char* msg, int msg_size) {

}

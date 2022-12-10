// include types
#include <string.h>
#include <stdlib.h>


// insere a carta na pilha
void pushToPile(Card pushed, Pile pile) {

}

// escolhe uma carta pra descartar (um dos últimos a serem feitos)
Card getBestDiscard(Card card, Hand hand) {
  Card aux;
  if ((card.num[0] - '0') < 10) { // PRIORIZA O DESCARTE DOS VALORES NUMERICOS
    for (int i=0; i<(*(hand.howManyCards)); i++) { // PROCURA UMA CARTA COM O MESMO VALOR
      if (!strcmp(hand.handCards[i].num, card.num)) {
        strcpy(aux.num, hand.handCards[i].num);
        strcpy(aux.suit, hand.handCards[i].suit);
        printf("DISCARD %s%s\n", aux.num, aux.suit);
        return aux;
      }
    }
    for (int i=0; i<(*(hand.howManyCards)); i++) { // PROCURA OUTRO NUMERO DE MESMA COR
      if (!strcmp(hand.handCards[i].suit, card.suit) && (((hand.handCards[i].num[0] - '0') < 10))) { 
        strcpy(aux.num, hand.handCards[i].num);
        strcpy(aux.suit, hand.handCards[i].suit);
        printf("DISCARD %s%s\n", aux.num, aux.suit);
        return aux;
      }
    }
  }
  for (int i=0; i<(*(hand.howManyCards)); i++) { // PROCURA UMA CARTA DE EFEITO DA MESMA COR
      if (!strcmp(hand.handCards[i].suit, card.suit) && (hand.handCards[i].num[0] == 'V' || hand.handCards[i].num[0] == 'D' || hand.handCards[i].num[0] == 'R')) {
        strcpy(aux.num, hand.handCards[i].num);
        strcpy(aux.suit, hand.handCards[i].suit);
        printf("DISCARD %s%s\n", aux.num, aux.suit);
        return aux;
      }
  }
  for (int i=0; i<(*(hand.howManyCards)); i++) { // DESCARTA AS CARTAS QUE TROCAM DE COR
    if (!strcmp(hand.handCards[i].suit, card.suit) && ((hand.handCards[i].num[0] == 'C' || hand.handCards[i].num[0] == 'A'))) {
      strcpy(aux.num, hand.handCards[i].num);
      strcpy(aux.suit, hand.handCards[i].suit);
      printf("DISCARD %s%s %s\n", aux.num, aux.suit, aux.suit); // coloquei para trocar sempre para o mesmo naipe da carta que estamos descartando
      return aux;                                               // pq nao implementamos ainda como descobrir qual o melhor naipe
    }
  }
  strcpy(aux.num, "12"); // CASO NAO ENCONTRE CARTA NA MAO, DEVOLVE UMA CARTA COM VALOR INVÁLIDO
  return aux;
}

// analisa a mão e diz qual eh o naipe menos frequente
char* getLeastFrequentSuitOnHand(Hand hand) {

}

// analisa a mão e diz qual eh o naipe mais frequente
char* getMostFrequentSuitOnHand(Hand hand) {

}

// analisa a pilha e diz qual eh o naipe menos frequente
char getLeastFrequentSuitOnPile() {

}

// analisa a pilha e diz qual eh o naipe mais frequente
char getMostFrequentSuitOnPile() {

}

// retorna um vetor com toda as cartas da mão de cor color
Card *getCardsOfColor(Hand hand, char* color) {

}

// retorna a carta da mão de maior valor (número)
Card getHigherCard(Hand hand) {
  
}

// diz se a carta eh de número (1 se for carta de número, 0 se for de ação)
int isNumberCard() {

}

// diz se a carta eh de ação (1 se for de ação, 0 se for de número)
int isActionCard() {

}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"
#include "io.h"

#define TAMANHO 17

// ---------------------------- HAND ----------------------------

Card createCard(char *input) {
  Card auxCard;

  auxCard.suit = calloc(3, sizeof(char));
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

Card getBestDiscard(Card card, Hand hand) {
  Card aux;
  aux.suit = calloc(4, sizeof(char));

  for (int i=0; i<(hand.howManyCards); i++) { // PROCURA UMA CARTA DE EFEITO DA MESMA COR
      if (!strcmp(hand.handCards[i].suit, card.suit) && (hand.handCards[i].num[0] == 'V' || hand.handCards[i].num[0] == 'R')) {
        strcpy(aux.num, hand.handCards[i].num);
        strcpy(aux.suit, hand.handCards[i].suit);
        printf("DISCARD %s%s\n", aux.num, aux.suit);
        return aux;
      }
  }
  for (int i=0; i<(hand.howManyCards); i++) { // FOCA EM FAZER OS OUTROS PUXAREM
    if (hand.handCards[i].num[0] == 'C') {
      strcpy(aux.num, hand.handCards[i].num);
      strcpy(aux.suit, hand.handCards[i].suit);
      printf("DISCARD %s%s %s\n", aux.num, aux.suit, card.suit); // coloquei para trocar sempre para o mesmo naipe da carta que estamos descartando
      return aux;                                               // pq nao implementamos ainda como descobrir qual o melhor naipe
    }
  }
  if ((card.num[0] - '0') < 10) { // PRIORIZA O DESCARTE DOS VALORES NUMERICOS
    for (int i=0; i<(hand.howManyCards); i++) { // PROCURA UMA CARTA COM O MESMO VALOR
      if (!strcmp(hand.handCards[i].num, card.num)) {
        strcpy(aux.num, hand.handCards[i].num);
        strcpy(aux.suit, hand.handCards[i].suit);
        printf("DISCARD %s%s\n", aux.num, aux.suit);
        return aux;
      }
    }
  }
  for (int i=0; i<(hand.howManyCards); i++) { // PROCURA OUTRO NUMERO DE MESMA COR
      if (!strcmp(hand.handCards[i].suit, card.suit) && (((hand.handCards[i].num[0] - '0') < 10))) {
        strcpy(aux.num, hand.handCards[i].num);
        strcpy(aux.suit, hand.handCards[i].suit);
        printf("DISCARD %s%s\n", aux.num, aux.suit);
        return aux;
      }
    }
  for (int i=0; i<(hand.howManyCards); i++) { // PROCURA UMA CARTA DE EFEITO DA MESMA COR
      if (!strcmp(hand.handCards[i].suit, card.suit) && (hand.handCards[i].num[0] == 'V' || hand.handCards[i].num[0] == 'D' || hand.handCards[i].num[0] == 'R')) {
        strcpy(aux.num, hand.handCards[i].num);
        strcpy(aux.suit, hand.handCards[i].suit);
        printf("DISCARD %s%s\n", aux.num, aux.suit);
        return aux;
      }
  }
  for (int i=0; i<(hand.howManyCards); i++) { // DESCARTA AS CARTAS QUE TROCAM DE COR
    if (((hand.handCards[i].num[0] == 'C' || hand.handCards[i].num[0] == 'A'))) {
      strcpy(aux.num, hand.handCards[i].num);
      strcpy(aux.suit, hand.handCards[i].suit);
      printf("DISCARD %s%s %s\n", aux.num, aux.suit, aux.suit); // coloquei para trocar sempre para o mesmo naipe da carta que estamos descartando
      return aux;                                               // pq nao implementamos ainda como descobrir qual o melhor naipe
    }
  }
  strcpy(aux.num, "12"); // CASO NAO ENCONTRE CARTA NA MAO, DEVOLVE UMA CARTA COM VALOR INVÁLIDO
  return aux;
}

void insertCardOnHand(Card card, Hand *hand) {

  (*hand).handCards = realloc( (*hand).handCards, sizeof(Card) * ((*hand).howManyCards + 1)); // realoca deixando 1 lugar vago
  (*hand).handCards[ (*hand).howManyCards ] = card; // coloca a nova carta na mao
  (*hand).howManyCards += 1; // aumenta a quantidade de cartas
  
}

void buy(int quant, Hand *hand) {
  Card auxCard;
  char input[10];

  printf("BUY %d\n", quant);
  for (int i=0; i<quant; i++) {
    scanf(" %[^\n]\n", input);
    auxCard = createCard(input);
    insertCardOnHand(auxCard, hand); // bota na mão
  }
}

void discard(Card card, Hand *hand) {
  Card aux;
  int indiceAux;
  aux = getBestDiscard(card, (*hand));
  if (!strcmp(aux.num, "12")) {
    buy(1, hand); // se não tiver carta p descartar, chama a funcao de compra ## >>NÃO SEI SE FUNCIONARIA :(<<
    return;
  }
  for (int i=0; i<(hand->howManyCards); i++) { 
    if (!strcmp(hand->handCards[i].suit, aux.suit) && !strcmp(hand->handCards[i].num, aux.num)) { // procura a carta descartada
      indiceAux = i;
      break;
    }
  }
  
  strcpy(hand->handCards[indiceAux].num, hand->handCards[(hand->howManyCards)-1].num);
  strcpy(hand->handCards[indiceAux].suit, hand->handCards[(hand->howManyCards)-1].suit);

  (*hand).handCards[(hand->howManyCards)-1].num[0] = '\0';
  (*hand).handCards[(hand->howManyCards)-1].suit[0] = '\0';
  (*hand).howManyCards -= 1;

  say();
}

void say() {
  char msgs[TAMANHO][100] = {"não importa o que você diria. alguém disse antes pra ela.",
                       "faltavam só 4 minutos... 4 minutos....",
                       "o jogo ja tava ganho...",
                       "não deixe que um bom final de semana te iluda.",
                       "seja aquilo que todos odeiam: você mesmo",
                       "por acaso seu presente é bom pra você ter medo do futuro?",
                       "não pense nos seus defeitos. eles são muitos e você não tem esse tempo todo.",
                       "dê o seu melhor! veja como nada muda.",
                       "sinta saudades de algo que nunca foi seu.",
                       "pratique o autoconhecimento. entenda porque não gostam de você.",
                       "acredite em você em 2023. porque não sobrou mais ninguém acreditando.",
                       "seja você mesmo. se decepcione.",
                       "perder tudo não faz diferença pra quem nunca teve nada.",
                       "dê uma nova chance. cometa velhos erros.",
                       "não desista. precisamos de alguém como exemplo de fracasso.",
                       "sua ex ainda lembre de você. quando lembra das piores escolhas da vida dela.",
                       "não deixe de insistir onde você sabe que não tem chance."};

  srand(time(0));
  int index = rand()%TAMANHO;

  printf("%s\n", strcat(msgs[index], " ((bom dia!"));
}
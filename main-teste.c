#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** Constantes para as strings a serem lidas */
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

typedef struct {

  char num[5];
  char *suit;

} Card;

typedef struct Hand {

  int howManyCards;
  Card *handCards;

} Hand;

void debug(char *message) {
  fprintf(stderr, "%s\n", message);
}

void debugaMao(Hand mao) {
  debug("---- Sua mao ----");
  for (int i=0; i<(mao.howManyCards); i++) {
    debug(mao.handCards[i].num);
    debug(mao.handCards[i].suit);
  }
  debug("---- x ----");
}

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
  //realloc((*hand).handCards, sizeof(Card)*((hand->howManyCards)));
}

Hand* readHand(char string[MAX_LINE]) {

   const char s[2] = " ";
   char *token;

   Hand *hand;
   hand = calloc( 1,  sizeof(Hand) );
   hand->handCards = calloc( 1, sizeof(Card) );
   hand->howManyCards = 0;

   token = strtok(string, s);
   
   while( token != NULL ) {
      Card card;
      card.suit = calloc( 10, sizeof(char) );

      int tokenLen = strlen(token);
      int ehNum10 = 0;

      if ( strcmp( token, "[" ) != 0 && strcmp( token, "]" ) != 0 ) {

        if ( token[0] == '1' && token[1] == '0' ) {
          strcpy(card.num, "10");
          ehNum10 = 1;

        } else {
          card.num[0] = token[0];

          memcpy( card.num, &token[0], 1);
          card.num[1] = '\0';
        }

        char suit[10]; 
        for (int i = 0; i < tokenLen; i++)
          suit[i] = token[1 + i + ehNum10];

        strcat(card.suit, suit);

        insertCardOnHand(card, hand);
      }
      token = strtok(NULL, s);
   }

   return hand;
}

int main() {

  char temp[MAX_LINE];   // string para leitura temporária de dados
  char my_id[MAX_ID_SIZE];  // identificador do seu bot

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===

  // Lê uma linha até o '\n' com os identificadores dos jogadores.
  scanf("PLAYERS %[^\n]\n", temp);

  // Lê o identificador do próprio bot. Isso é importante para testar quando é sua vez.
  scanf("YOU %s\n", my_id);

  // Lê as cartas iniciais que o bot tem na mão. Ex: "[ 4♥ 7♦ 2♣ J♠ A♥ 3♦ 2♣ 9♠ ]".
  scanf("HAND %[^\n]\n", temp);
  Hand *hand = readHand(temp);


  // Lê a carta aberta sobre a mesa. Ex: TABLE 8♣
  scanf("TABLE %s\n", temp);
  Card table = createCard(temp);


  // === PARTIDA ===

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char complement2[MAX_LINE];
  int buyCount = 0; // verifica quantas precisaremos puxar
  Card newTable = table;

  while(1) {

    do {

      scanf("%s %s", action, complement); // lê o comando da vez
      if (complement[0] == 'A' || complement[0] == 'C') { // se tiver q trocar de cor, lê a nova cor
        scanf(" %s\n", complement2);
      }

      if (!strcmp(action, "DISCARD")) {
        newTable = createCard(complement);
        if (complement[0] == 'C') {
          buyCount = 4;
          strcpy(newTable.suit, complement2); // troca a cor
        } else if (complement[0] == 'V') {
          buyCount = 2;
        } else if (complement[0] == 'A') {
          strcpy(newTable.suit, complement2); // troca a cor
        } else {
          buyCount = 0;
        }
      }

    } while (strcmp(action, "TURN") || strcmp(complement, my_id));

    if (!buyCount) { // se nao tiver que comprar carta....
      discard(newTable, hand);
    } else {
      buy(buyCount, hand);
      buyCount = 0;
    }
  }

  return 0;
}

// Um exemplo de dados iniciais é:
// PLAYERS b1 b2 b3
// YOU b1
// HAND [ 4♥ 7♦ 2♣ V♠ A♥ 3♦ 2♣ 9♠ ]
// TABLE 8♦
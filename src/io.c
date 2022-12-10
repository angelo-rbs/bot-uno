#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hand.h"
#include "teste.h"

// *******************************************************

/* meu compilador tá reclamando que funções types.h e hand.h não existem. 
colei elas aqui por enquanto. */

void printaCarta(Card card) {
  printf("num: %s; suit: %s;\n", card.num, card.suit);
}

void printaMao(Hand hand) {

  for (int i = 0; i <hand.howManyCards; i++)
    printf("a %dª carta eh %s %s.\n", i+1, hand.handCards[i].num, hand.handCards[i].suit);
}

void insertCardOnHand(Card card, Hand *hand) {

  (*hand).handCards = realloc( (*hand).handCards, sizeof(Card) * ((*hand).howManyCards + 1)); // realoca deixando 1 lugar vago
  (*hand).handCards[ (*hand).howManyCards ] = card; // coloca a nova carta na mao
  (*hand).howManyCards += 1; // aumenta a quantidade de cartas
  
}

// *******************************************************


int *readPlayers(char string[MAX_LINE], int *playersIdList, int *idListSize) {

   const char s[2] = " ";
   char *token;

   token = strtok(string, s);
   (*idListSize) = 0;
   
   while( token != NULL ) {
      playersIdList = realloc(playersIdList, (*idListSize + 1) * sizeof(char)); //realoca pra receber +1 id
      sscanf(token, "%d", &playersIdList[ *idListSize ]);
      token = strtok(NULL, s);
      ++(*idListSize);
   }

   return *playersIdList;
}

// "[ 4♥ 7♦ 2♣ J♠ A♥ 3♦ 2♣ 9♠ ]"
// ou seja, A, 2, 3, 4, 5, 6, 7, 8, 9, 10, V (valete), D (dama), R (rei) e C (coringa),


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
        printf("dentro: suit(%s) num(%s)", card.suit, card.num);

        insertCardOnHand(card, hand);
      }
      printf("\n\n");
      token = strtok(NULL, s);
   }

   return hand;
}

void readTable() {
  
}

int main() {

  char str[MAX_LINE] = "[ 7♥ 1♣ 10♥ J♠ A♥ 3♦ 2♣ 9♠ ]";
  /*
  ♥ eh 14850469.
  ♦ eh 14850470.
  ♣ eh 14850467.
  ♠ eh 14850464.
  */
  
  Hand *hand = readHand(str);
  printf("\n");

  for (int i = 0; i < hand->howManyCards; i++)
    printaCarta(hand->handCards[i]);
  
}
#include <string.h>
#include <stdlib.h>

#include "hand.h"
#include "definitions.h"

// ---------------------------- IO ----------------------------

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
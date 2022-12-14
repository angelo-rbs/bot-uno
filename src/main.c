#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "definitions.h"
#include "hand.h"
#include "io.h"

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

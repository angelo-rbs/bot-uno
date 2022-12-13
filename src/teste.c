
#include <stdio.h>
#include "definitions.h"

// ---------------------------- TESTE ----------------------------

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
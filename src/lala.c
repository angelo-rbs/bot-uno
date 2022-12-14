#include <stdio.h>
#include <string.h>
#include <time.h>

#define TAMANHO 17

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

int main() {

  say();
}
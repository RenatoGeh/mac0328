/* DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.
// TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE
// SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM.  DECLARO
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.
//
// Autor:      Renato Lui Geh
// Numero USP: 8536030
// Sigla:      RENATOLU
// Data:       2016-08-29
//
// Este arquivo faz parte da tarefa E
// da disciplina MAC0328.
//
////////////////////////////////////////////////////////////// */

/* Este programa aceita dois valores pela linha de comando e um
 * terceiro opcional. O primeiro é o valor V de vértices do digrafo. O
 * segundo é o número k de digrafos aleatórios a serem gerados. O
 * terceiro é o algoritmo a ser usado (se 1, algoritmo naive e 2
 * algoritmo de Kosaraju-Sharir). O programa então imprime uma tabela
 * comparando as três primeiras componentes fortes do digrafo. */

#include <stdio.h>
#include <stdlib.h>

#include "DIGRAPHlists.h"

#define NUM_EVALD_SC 3

int naive_sc(Digraph G) {
   return 0;
}

int main(int argc, char *args[]) {
   int k, V, a, alg;
   int i, j;
   int msc[NUM_EVALD_SC + 1];
   Digraph G;
   int (*algs[2]) (Digraph G) = {naive_sc, DIGRAPHscKS};

   if (argc > 3) alg = atoi(args[3]);
   else alg = 2;

   V = atoi(args[1]);
   k = atoi(args[2]);

   for (i = 0; i < NUM_EVALD_SC + 1; ++i)
      msc[i] = 0;

   printf("%*cA |  0  |  1  |  2  | med |\n"
         "-------+-----+-----+-----+-----+\n", 5, ' ');
   for (i = 0; i < 17;) {
      int sc[NUM_EVALD_SC];
      int k, l, last;
      double avg = 0.0;

      for (j = 0; j < NUM_EVALD_SC; ++j)
         sc[j] = -1;
      if (i == 0)
         a = V/2;
      else a = i*V;

      G = DIGRAPHrand1(V, a);

      printf("nsc: %d\n", algs[alg-1](G));
      for (j = 0; j < G->V; ++j)
         printf(" %d", G->sc[j]);
      putchar('\n');

      last = G->sc[0];
      for (j = l = k = 0; l < G->V; ++l) {
         if (G->sc[l] != last) {
            int c;
            for (j = 0; j < NUM_EVALD_SC; ++j)
               if (k > sc[j]) {
                  for (c = NUM_EVALD_SC-1; c != j; --c)
                     sc[c] = sc[c + 1];
                  sc[j] = k;
                  break;
               }
            k = 0;
            last = G->sc[l];
         }
         ++k;
      }
      if (i == 0) printf("0.5*V  ");
      else printf("%3d*V  ", i);
      for (j = 0; j < NUM_EVALD_SC; ++j) {
         if (sc[j] < 0)
            printf("|  -  ");
         else {
            printf("|%5d", sc[j]);
            avg += sc[j];
            msc[j] += sc[j];
         }
      }
      msc[NUM_EVALD_SC] += avg;
      avg /= 3;
      printf("|%5.1f|\n", avg);

      if (i == 0)
         i = 1;
      else
         i <<= 1;

      DIGRAPHdestroy(G);
   }
   printf(" media ");
   for (i = 0; i < NUM_EVALD_SC; ++i)
      printf("|%5d", msc[i]);
   printf("|%5.1f|\n", msc[NUM_EVALD_SC]/(6.0*NUM_EVALD_SC));
   printf("-------+-----+-----+-----+-----+\n");
   return 0;
}

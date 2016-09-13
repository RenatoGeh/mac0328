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
// Data:       2016-09-07
//
// Este arquivo faz parte da tarefa F
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

/* Toma um digrafo G e retorna quantas componentes fortes estão
 * presentes em G. Guarda em G->sc as componentes fortes com rótulos
 * {0,1,2,...}, onde cada rótulo indica que o vértice de índice i está
 * na (G->sc[i])-ésima componente forte. */
int naive_sc(Digraph G) {
   int i, j, c;

   if (G->sc == NULL)
      G->sc = (int*) malloc(G->V * sizeof(int));

   for (i = 0; i < G->V; ++i)
      G->sc[i] = -1;

   c = 0;
   for (i = 0; i < G->V; ++i)
      if (G->sc[i] < 0) {
         G->sc[i] = c;
         for (j = i+1; j < G->V; ++j)
            if (G->sc[i] < 0 || G->sc[j] < 0)
               if (DIGRAPHreach(G, i, j) && DIGRAPHreach(G, j, i))
                  G->sc[j] = c;
         ++c;
      }

   return c;
}

int main(int argc, char *args[]) {
   int k, V, a, alg;
   int i, j, t;
   double tsc[NUM_EVALD_SC + 1], avg;
   Digraph G;
   int (*algs[2]) (Digraph G) = {naive_sc, DIGRAPHscKS};

   if (argc > 3) alg = atoi(args[3]);
   else alg = 2;

   V = atoi(args[1]);
   k = atoi(args[2]);

   for (i = 0; i < NUM_EVALD_SC + 1; ++i)
      tsc[i] = 0.0;

   printf("As proximas k=%d tabelas mostram o numero de vertices nas\n"
         "tres maiores componentes fortes de cada digrafo aleatorio.\n"
         "A primeira coluna mostra o numero de arestas em funcao do\n"
         "numero fixo de V=%d vertices. As tres seguintes colunas\n"
         "mostram o numero de vertices nas tres maiores componentes\n"
         "fortes de cada digrafo. A ultima coluna mostra a media de\n"
         "vertices da linha correspondente. Cada linha da tabela e'\n"
         "um digrafo aleatorio, com a ultima linha sendo a media das\n"
         "componentes fortes. ", k, V);
   printf("Algoritmo a ser utilizado:\n%s.\n\n",
         (alg == 1) ? "naive/simplorio" : "Kosaraju-Sharir");

   for (t = 0; t < k; ++t) {
      int msc[NUM_EVALD_SC + 1];

      for (i = 0; i < NUM_EVALD_SC + 1; ++i)
         msc[i] = 0;

      printf("====================================\n"
            "  Para o %d-esimo digrafo aleatorio:\n"
            "====================================\n", t+1);
      printf("%*cA |   0  |   1  |   2  |  med |\n"
            "-------+------+------+------+------+\n", 5, ' ');
      for (i = 0; i < 17;) {
         int sc[NUM_EVALD_SC];
         int q, l, last;
         avg = 0.0;

         for (j = 0; j < NUM_EVALD_SC; ++j)
            sc[j] = -1;
         if (i == 0)
            a = V/2;
         else a = i*V;

         G = DIGRAPHrand1(V, a);

         algs[alg-1](G);
         last = G->sc[0];
         for (j = l = q = 0; l < G->V; ++l) {
            if (G->sc[l] != last) {
               int c;
               for (j = 0; j < NUM_EVALD_SC; ++j)
                  if (q > sc[j]) {
                     for (c = NUM_EVALD_SC-1; c != j; --c)
                        sc[c] = sc[c + 1];
                     sc[j] = q;
                     break;
                  }
               q = 0;
               last = G->sc[l];
            }
            ++q;
         }
         if (sc[0] < 0) sc[0] = G->V;
         if (i == 0) printf("0.5*V  ");
         else printf("%3d*V  ", i);
         for (j = 0; j < NUM_EVALD_SC; ++j) {
            if (sc[j] < 0)
               printf("|   -  ");
            else {
               printf("|%6d", sc[j]);
               avg += sc[j];
               msc[j] += sc[j];
            }
         }
         msc[NUM_EVALD_SC] += avg;
         avg /= 3;
         printf("|%6.1f|\n", avg);

         if (i == 0)
            i = 1;
         else
            i <<= 1;

         DIGRAPHdestroy(G);
      }
      printf(" media ");
      for (i = 0; i < NUM_EVALD_SC; ++i) {
         avg = msc[i]/6.0;
         tsc[i] += avg;
         printf("|%6.1f", avg);
      }
      avg = msc[NUM_EVALD_SC]/(6.0*NUM_EVALD_SC);
      printf("|%6.1f|\n", avg);
      tsc[NUM_EVALD_SC] += avg;
      puts("-------+------+------+------+------+\n");
   }

   printf("Media agregada das tres primeiras componentes fortes dos\n"
         "%d digrafos aleatorios:\n\nC: numero de vertices\n", k);
   puts("-----------------------");
   for (i = 0; i < NUM_EVALD_SC; ++i)
      printf("%d: %.3f\n", i, tsc[i]/((double) k));
   puts("-----------------------");
   printf("Media das medias: %.3f\n", tsc[NUM_EVALD_SC]/((double) k));

   return 0;
}

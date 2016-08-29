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

/* Este programa aceita um arquivo gráfico pela entrada padrão e cria
 * um digrafo G representado pelo arquivo. Em seguida verifica se G
 * possue um ciclo. Se possue um ciclo, imprime os vértices contidos em
 * um dos ciclos. Senão, imprime a listagem topológica do digrafo. */

#include <stdio.h>
#include <stdlib.h>

#ifndef GRAPH
#define GRAPH 1
#endif

#if GRAPH == 0
#define GRAPH_HEADER "DIGRAPHlists.h"
#else
#define GRAPH_HEADER "DIGRAPHmatrix.h"
#endif

#include GRAPH_HEADER

/* Supõe que v faz parte de um ciclo. Faz uma DFS a partir do vértice
 * u até achar um ciclo. Quando acha, faz a "volta" imprimindo o
 * caminho. Pela hipótese anterior, print_cycle() sempre acha um ciclo
 * em tempo O(V+A). */
int print_cycle(Digraph G, Vertex v, Vertex u, int first) {
   int i;
   if (v == u && !first) return 1;
   for (i = 0; i < G->V; ++i) {
      if (i == u) continue;
      if (G->adj[u][i] && print_cycle(G, v, i, 0)) {
            printf(" %d", i);
            return 1;
      }
   }
   return 0;
}

int main(int argc, char *args[]) {
   Digraph G;
   int c, i, *top;

   G = DIGRAPHinputArcs();
   c = DIGRAPHcycleOrTopo(G);

   if (c < 0) {
      top = (int*) malloc(G->V * sizeof(int));
      for (i = G->V-1; i > -1; --i)
         top[G->pos[i]] = i;
      printf("Listagem topologica:\n  %d", top[G->V - 1]);
      for (i = G->V - 2; i > -1; --i)
         printf(" %d", top[i]);
      putchar('\n');
      free(top);
   } else {
      printf("Ciclo contem vertices:\n ");
      print_cycle(G, c, c, 1);
      putchar('\n');
   }

   DIGRAPHdestroy(G);

   return 0;
}

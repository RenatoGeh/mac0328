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
// Data:       2016-08-07
//
// Este arquivo faz parte da tarefa B
// da disciplina MAC0328.
//
////////////////////////////////////////////////////////////// */

/* Funções teste da biblioteca DIGRAPHmatrix.h. */

#include "DIGRAPHmatrix.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função DIGRAPHinit_test()
 * testa se o digrafo produzido pela função DIGRAPHinit() de fato cria
 * uma matriz de adjacência com V vértices e 0 arcos. */
static void DIGRAPHinit_test(int V) {
   int i, j;
   Digraph G;

   G = DIGRAPHinit(V);
   assert(G->V == V);
   assert(G->A == 0);
   for (i = 0; i < V; i++)
      for (j = 0; j < V; j++)
         assert(G->adj[i][j] == 0);
   DIGRAPHdestroy(G);
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função
 * DIGRAPHinsertA_test() testa se a função DIGRAPHinsertA() guarante
 * que existirá um arco v-w, onde v e w são vértices do digrafo G. */
static void DIGRAPHinsertA_test(Digraph G, Vertex v, Vertex w) {
   DIGRAPHinsertA(G, v, w);
   assert(G->adj[v][w] == 1);
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função
 * DIGRAPHremoveA_test() testa se a função DIGRAPHremoveA() guarante
 * que o arco v-w, onde v e w são vértices do digrafo G, não existirá
 * ao final da função. */
static void DIGRAPHremoveA_test(Digraph G, Vertex v, Vertex w) {
   DIGRAPHremoveA(G, v, w);
   assert(G->adj[v][w] == 0);
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função
 * DIGRAPHindeg_test()
 * testa se a função DIGRAPHindeg() de fato computa o grau de entrada
 * de um vértice no digrafo G. Assume-se que o número de vértices de G
 * é maior que dois. */
static void DIGRAPHindeg_test(Digraph G, Vertex v) {
   int d1, d2;

   DIGRAPHremoveA(G, 0, v);
   DIGRAPHremoveA(G, 1, v);
   d1 = DIGRAPHindeg(G, v);
   DIGRAPHinsertA(G, 0, v);
   DIGRAPHinsertA(G, 1, v);
   d2 = DIGRAPHindeg(G, v);
   assert(d2 == d1 + 2);

   DIGRAPHremoveA(G, 0, v);
   d2 = DIGRAPHindeg(G, v);
   assert(d2 == d1 + 1);
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função
 * DIGRAPHoutdeg_test() testa se a função DIGRAPHoutdeg() de fato
 * computa o grau de saída de um vértice no digrafo G. Assume-se que
 * o número de vértices de G é maior que dois. */
static void DIGRAPHoutdeg_test(Digraph G, Vertex v) {
   int d1, d2;

   DIGRAPHremoveA(G, v, 0);
   DIGRAPHremoveA(G, v, 1);
   d1 = DIGRAPHoutdeg(G, v);
   DIGRAPHinsertA(G, v, 0);
   DIGRAPHinsertA(G, v, 1);
   d2 = DIGRAPHoutdeg(G, v);
   assert(d2 == d1 + 2);

   DIGRAPHremoveA(G, v, 1);
   d2 = DIGRAPHoutdeg(G, v);
   assert(d2 == d1 + 1);
}

void DIGRAPHmatrix_test() {
   Digraph G;
#define V 10
   DIGRAPHinit_test(V);
   G = DIGRAPHinit(V);
   DIGRAPHinsertA(G, 1, 6);
   DIGRAPHinsertA(G, 2, 4);
   DIGRAPHinsertA(G, 4, 6);
   DIGRAPHinsertA_test(G, 1, 9);
   DIGRAPHremoveA_test(G, 2, 4);
   DIGRAPHindeg_test(G, 1);
   DIGRAPHoutdeg_test(G, 6);
   DIGRAPHdestroy(G);
#undef V
   puts("DIGRAPHmatrix passou em todos os testes.");
}

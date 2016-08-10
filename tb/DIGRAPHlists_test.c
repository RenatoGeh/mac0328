#include "DIGRAPHlists.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinit_test()
 * testa se o digrafo produzido pela função DIGRAPHinit() de fato cria
 * uma lista de adjacência com V vértices e 0 arcos. */
static void DIGRAPHinit_test(int V) {
   int i;
   Digraph G;

   G = DIGRAPHinit(V);
   assert(G->V == V);
   assert(G->A == 0);
   for (i = 0; i < V; i++) {
      link it = G->adj[i];
      assert(it == NULL);
   }
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função
 * DIGRAPHinsertA_test() testa se a função DIGRAPHinsertA() guarante
 * que existirá um arco v-w, onde v e w são vértices do digrafo G. */
static void DIGRAPHinsertA_test(Digraph G, Vertex v, Vertex w) {
   int i = 0;
   link it;

   DIGRAPHinsertA(G, v, w);
   it = G->adj[v];
   while (it != NULL) {
      if (it->w == w)
         ++i;
      it = it->next;
   }
   assert(i == 1);
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função
 * DIGRAPHremoveA_test() testa se a função DIGRAPHremoveA() guarante
 * que o arco v-w, onde v e w são vértices do digrafo G, não existirá
 * ao final da função. */
static void DIGRAPHremoveA_test(Digraph G, Vertex v, Vertex w) {
   int i = 0;
   link it;

   DIGRAPHremoveA(G, v, w);
   it = G->adj[v];
   while (it != NULL) {
      if (it->w == w)
         ++i;
      it = it->next;
   }
   assert(i == 0);
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHindeg_test()
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

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função
 * DIGRAPHoutdeg_test() testa se a função DIGRAPHoutdeg() de fato
 * computa o grau de saída de um vértice no digrafo G. Assume-se que
 * o número de vértices de G é maior que dois. */
static void DIGRAPHoutdeg_test(Digraph G, Vertex v) {
   int d1, d2;

   DIGRAPHremoveA(G, v, 3);
   DIGRAPHremoveA(G, v, 8);
   d1 = DIGRAPHoutdeg(G, v);
   DIGRAPHinsertA(G, v, 8);
   DIGRAPHinsertA(G, v, 3);
   d2 = DIGRAPHoutdeg(G, v);
   assert(d2 == d1 + 2);

   DIGRAPHremoveA(G, v, 3);
   d2 = DIGRAPHoutdeg(G, v);
   assert(d2 == d1 + 1);
}

void DIGRAPHlists_test() {
   Digraph G;
#define V 10
   DIGRAPHinit_test(V);
   G = DIGRAPHinit(V);
   DIGRAPHinsertA(G, 1, 6);
   DIGRAPHinsertA(G, 2, 4);
   DIGRAPHinsertA(G, 4, 6);
   DIGRAPHinsertA_test(G, 1, 9);
   DIGRAPHremoveA_test(G, 2, 4);
   DIGRAPHindeg_test(G, 5);
   DIGRAPHoutdeg_test(G, 7);
#undef V
   puts("DIGRAPHlists passou em todos os testes.");
}

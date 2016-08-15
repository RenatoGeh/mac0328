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
// Data:       2016-08-15
//
// Este arquivo faz parte da tarefa C
// da disciplina MAC0328.
//
////////////////////////////////////////////////////////////// */

/* Biblioteca para representação de digrafos em formato de matriz de
 * adjacência. */

#include "DIGRAPHmatrix.h"

#include <stdlib.h>
#include <stdio.h>

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXinit() aloca
 * uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da
 * matriz recebe valor val. */
static int **MATRIXinit(int r, int c, int val) {
   Vertex i, j;
   int **m = malloc(r * sizeof (int *));
   for (i = 0; i < r; i++)
      m[i] = malloc(c * sizeof (int));
   for (i = 0; i < r; i++)
      for (j = 0; j < c; j++)
         m[i][j] = val;
   return m;
}

Digraph DIGRAPHinit(int V) {
   int i;
   Digraph G = malloc(sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = MATRIXinit(V, V, 0);
   G->pre = (int*) malloc(V * sizeof(int));
   for (i = 0; i < V; ++i)
      G->pre[i] = -1;
   return G;
}

void DIGRAPHdestroy(Digraph G) {
   int i;
   for (i = 0; i < G->V; i++)
      free(G->adj[i]);
   free(G->adj);
   free(G);
}

void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w) {
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1;
      G->A++;
   }
}

void DIGRAPHremoveA(Digraph G, Vertex v, Vertex w) {
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0;
      G->A--;
   }
}

void DIGRAPHshow(Digraph G) {
   Vertex v, w;
   for (v = 0; v < G->V; v++) {
      printf("%2d:", v);
      for (w = 0; w < G->V; w++)
         if (G->adj[v][w] == 1)
            printf(" %2d", w);
      printf("\n");
   }
}

int DIGRAPHindeg(Digraph G, Vertex v) {
   int i, id = 0;
   for (i = 0; i < G->V; i++)
      id += G->adj[i][v];
   return id;
}

int DIGRAPHoutdeg(Digraph G, Vertex v) {
   int i, od = 0;
   for (i = 0; i < G->V; i++)
      od += G->adj[v][i];
   return od;
}

void DIGRAPHdraw(Digraph G, const char *filename) {
   int i, j;
   FILE *out;

   out = fopen(filename, "w");

   if (out == NULL) {
      printf("Erro ao criar arquivo %s.\n", filename);
      return;
   }

   fprintf(out, "digraph {\n");
   for (i = 0; i < G->V; i++)
      fprintf(out, "v_%d [label=\"%d\", shape=circle];\n", i, i);
   for (i = 0; i < G->V; i++)
      for (j = 0; j < G->V; j++)
         if (G->adj[i][j])
           fprintf(out, "v_%d -> v_%d;\n", i, j);
   fprintf(out, "}\n");
   fclose(out);
}

/* A função randV() devolve um vértice aleatório do digrafo G. Ela é
 * apenas um invólucro para a função rand() da biblioteca stdlib, que
 * produz um número inteiro (pseudo)aleatório no intervalo fechado
 * 0..RAND_MAX. */
static Vertex randV(Digraph G) {
   double r;
   r = rand() / (RAND_MAX + 1.0);
   return r * G->V;
}

Digraph DIGRAPHrand1(int V, int A) {
   Vertex v, w;
   Digraph G = DIGRAPHinit(V);
   while (G->A < A) {
      v = randV(G);
      w = randV(G);
      if (v != w)
         DIGRAPHinsertA(G, v, w);
   }
   return G;
}

Digraph DIGRAPHrand2(int V, int A) {
   Vertex v, w;
   double p = (double) A / V / (V-1);
   Digraph G = DIGRAPHinit(V);
   for (v = 0; v < V; v++)
      for (w = 0; w < V; w++)
         if (v != w && rand() < p*(RAND_MAX+1.0))
            DIGRAPHinsertA(G, v, w);
   return G;
}

Digraph GRAPHrand1(int V, int E) {
   Vertex v, w;
   Digraph G = DIGRAPHinit(V);
   while (2*G->A < E) {
      v = randV(G);
      w = randV(G);
      if (v != w) {
         DIGRAPHinsertA(G, v, w);
         DIGRAPHinsertA(G, w, v);
      }
   }
   return G;
}

Digraph GRAPHrand2(int V, int E) {
   Vertex v, w;
   double p = (double) (2*E) / V / (V-1);
   Digraph G = DIGRAPHinit(V);
   for (v = 0; v < V; v++)
      for (w = 0; w < V; w++)
         if (v != w && rand() < p*(RAND_MAX+1.0)) {
            DIGRAPHinsertA(G, v, w);
            DIGRAPHinsertA(G, w, v);
         }
   return G;
}

static int dfs_trailing;
/* Seja U o conjunto dos vértices u tais que pre[u] >= 0. Nesse
 * ambiente, para cada vértice x acessível a partir de v por um caminho
 * que não usa vértices de U, a função dfsR() atribui um número
 * positivo a pre[x]:  se x é o k-ésimo vértice descoberto, pre[x]
 * recebe dfs_conta+k. (Código inspirado no programa 18.1 de
 * Sedgewick.)
 * */
static int dfsR(Digraph G, Vertex v, int count) {
   Vertex w;
   G->pre[v] = count++;
   dfs_trailing += 2;
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w] != 0) {
         printf("%*c%d-%d", dfs_trailing, ' ', v, w);
         if (G->pre[w] == -1) {
            printf(" dfsR(G, %d)\n", w);
            count = dfsR(G, w, count);
         } else putchar('\n');
      }
   dfs_trailing -= 2;
   return count;
}

void DIGRAPHdfs(Digraph G) {
   Vertex v;
   int count = 0;
   dfs_trailing = 0;
   for (v = 0; v < G->V; v++)
      G->pre[v] = -1;
   for (v = 0; v < G->V; v++)
      if (G->pre[v] == -1) {
         printf("dfsR(G, %d)\n", v);
         count = dfsR(G, v, count);
      }
}

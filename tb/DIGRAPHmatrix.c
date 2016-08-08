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
  Digraph G = malloc(sizeof *G);
  G->V = V;
  G->A = 0;
  G->adj = MATRIXinit(V, V, 0);
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

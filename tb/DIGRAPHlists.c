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

/* Biblioteca para representação de digrafos em formato de lista de
 * adjacência. */

#include "DIGRAPHlists.h"

#include <stdlib.h>
#include <stdio.h>

static link NEWnode(Vertex w, link next) {
  link a = malloc(sizeof(struct node));
  a->w = w;
  a->next = next;
  return a;
}

Digraph DIGRAPHinit(int V) {
  Vertex v;
  Digraph G = malloc(sizeof *G);
  G->V = V;
  G->A = 0;
  G->adj = malloc(V * sizeof(link));
  for (v = 0; v < V; v++)
    G->adj[v] = NULL;
  return G;
}

void DIGRAPHdestroy(Digraph G) {
  int i;
  for (i = 0; i < G->V; i++) {
    link it, next;
    it = G->adj[i];
    next = NULL;
    while (it != NULL) {
      next = it->next;
      free(it);
      it = next;
    }
  }
  free(G->adj);
  free(G);
}

void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w) {
  link a;
  for (a = G->adj[v]; a != NULL; a = a->next)
    if (a->w == w) return;
  G->adj[v] = NEWnode(w, G->adj[v]);
  G->A++;
}

void DIGRAPHremoveA(Digraph G, Vertex v, Vertex w) {
  link prev = G->adj[v];
  link nb = prev;

  while (nb != NULL) {
    if (nb->w == w) {
      link next = nb->next;
      free(nb);
      prev->next = next;
      return;
    }
    prev = nb;
    nb = nb->next;
  }
}

void DIGRAPHshow(Digraph G) {
  int i;
  for (i = 0; i < G->V; i++) {
    link it = G->adj[i];
    printf("%2d:", i);
    while (it != NULL) {
      printf(" %2d", it->w);
      it = it->next;
    }
    putchar('\n');
  }
}

int DIGRAPHindeg(Digraph G, Vertex v) {
  int i, id = 0;
  for (i = 0; i < G->V; i++) {
    link nb = G->adj[i];
    while (nb != NULL) {
      if (nb->w == v) ++id;
      nb = nb->next;
    }
  }
  return id;
}

int DIGRAPHoutdeg(Digraph G, Vertex v) {
  int od = 0;
  link nb = G->adj[v];
  while (nb != NULL) {
    ++od;
    nb = nb->next;
  }
  return od;
}

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

#include "DIGRAPHmatrix.h"

/* Uma pilha implementada por meio de um vetor cíclico. */
typedef struct {
   int *data;
   int n, cap;
} stack;

/* Cria uma nova pilha com capacidade V. */
stack *new_stack(int V) {
   stack *st;
   st = (stack*) malloc(sizeof(stack));
   st->data = (int*) malloc(V * sizeof(int));
   st->n = 0;
   st->cap = V;
   return st;
}

/* Coloca o elemento v no topo da pilha st. */
void stack_push(stack *st, int v) {
   if (st->n + 1 > st->cap) {
      puts("Pilha cheia.");
      return;
   }
   st->data[st->n++] = v;
}

/* Desempilha o elemento do topo da pilha st. */
int stack_pop(stack *st) {
   if (st->n < 1) {
      puts("Pilha vazia.");
      return -1;
   }
   return st->data[--st->n];
}

/* Retorna 1 se a pilha st está vazia. 0 caso contrário. */
int stack_empty(stack *st) {
   return st->n == 0;
}

/* Libera a memória da pilha st. */
void free_stack(stack *st) {
   free(st->data);
   free(st);
}

stack *cstack;

/* Supõe que v faz parte de um ciclo. Faz uma DFS a partir do vértice
 * u até achar um ciclo. Quando acha, faz a "volta" imprimindo o
 * caminho. Pela hipótese anterior, print_cycle() sempre acha um ciclo
 * em tempo O(V+A). */
int find_cycle(Digraph G, Vertex v, Vertex u, int first) {
   int i;
   if (v == u && !first) return 1;
   for (i = 0; i < G->V; ++i) {
      if (i == u) continue;
      if (G->adj[u][i] && find_cycle(G, v, i, 0)) {
            stack_push(cstack, i);
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
      cstack = new_stack(G->V);
      printf("Ciclo contem vertices:\n ");
      find_cycle(G, c, c, 1);
      printf("%d", stack_pop(cstack));
      while (!stack_empty(cstack))
         printf("-%d", stack_pop(cstack));
      putchar('\n');
      free_stack(cstack);
   }

   DIGRAPHdestroy(G);

   return 0;
}

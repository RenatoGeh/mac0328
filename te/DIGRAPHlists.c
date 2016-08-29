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
   G->pre = G->pos = G->pai = NULL;
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
   free(G->pre);
   free(G->pos);
   free(G->pai);
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
         if (prev == G->adj[v])
            G->adj[v] = next;
         else
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
         if (nb->w == v)
            ++id;
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

void DIGRAPHdraw(Digraph G, const char *filename) {
   int i;
   FILE *out;

   out = fopen(filename, "w");

   if (out == NULL) {
      printf("Erro ao criar arquivo %s.\n", filename);
      return;
   }

   fprintf(out, "digraph {\n");
   for (i = 0; i < G->V; i++)
      fprintf(out, "v_%d [label=\"%d\", shape=circle];\n", i, i);
   for (i = 0; i < G->V; i++) {
         link it = G->adj[i];
      while (it != NULL) {
         fprintf(out, "v_%d -> v_%d;\n", i, it->w);
         it = it->next;
      }
   }
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

static int pre_count, pos_count;
/* Seja U o conjunto dos vértices u tais que pre[u] >= 0. Nesse
 * ambiente, para cada vértice x acessível a partir de v por um caminho
 * que não usa vértices de U, a função dfsR() atribui um número
 * positivo a pre[x]:  se x é o k-ésimo vértice descoberto, pre[x]
 * recebe dfs_conta+k. (Código inspirado no programa 18.1 de
 * Sedgewick.)
 * */
static void dfsR(Digraph G, Vertex v) {
   link it;
   G->pre[v] = pre_count++;
   for (it = G->adj[v]; it != NULL; it = it->next)
      if (G->pre[it->w] == -1) {
         G->pai[it->w] = v;
         dfsR(G, it->w);
      }
   G->pos[v] = pos_count++;
}

void DIGRAPHdfs(Digraph G) {
   Vertex v;

   if (G->pre == NULL) {
      G->pre = (int*) malloc(G->V * sizeof(int));
      G->pos = (int*) malloc(G->V * sizeof(int));
      G->pai = (int*) malloc(G->V * sizeof(int));
   }

   pre_count = pos_count = 0;
   for (v = 0; v < G->V; v++)
      G->pre[v] = -1;
   for (v = 0; v < G->V; v++)
      if (G->pre[v] == -1)
         dfsR(G, v);
}

/* A função cycleR() devolve um vértice contido no ciclo se encontra um
 * ciclo ao percorrer G a partir do vértice v e devolve -1 em caso
 * contrário. */
static bool cycleR(Digraph G, Vertex v) {
   link a;
   G->pre[v] = pre_count++;
   for (a = G->adj[v]; a != NULL; a = a->next) {
      Vertex w = a->w;
      if (G->pre[w] == -1) {
         G->pai[a->w] = v;
         if (cycleR(G, w) >= 0)
            return w;
      } else if (G->pos[w] == -1)
         return w; /* v-w é de retorno */
   }
   G->pos[v] = pos_count++;
   return -1;
}

bool DIGRAPHcycle(Digraph G) {
   Vertex v;

   if (G->pre == NULL) {
      G->pre = (int*) malloc(G->V * sizeof(int));
      G->pos = (int*) malloc(G->V * sizeof(int));
      G->pai = (int*) malloc(G->V * sizeof(int));
   }

   pre_count = pos_count = 0;
   for (v = 0; v < G->V; v++)
      G->pre[v] = G->pos[v] = -1;
   for (v = 0; v < G->V; v++)
      if (G->pre[v] == -1)
         if (cycleR(G, v) >= 0) return TRUE;
   return FALSE;
}

Vertex DIGRAPHcycleOrTopo(Digraph G) {
   Vertex v, w;

   if (G->pre == NULL) {
      G->pre = (int*) malloc(G->V * sizeof(int));
      G->pos = (int*) malloc(G->V * sizeof(int));
      G->pai = (int*) malloc(G->V * sizeof(int));
   }

   pre_count = pos_count = 0;
   for (v = 0; v < G->V; v++)
      G->pre[v] = G->pos[v] = -1;
   for (v = 0; v < G->V; v++)
      if (G->pre[v] == -1)
         if ((w = cycleR(G, v)) >= 0) return w;
   return -1;
}

/* Considera que o número de vértices não ultrapassa os 10 dígitos, ou
 * seja, que não ultrapassa o máximo número de dígitos que int pode
 * guardar (INT_MAX = 2147483647). */
#define BUFFER_SIZE 22
Digraph DIGRAPHinputArcs() {
   Digraph G;
   int V;
   char buffer[BUFFER_SIZE];

   scanf("%d", &V);
   G = DIGRAPHinit(V);
   while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
      int u, v;
      if (buffer[0] == '\n') break;
      sscanf(buffer, "%d %d", &u, &v);
      DIGRAPHinsertA(G, u, v);
   }

   return G;
}
#undef BUFFER_SIZE

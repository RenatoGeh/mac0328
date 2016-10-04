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

/* Biblioteca para representação de digrafos em formato de matriz de
 * adjacência. */

#include "DIGRAPHmatrix.h"

#include <stdlib.h>
#include <stdio.h>

#define PPP_IS_NULL(G) ((G)->pre == NULL || (G)->pos == NULL ||\
      (G)->pai == NULL)
#define SCORD_IS_NULL(G) ((G)->sc == NULL || (G)->ord == NULL)
#define VISIT_IS_NULL(G) ((G)->visit == NULL)

void init_ppp(Digraph G) {
   G->pre = (int*) malloc(G->V * sizeof(int));
   G->pai = (int*) malloc(G->V * sizeof(int));
   G->pos = (int*) malloc(G->V * sizeof(int));
}

void init_scord(Digraph G) {
   G->sc = (int*) malloc(G->V * sizeof(int));
   G->ord = (int*) malloc(G->V * sizeof(int));
}

static void init_visit(Digraph G) {
   G->visit = (int*) malloc(G->V * sizeof(int));
}

static void free_ppp(Digraph G) {
   free(G->pre);
   free(G->pai);
   free(G->pos);
}

static void free_scord(Digraph G) {
   free(G->sc);
   free(G->ord);
}

static void free_visit(Digraph G) {
   free(G->visit);
}

#define CHECK_PPP(G) if (PPP_IS_NULL(G)) init_ppp(G)
#define CHECK_SCORD(G) if (SCORD_IS_NULL(G)) init_scord(G)
#define CHECK_VISIT(G) if (VISIT_IS_NULL(G)) init_visit(G)

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
   G->pre = G->pos = G->pai = NULL;
   G->sc = G->ord = NULL;
   G->visit = NULL;
   return G;
}

void DIGRAPHdestroy(Digraph G) {
   int i;
   for (i = 0; i < G->V; i++)
      free(G->adj[i]);
   free(G->adj);
   free_ppp(G);
   free_scord(G);
   free_visit(G);
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

static int pre_count, pos_count;
/* Seja U o conjunto dos vértices u tais que pre[u] >= 0. Nesse
 * ambiente, para cada vértice x acessível a partir de v por um caminho
 * que não usa vértices de U, a função dfsR() atribui um número
 * positivo a pre[x]:  se x é o k-ésimo vértice descoberto, pre[x]
 * recebe dfs_conta+k. (Código inspirado no programa 18.1 de
 * Sedgewick.)
 * */
static void dfsR(Digraph G, Vertex v) {
   Vertex w;
   G->pre[v] = pre_count++;
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w] != 0)
         if (G->pre[w] == -1) {
            G->pai[v] = w;
            dfsR(G, w);
         }
   G->pos[v] = pos_count++;
}

void DIGRAPHdfs(Digraph G) {
   Vertex v;
   CHECK_PPP(G);
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
   int w;
   G->pre[v] = pre_count++;
   for (w = 0; w < G->V; ++w) {
      if (!G->adj[v][w]) continue;
      if (G->pre[w] == -1) {
         int r;
         G->pai[w] = v;
         if ((r = cycleR(G, w)) >= 0)
            return r;
      } else if (G->pos[w] == -1)
         return w; /* v-w é de retorno */
   }
   G->pos[v] = pos_count++;
   return -1;
}

bool DIGRAPHcycle(Digraph G) {
   Vertex v;
   CHECK_PPP(G);
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
   CHECK_PPP(G);
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
   int V, a;

   scanf("%d ", &V);
   scanf("%d ", &a);
   G = DIGRAPHinit(V);
   while (a--) {
      int u, v;
      scanf("%d %d ", &u, &v);
      DIGRAPHinsertA(G, u, v);
   }

   return G;
}
#undef BUFFER_SIZE

static void dfsRsc(Digraph G, Vertex v, int k) {
   int w;
   G->sc[v] = k;
   for (w = 0; w < G->V; ++w)
      if (G->adj[v][w] && w != v && G->sc[w] == -1)
         dfsRsc(G, w, k);
}

/* Esta função implementa o algoritmo de Kosaraju-Sharir de cálculo das
 * componentes fortes de um digrafo G. A função atribui um rótulo sc[v]
 * (os rótulos são 0,1,2,...) a cada vértice v de G de modo que dois
 * vértices tenham o mesmo rótulo se e somente se os dois pertencem à
 * mesma componente forte. A função devolve o número (quantidade) de
 * componentes fortes de G. (O código é adaptado do Programa 19.10 de
 * Sedgewick.) */
int DIGRAPHscKS(Digraph G) {
   int k, i;
   Vertex v;
   Digraph GR = DIGRAPHreverse(G);
   init_ppp(GR);
   CHECK_PPP(G);
   CHECK_SCORD(G);
   pre_count = pos_count = 0;

   /* 1a fase */
   for (v = 0; v < GR->V; v++)
      GR->pre[v] = -1;
   for (v = 0; v < GR->V; v++)
      if (GR->pre[v] == -1)
         dfsR(GR, v);
   for (v = 0; v < GR->V; v++)
      G->ord[GR->pos[v]] = v; /* ordenamento dos vértices */

   /* 2a fase */
   for (v = 0; v < G->V; v++)
      G->sc[v] = -1;
   for (k = 0, i = G->V-1; i >= 0; i--) {
      v = G->ord[i];
      if (G->sc[v] == -1) {
         dfsRsc(G, v, k);
         k++;
      }
   }
   DIGRAPHdestroy(GR);
   return k;
}

/* Constrói o inverso do digrafo G. */
Digraph DIGRAPHreverse(Digraph G) {
   Vertex v, w;
   Digraph GR = DIGRAPHinit(G->V);
   for (v = 0; v < G->V; ++v)
      for (w = 0; w < G->V; ++w)
         if (G->adj[v][w] && w != v)
            DIGRAPHinsertA(GR, w, v);
   return GR;
}

static void reachR(Digraph G, Vertex v) {
   Vertex w;
   G->visit[v] = 1;
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w] == 1 && G->visit[w] == 0)
         reachR(G, w);
}

bool DIGRAPHreach(Digraph G, Vertex s, Vertex t) {
   Vertex v;
   CHECK_VISIT(G);
   for (v = 0; v < G->V; v++)
      G->visit[v] = 0;
   reachR(G, s);
   if (G->visit[t] == 0) return FALSE;
   else return TRUE;
}

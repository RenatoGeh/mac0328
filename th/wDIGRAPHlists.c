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
// Data:       2016-11-28
//
// Este arquivo faz parte da tarefa H
// da disciplina MAC0328.
//
////////////////////////////////////////////////////////////// */

/* Biblioteca para representação de digrafos em formato de lista de
 * adjacência. */

#include "wDIGRAPHlists.h"

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "PQ.h"

#define INFINITE DBL_MAX

/************** Digraph struct components ***************/

#define PPP_IS_NULL(G) ((G)->pre == NULL || (G)->pos == NULL ||\
      (G)->pai == NULL)
#define SCORD_IS_NULL(G) ((G)->sc == NULL || (G)->ord == NULL)
#define VISIT_IS_NULL(G) ((G)->visit == NULL)
#define COLOR_IS_NULL(G) ((G)->color == NULL)
#define DIST_IS_NULL(G) ((G)->dist == NULL)
#define NUM_IS_NULL(G) ((G)->num == NULL)
#define FRJ_IS_NULL(G) ((G)->frj == NULL)

static void init_ppp(Digraph G) {
   G->pre = (int*) malloc(G->V * sizeof(int));
   G->pai = (int*) malloc(G->V * sizeof(int));
   G->pos = (int*) malloc(G->V * sizeof(int));
}

static void init_scord(Digraph G) {
   G->sc = (int*) malloc(G->V * sizeof(int));
   G->ord = (int*) malloc(G->V * sizeof(int));
}

static void init_visit(Digraph G) {
   G->visit = (int*) malloc(G->V * sizeof(int));
}

static void init_color(Digraph G) {
   G->color = (int*) malloc(G->V * sizeof(int));
}

static void init_dist(Digraph G) {
   G->dist = (double*) malloc(G->V * sizeof(double));
}

static void init_num(Digraph G) {
   G->num = (int*) malloc(G->V * sizeof(int));
}

static void init_frj(Digraph G) {
   G->frj = (Vertex*) malloc(G->V * sizeof(Vertex));
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

static void free_color(Digraph G) {
   free(G->color);
}

static void free_dist(Digraph G) {
   free(G->dist);
}

static void free_num(Digraph G) {
   free(G->num);
}

static void free_frj(Digraph G) {
   free(G->num);
}

#define CHECK_PPP(G) if (PPP_IS_NULL(G)) init_ppp(G)
#define CHECK_SCORD(G) if (SCORD_IS_NULL(G)) init_scord(G)
#define CHECK_VISIT(G) if (VISIT_IS_NULL(G)) init_visit(G)
#define CHECK_COLOR(G) if (COLOR_IS_NULL(G)) init_color(G)
#define CHECK_DIST(G) if (DIST_IS_NULL(G)) init_dist(G)
#define CHECK_NUM(G) if (NUM_IS_NULL(G)) init_num(G)
#define CHECK_FRJ(G) if (FRJ_IS_NULL(G)) init_frj(G)

/***************** QUEUE functions **********************/

/* Fila circular. */
Vertex *_queue;
int _queue_capacity, _queue_size;
int _queue_start, _queue_end;

/* Cria uma nova fila com V vértices de capacidade. */
void QUEUEinit(int V) {
   _queue = (Vertex*) malloc(V*sizeof(Vertex));
   _queue_capacity = V;
   _queue_size = _queue_start = _queue_end = 0;
}

/* Insere um vértice v na fila. Retorna -1 se a fila está cheia, ou
 * o número de vértices na fila após a inserção caso contrário. */
int QUEUEput(Vertex v) {
   if (_queue_size >= _queue_capacity)
      return -1;
   _queue[_queue_end++ % _queue_capacity] = v;
   return ++_queue_size;
}

/* Tira o primeiro vértice da fila e retorna-o. Se a fila já estiver
 * vazia, retorna -1. */
Vertex QUEUEget() {
   if (_queue_size <= 0)
      return -1;
   --_queue_size;
   return _queue[_queue_start++ % _queue_capacity];
}

/* Retorna se a fila está vazia. */
boolean QUEUEempty() {
   return _queue_size == 0;
}

/* Libera a memória da fila. */
void QUEUEfree() {
   free(_queue);
}

/************* DIGRAPH/GRAPH functions ******************/

static link NEWnode(Vertex w, link next, double cst) {
   link a = malloc(sizeof(struct node));
   a->w = w;
   a->cst = cst;
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
   G->sc = G->ord = NULL;
   G->visit = NULL;
   G->color = NULL;
   G->dist = NULL;
   G->num = NULL;
   G->frj = NULL;
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
   free_ppp(G);
   free_scord(G);
   free_visit(G);
   free_color(G);
   free_num(G);
   free_dist(G);
   free_frj(G);
   free(G);
}

void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w, double cst) {
   link a;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w) return;
   G->adj[v] = NEWnode(w, G->adj[v], cst);
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
         printf(" %2d (%.2f)", it->w, it->cst);
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
         DIGRAPHinsertA(G, v, w, (double) rand());
   }
   return G;
}

Digraph DIGRAPHrand2(int V, int A, double cmin, double cmax) {
   Vertex v, w;
   double p = (double) A / V / (V-1);
   Digraph G = DIGRAPHinit(V);
   for (v = 0; v < V; v++)
      for (w = 0; w < V; w++)
         if (v != w && rand() < p*(RAND_MAX+1.0)) {
            double c = (cmax - cmin)*(rand()/(RAND_MAX + 1.0)) + cmin;
            DIGRAPHinsertA(G, v, w, c);
         }
   return G;
}

Digraph GRAPHrand1(int V, int E) {
   Vertex v, w;
   Digraph G = DIGRAPHinit(V);
   while (2*G->A < E) {
      v = randV(G);
      w = randV(G);
      if (v != w) {
         double cst = rand();
         DIGRAPHinsertA(G, v, w, cst);
         DIGRAPHinsertA(G, w, v, cst);
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
            double cst = rand();
            DIGRAPHinsertA(G, v, w, cst);
            DIGRAPHinsertA(G, w, v, cst);
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
static boolean cycleR(Digraph G, Vertex v) {
   link a;
   G->pre[v] = pre_count++;
   for (a = G->adj[v]; a != NULL; a = a->next) {
      Vertex w = a->w;
      if (G->pre[w] == -1) {
         int r;
         G->pai[a->w] = v;
         if ((r = cycleR(G, w)) >= 0)
            return r;
      } else if (G->pos[w] == -1)
         return w; /* v-w é de retorno */
   }
   G->pos[v] = pos_count++;
   return -1;
}

boolean DIGRAPHcycle(Digraph G) {
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
      double cst;
      scanf("%d %d %lf ", &u, &v, &cst);
      DIGRAPHinsertA(G, u, v, cst);
   }

   return G;
}
#undef BUFFER_SIZE

static void dfsRsc(Digraph G, Vertex v, int k) {
   link a;
   G->sc[v] = k;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (G->sc[a->w] == -1)
         dfsRsc(G, a->w, k);
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
   link a;
   Digraph GR = DIGRAPHinit(G->V);
   for (v = 0; v < G->V; v++)
      for (a = G->adj[v]; a != NULL; a = a->next) {
         w = a->w;
         DIGRAPHinsertA(GR, w, v, a->cst);
      }
   return GR;
}

static void reachR(Digraph G, Vertex v) {
   link a;
   G->visit[v] = 1;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (G->visit[a->w] == 0)
         reachR(G, a->w);
}

boolean DIGRAPHreach(Digraph G, Vertex s, Vertex t) {
   Vertex v;
   CHECK_VISIT(G);
   for (v = 0; v < G->V; v++)
      G->visit[v] = 0;
   reachR(G, s);
   if (G->visit[t] == 0) return FALSE;
   else return TRUE;
}

void DIGRAPHbfs(Digraph G, Vertex s) {
   Vertex v;
   int count;

   CHECK_PPP(G);
   CHECK_NUM(G);

   count = 0;
   for (v = 0; v < G->V; v++)
      G->num[v] = G->pai[v] = -1;
   QUEUEinit(G->V);
   G->num[s] = count++;
   G->pai[s] = s;
   QUEUEput(s);

   while (!QUEUEempty()) {
      link a;
      v = QUEUEget();
      for (a = G->adj[v]; a != NULL; a = a->next)
         if (G->num[a->w] == -1) {
            G->num[a->w] = count++;
            G->pai[a->w] = v;
            QUEUEput(a->w);
         }
   }
   QUEUEfree();
}

void DIGRAPHdist(Digraph G, Vertex s) {
   const int INF = G->V;
   Vertex v;

   CHECK_PPP(G);
   CHECK_DIST(G);

   for (v = 0; v < G->V; v++)
      G->dist[v] = INF;
   QUEUEinit(G->V);
   G->dist[s] = 0;
   G->pai[s] = s;
   QUEUEput(s);

   while (!QUEUEempty()) {
      link a;
      v = QUEUEget();
      for (a = G->adj[v]; a != NULL; a = a->next)
         if (G->dist[a->w] == INF) {
            G->dist[a->w] = G->dist[v] + 1;
            G->pai[a->w] = v;
            QUEUEput(a->w);
         }
   }
   QUEUEfree();
}

boolean dfsRcolor(Graph G, Vertex v, int clr) {
   link a;
   G->color[v] = clr;
   for (a = G->adj[v]; a != NULL; a = a->next) {
      Vertex w = a->w;
      if (G->color[w] == -1) {
         if (dfsRcolor(G, w, 1-clr) == FALSE)
            return FALSE;
      }
      else { /* v-w é arco de retorno */
         if (G->color[w] == clr) /* base da recursão */
            return FALSE;
      }
   }
   return TRUE;
}

void GRAPHinsertE(Graph G, Vertex v, Vertex w, double cst) {
   DIGRAPHinsertA(G, v, w, cst);
   DIGRAPHinsertA(G, w, v, cst);
}

void GRAPHremoveE(Digraph G, Vertex v, Vertex w) {
   DIGRAPHremoveA(G, v, w);
   DIGRAPHremoveA(G, w, v);
}

boolean GRAPHtwocolor(Graph G) {
   Vertex v;
   CHECK_COLOR(G);
   for (v = 0; v < G->V; v++)
      G->color[v] = -1; /* incolor */
   for (v = 0; v < G->V; v++)
      if (G->color[v] == -1) /* começa nova etapa */
         if (dfsRcolor(G, v, 0) == FALSE)
            return FALSE;
   return TRUE;
}

static int cycle_count;
/* A função cycle3R() devolve TRUE se encontrar um ciclo não trivial ao
 * percorrer G a partir do vértice v. */
static boolean cycle3R(Graph G, Vertex v) {
   link a;
   G->pre[v] = cycle_count++;
   for (a = G->adj[v]; a != NULL; a = a->next) {
      Vertex w = a->w;
      if (G->pre[w] == -1) {
         G->pai[w] = v;
         if (cycle3R(G, w))
            return TRUE;
      } else { /* v-w é arco de retorno */
         if (w != G->pai[v]) /* base da recursão */
            return TRUE;
      }
   }
   return FALSE;
}

boolean GRAPHhasCycle(Graph G) {
   Vertex v;
   CHECK_PPP(G);
   cycle_count = 0;
   for (v = 0; v < G->V; v++)
      G->pre[v] = -1;
   for (v = 0; v < G->V; v++)
      if (G->pre[v] == -1) {
         G->pai[v] = v; /* v é uma raiz */
         if (cycle3R(G, v)) return TRUE;
      }
   return FALSE;
}

Graph GRAPHclosePoints(int V, double d) {
   Graph G;
   Vertex i, j;
   double *x, *y;

   G = DIGRAPHinit(V);
   x = (double*) malloc(V*sizeof(double));
   y = (double*) malloc(V*sizeof(double));

   for (i = 0; i < V; ++i) {
      x[i] = (double) rand() / (RAND_MAX + 1.0);
      y[i] = (double) rand() / (RAND_MAX + 1.0);
   }

   d *= d;
   for (i = 0; i < V; ++i)
      for (j = i + 1; j < V; ++j) {
         double dx, dy, dt;
         dx = x[i] - x[j];
         dy = y[i] - y[j];
         dt = dx*dx + dy*dy;
         if (dt <= d)
            GRAPHinsertE(G, i, j, dt);
      }

   free(x);
   free(y);
   return G;
}

void GRAPHaddRandEdges(Graph G, int k) {
   int i;
   Vertex v;
   for (v = 0; v < G->V; ++v)
      for (i = 0; i < k ; ++i)
         GRAPHinsertE(G, v, randV(G), rand());
}

double GRAPHsmallWorld(Graph G) {
   Vertex v, w;
   double mean;
   int n;
   const int INF = G->V+1;

   n = G->V;
   mean = 0.0;
   for (v = 0; v < n; ++v) {
      DIGRAPHdist(G, v);
      for (w = 0; w < n; ++w)
         if (v != w) {
            if (G->dist[w] == INF)
               return INF;
            mean += G->dist[w];
         }
   }
   return mean / ((n-1)*n);
}

void DIGRAPHsptD0(Digraph G, Vertex s) {
   Vertex v;
   CHECK_PPP(G);
   CHECK_DIST(G);

   for (v = 0; v < G->V; v++)
      G->pai[v] = -1, G->dist[v] = INFINITE;
   G->pai[s] = s, G->dist[s] = 0.0;

   while (TRUE) {
      Vertex x, y;
      double min = INFINITE;
      for (v = 0; v < G->V; v++) {
         link a;
         if (G->pai[v] == -1) continue;
         for (a = G->adj[v]; a != NULL; a = a->next) {
            if (G->pai[a->w] == -1 && G->dist[v] + a->cst < min) {
               min = G->dist[v] + a->cst;
               x = v, y = a->w;
            }
         }
      }
      if (min == INFINITE) /*A*/ break;
      G->pai[y] = x, G->dist[y] = min;
   }
}

void DIGRAPHsptD1(Digraph G, Vertex s) {
   Vertex y; link a;
   CHECK_FRJ(G);
   CHECK_PPP(G);
   CHECK_DIST(G);
   for (y = 0; y < G->V; y++)
      G->pai[y] = -1, G->dist[y] = INFINITE;
   G->pai[s] = s, G->dist[s] = 0.0;
   for (a = G->adj[s]; a != NULL; a = a->next) {
      G->dist[a->w] = a->cst;
      G->frj[a->w] = s;
   }
   while (TRUE) {
      Vertex z;
      double min = INFINITE;
      for (z = 0; z < G->V; z++)
         if (G->pai[z] == -1 && G->dist[z] < min)
            min = G->dist[y = z];
      if (min == INFINITE) break;
      G->pai[y] = G->frj[y];
      for (a = G->adj[y]; a != NULL; a = a->next) {
         /* atualização da franja e dos preços */
         Vertex w = a->w; double c = a->cst;
         if (G->pai[w] == -1 && !(G->dist[y] + c >= G->dist[w])) {
            G->dist[w] = G->dist[y] + c; /* relaxação de y-w */
            G->frj[w] = y;
         }
      }
   }
}

/* Recebe um digrafo G com custos positivos nos arcos e um vértice s.
 * Calcula uma SPT com raiz s. A SPT é armazenada no vetor G->pai[]. As
 * G->distâncias a partir de s são armazenadas no vetor G->dist[]. (Se
 * um vértice v não está ao alcance de s, G->pai[v] vale -1.) Esta
 * função implementa o algoritmo de Dijkstra. Ela supõe que G é
 * representado por listas de adjacência e tem no máximo 1000
 * vértices. (O código foi inspirado nos Programas 20.4, e 21.1 de
 * Sedgewick.) */
void DIGRAPHsptD2(Digraph G, Vertex s) {
   Vertex y; link a;
   CHECK_FRJ(G);
   CHECK_PPP(G);
   CHECK_DIST(G);
   for (y = 0; y < G->V; y++)
      G->pai[y] = G->frj[y] = -1;
   G->pai[s] = s, G->dist[s] = 0.0;
   PQinit(G->V);
   for (a = G->adj[s]; a != NULL; a = a->next) {
      G->dist[a->w] = a->cst;
      PQinsert(a->w, G->dist);
      G->frj[a->w] = s;
   }
   while (!PQempty()) {
      y = PQdelmin(G->dist);
      G->pai[y] = G->frj[y];
      for (a = G->adj[y]; a != NULL; a = a->next) {
         Vertex w = a->w; double c = a->cst;
         if (G->pai[w] != -1) continue;
         if (G->frj[w] == -1) {       /* G->dist[w] indefinido */
            G->dist[w] = G->dist[y] + c; /* relaxação de y-w */
            PQinsert(w, G->dist);
            G->frj[w] = y;
         }
         else if (!(G->dist[y] + c >= G->dist[w])) {
            G->dist[w] = G->dist[y] + c; /* relaxação de y-w */
            PQdec(w, G->dist);
            G->frj[w] = y;
         }
      }
   }
   PQfree();
}

static int cdR(Digraph G, Vertex s, Vertex v, double c, double *dist) {
   link a;
   G->pai[v] = pre_count++;
   if (dist[s] + c < dist[v]) return FALSE;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (!cdR(G, v, a->w, a->cst, dist))
         return FALSE;
   return TRUE;
}

int DIGRAPHcheckDist(Digraph G, Vertex s, double *dist) {
   link a;
   Vertex v;
   CHECK_PPP(G);
   pre_count = 0;
   for (v = 0; v < G->V; ++v)
      G->pai[v] = -1;
   for (a = G->adj[s]; a != NULL; a = a->next)
      if (!cdR(G, s, a->w, a->cst, dist))
         return FALSE;
   for (v = 0; v < G->V; ++v)
      if (G->pai[v] < 0 && dist[v] < INFINITE)
         return FALSE;
   return TRUE;
}

Vertex* DIGRAPHpath(Vertex t, Vertex *T, int n) {
   Vertex *p, v;
   v = t;
   p = (Vertex*) malloc(n * sizeof(Vertex));
   do {
      p[--n] = v;
      v = T[v];
   } while (v != T[v]);
   p[n-1] = v;
   return p;
}

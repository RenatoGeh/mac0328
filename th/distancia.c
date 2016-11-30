#include <stdio.h>
#include <stdlib.h>

#include "wDIGRAPHlists.h"

void (* const IMPL[3])(Digraph, Vertex) = {
   DIGRAPHsptD0, DIGRAPHsptD1, DIGRAPHsptD2
};

void print_diameter(Digraph G, void (*f)(Digraph, Vertex));
void print_delta(Digraph G, Vertex s);

int main(int argc, char *args[]) {
   int V, A, s, impl, seed;
   void (*f)(Digraph, Vertex);
   Digraph G;

   if (argc != 6) {
      printf("Uso: %s V A s impl seed\n"
            "  V    - numero de vertices\n"
            "  A    - numero de arestas\n"
            "  s    - vertice a ser medido\n"
            "  impl - implementacao da distancia\n"
            "  seed - semente para o gerador\n", args[0]);
      return 1;
   }

   V = atoi(args[1]);
   A = atoi(args[2]);
   s = atoi(args[3]);
   impl = atoi(args[4]);
   seed = atoi(args[5]);

   f = IMPL[impl];

   srand(seed);
   G = DIGRAPHrand2(V, A, 0, 1);

   if (V < 30) {
      printf("Imprimindo o digrafo G com %d vertices e %d arestas. Os "
            "pesos de cada aresta e' impresso em parenteses:\n", V, A);
      DIGRAPHshow(G);
   }

   DIGRAPHdraw(G, "graph.dot");
   f(G, s);
   if (!DIGRAPHcheckDist(G, s, G->dist))
      printf("Distancia medida com DIGRAPHsptD%d errada!\n", impl);
   else
      printf("Distancia medida com DIGRAPHsptD%d correta!\n", impl);

   print_delta(G, s);
   print_diameter(G, f);

   return 0;
}

double min(double l, double r) { return l > r ? r : l; }
double max(double l, double r) { return l < r ? r : l; }

int count;

double deltaR(Digraph G, Vertex s, Vertex v, double c, Vertex *p,
      Vertex *q) {
   link a;
   double delta;
   G->pai[v] = count++;
   delta = (G->dist[s] + c) - G->dist[v];
   delta = min(c, max(delta, 0));
   for (a = G->adj[v]; a != NULL; a = a->next) {
      double d;
      if (G->pai[a->w] != -1) {
         d = (G->dist[v] + a->cst) - G->dist[a->w];
         d = min(a->cst, max(d, 0));
         if (d > delta) {
            delta = d;
            *p = v; *q = a->w;
         }
      } else {
         d = deltaR(G, v, a->w, a->cst, p, q);
         if (d > delta) {
            delta = d;
            *p = v; *q = a->w;
         }
      }
   }
   return delta;
}

void print_delta(Digraph G, Vertex s) {
   link a;
   Vertex v, p, q;
   double max = -1;

   count = 0;
   for (v = 0; v < G->V; ++v)
      G->pai[v] = -1;
   for (a = G->adj[s]; a != NULL; a = a->next) {
      double d = deltaR(G, s, a->w, a->cst, &p, &q);
      if (d > max) {
         max = d;
         p = s; q = a->w;
      }
   }

   if (max < 0)
      puts("Nao foi possivel achar delta pois s e' um no' disjunto "
            "dos outros vertices.");
   else if (max == 0)
      puts("Nenhum custo pode ser alterado sem alterar a arvore.");
   else
      printf("delta[%d-%d]=%.4f\n", p, q, max);
}

void print_diameter(Digraph G, void (*f)(Digraph, Vertex)) {
   int show;
   Vertex v, vmax;
   Vertex *cpai, *path;
   double max, inf;

   show = G->V < 30;
   if (show) cpai = (Vertex*) malloc(G->V * sizeof(Vertex));
   max = vmax = -1;
   inf = DIGRAPHinf(G);

   for (v = 0; v < G->V; ++v) {
      Vertex w, y = -1;
      f(G, v);
      for (w = 0; w < G->V; ++w)
         if (w != v && G->dist[w] < inf && G->dist[w] > max) {
            max = G->dist[w];
            y = w;
         }
      if (show && y >= 0) {
         for (w = 0; w < G->V; ++w)
            cpai[w] = G->pai[w];
         vmax = y;
      }
   }

   if (max < 0) {
      puts("O digrafo nao tem arestas.");
      return;
   }

   printf("Diametro: %.2f\n", max);
   if (show) {
      int i, n;
      path = DIGRAPHpath(vmax, cpai, G->V, &n);
      printf("Caminho do diametro (tamanho n=%d):\n", n);
      for (i = 1; i <= n; ++i)
         printf("%3d -> %3d\n", path[i-1], path[i]);
      free(cpai);
      free(path);
   }
}

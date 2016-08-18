#include <stdio.h>
#include <stdlib.h>

#include "DIGRAPHmatrix.h"

Vertex **dfs_path;

int path_exists(int V, Vertex v, Vertex w) {
   int i;
   if (v == w) return 1;
   for (i = 0; i < V; ++i)
      if (dfs_path[v][i] == 1)
         return path_exists(V, i, w);
   return 0;
}

int dfs_trailing, pre_count, pos_count;

void dfsR(Digraph G, Vertex v) {
   Vertex w;
   G->pre[v] = pre_count++;
   dfs_trailing += 2;
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w] != 0) {
         printf("%*c%d-%d ", dfs_trailing, ' ', v, w);
         if (G->pre[w] == -1) {
            G->pai[v] = w;
            dfs_path[w][v] = 1;
            puts("floresta");
            dfsR(G, w);
         } else {
            if (path_exists(G->V, w, v))
               puts("descendente");
            else if (path_exists(G->V, v, w))
               puts("retorno");
            else
               puts("cruzado");
         }
      }
   G->pos[v] = pos_count++;
   dfs_trailing -= 2;
}

void dfs_rastro(Digraph G) {
   Vertex v;
   dfs_trailing = pre_count = pos_count = 0;
   for (v = 0; v < G->V; v++)
      G->pre[v] = -1;
   for (v = 0; v < G->V; v++)
      if (G->pre[v] == -1)
         dfsR(G, v);
}

int main(int argc, char *args[]) {
   int i, j;
   Digraph G;

#define V 7
   G = DIGRAPHinit(V);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 2);
   DIGRAPHinsertA(G, 1, 3);
   DIGRAPHinsertA(G, 3, 4);
   DIGRAPHinsertA(G, 4, 5);
   DIGRAPHinsertA(G, 5, 6);
   DIGRAPHinsertA(G, 6, 3);
   DIGRAPHinsertA(G, 4, 2);
   DIGRAPHinsertA(G, 5, 2);

   dfs_path = (Vertex**) malloc(V * sizeof(Vertex*));
   for (i = 0; i < V; ++i) {
      dfs_path[i] = (Vertex*) malloc(V * sizeof(Vertex));
      for (j = 0; j < V; ++j)
         dfs_path[i][j] = 0;
   }

   dfs_rastro(G);

   DIGRAPHdestroy(G);
#undef V

   return 0;
}

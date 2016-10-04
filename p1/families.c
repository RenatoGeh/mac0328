#include <stdio.h>
#include <stdlib.h>

#include "DIGRAPHlists.h"

int *get_top(Digraph G, int *top) {
   Digraph H;
   int i, t, *indeg;

   DIGRAPHinit(H, G->V);
   indeg = (int*) malloc(G->V * sizeof(int));

   for (i = 0; i < G->V; ++i)
      indeg[i] = 0;

   for (i = 0; i < G->V; ++i) {
      link it;
      for (it = G->adj[i]; it != NULL; it = it->next) {
         DIGRAPHinsertA(H, i, it->w);
         ++indeg[it->w];
      }
   }

   for (t = 0; H->V > 0;) {
      for (i = 0; i < H->V; ++i) {
         link it;
         if (indeg[i] < 0) continue;
         if (indeg[i] == 0) {
            top[i] = t++;
            indeg[i] = 0;
            for (it = H->adj[i]; it != NULL; it = it->next) {
               DIGRAPHremoveA(H, i, it->w);
               --indeg[it->w];
            }
         }
      }
   }

   DIGRAPHdestroy(H);
   free(indeg);

   return top;
}

int is_top(Digraph G, int *top) {

}

int main(int argc, char *args[]) {
   Digraph G;
   int top;

   G = DIGRAPHinit(13);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 0, 1);

   get_top

   return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "DIGRAPHlists.h"

double get_rand() {
   return ((double) rand())/((double) (RAND_MAX));
}

#define PROB 0.5
#define RAND_SEED 123456
void ex3_4(int m, int n) {
   Digraph G;
   int i, j;

   srand(RAND_SEED);
   G = DIGRAPHinit(m*n);

   for (i = 0; i < m; ++i)
      for (j = 1; j < n; ++j)
         if (get_rand() <= PROB)
            DIGRAPHinsertA(G, i*m + j-1, i*m + j);
         else
            DIGRAPHinsertA(G, i*m + j, i*m + j-1);

   for (i = 1; i < m; ++i)
      for (j = 0; j < n; ++j)
         if (get_rand() <= PROB)
            DIGRAPHinsertA(G, i*m + j, (i-1)*m + j);
         else
            DIGRAPHinsertA(G, (i-1)*m + j, i*m + j);

   DIGRAPHdraw(G, "digraph.dot");
   DIGRAPHdestroy(G);
}
#undef RAND_SEED
#undef PROB

int main(int argc, char *args[]) {
   ex3_4(atoi(args[1]), atoi(args[2]));

   return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "wDIGRAPHlists.h"

int main(int argc, char *args[]) {
   int V, A, s, impl, seed;
   Digraph G;

   V = atoi(args[1]);
   A = atoi(args[2]);
   s = atoi(args[3]);
   impl = atoi(args[4]);
   seed = atoi(args[5]);

   srand(seed);
   G = DIGRAPHrand2(V, A);


   return 0;
}

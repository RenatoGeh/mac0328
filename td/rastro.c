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
// Data:       2016-08-15
//
// Este arquivo faz parte da tarefa C
// da disciplina MAC0328.
//
////////////////////////////////////////////////////////////// */

/* Este programa cria um digrafo aleatório com V vértices e A arestas
 * que são passados pela linha de comando. Em seguida percorre o
 * digrafo por meio de uma DFS, imprimindo o rastro da recursão
 * conforme a DFS passa pelos vértices. */

#include <stdio.h>
#include <stdlib.h>

/*#ifndef GRAPH*/
/*#define GRAPH 0*/
/*#endif*/

/*#if GRAPH == 0*/
#define GRAPH_HEADER "DIGRAPHlists.h"
/*#else*/
/*#define GRAPH_HEADER "DIGRAPHmatrix.h"*/
/*#endif*/

#include GRAPH_HEADER

int test_rastro() {
   int i;
   Digraph G;

   G = DIGRAPHrand1(20, 0);
   DIGRAPHdfs(G);
   for (i = 0; i < G->V; ++i)
      if (G->pre[i] != i)
         return 1;
   DIGRAPHdestroy(G);

   G = DIGRAPHinit(10);
   DIGRAPHinsertA(G, 0, 4);
   DIGRAPHinsertA(G, 0, 3);
   DIGRAPHinsertA(G, 0, 1);
   DIGRAPHinsertA(G, 1, 2);
   DIGRAPHinsertA(G, 5, 6);
   DIGRAPHinsertA(G, 6, 9);
   DIGRAPHinsertA(G, 6, 7);
   DIGRAPHinsertA(G, 7, 8);
   DIGRAPHinsertA(G, 5, 0);
   DIGRAPHdfs(G);
   for (i = 0; i < G->V; ++i)
      if (G->pre[i] != i)
         return 1;
   DIGRAPHdestroy(G);

   G = DIGRAPHrand1(1000, 2000);
   if (G->A != 2000)
      return 1;
   DIGRAPHdestroy(G);

   return 0;
}

int main(int argc, char *args[]) {
   int A, V;
   Digraph G;

   V = atoi(args[1]);
   A = atoi(args[2]);

#define RAND_SEED 123456
   srand(RAND_SEED);
#undef RAND_SEED

   G = DIGRAPHrand1(V, A);
   DIGRAPHdfs(G);

   /* Desenha o grafo em .dot. */
   if (argc > 3)
      DIGRAPHdraw(G, args[3]);

   DIGRAPHdestroy(G);

   puts("Testando...");
   if (test_rastro())
      puts("Nao passou no teste.");
   else
      puts("Passou no teste.");

   return 0;
}

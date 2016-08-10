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
// Data:       2016-08-07
//
// Este arquivo faz parte da tarefa B
// da disciplina MAC0328.
//
////////////////////////////////////////////////////////////// */

/* Biblioteca para construção de digrafos aleatórios. */

#include "DIGRAPHrand.h"

#include <stdlib.h>

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

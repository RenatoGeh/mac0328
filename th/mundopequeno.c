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
// Data:       2016-10-04
//
// Este arquivo faz parte da tarefa G
// da disciplina MAC0328.
//
////////////////////////////////////////////////////////////// */

/* Este programa imprime a distância média entre dois vértices em um
 * grafo do tipo Watts-Strogatz. Recebe um inteiro V que corresponde
 * ao número de vértices do grafo, um número real d que é a distância
 * entre os dois pontos no plano [0,1) x [0,1), e um inteiro k que
 * é o número de novas arestas aleatórias a se adicionar a cada
 * vértice. */

#include <stdio.h>

#include "DIGRAPHlists.h"

int main() {
   int V, k;
   double d;
   Graph G;

   while (1) {
      printf("> ");
      scanf("%d", &V);
      if (V < 0)
         break;
      scanf("%lf %d" , &d, &k);

      G = GRAPHclosePoints(V, d);
      GRAPHaddRandEdges(G, k);
      printf("distancia media: %.2f\n\n", GRAPHsmallWorld(G));
      DIGRAPHdestroy(G);
   }

   return 0;
}

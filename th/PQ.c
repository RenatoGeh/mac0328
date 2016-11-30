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

/* Biblioteca para filas de prioridade. */

#include "PQ.h"
#include <stdlib.h>

/* Este módulo implementa uma fila priorizada em um heap.
// O heap é armazenado num vetor pq[1..N] de vértices. (A posição 0
// do vetor não é usada.) */

static Vertex *pq;
static int N;

/* As prioridades são dadas em um vetor prty indexado por vértices:
// o vértice na posição k de pq tem prty[pq[k]]. O heap é
// caracterizado pela propriedade  prty[pq[k/2]] ≤ prty[pq[k]]
// para k = 2, ..., N. Portanto, o vértice pq[1] tem prioridade
// mínima. */

#define greater(i, j) (prty[pq[i]] > prty[pq[j]] ? 1 : 0)

/* O vetor qp[0..N-1] é o "inverso" de pq: para cada vértice v,
// qp[v] é o único índice tal que pq[qp[v]] == v.
// É claro que qp[pq[i]] == i para todo i. */

static int *qp;

static void exch(int i, int j) {
   Vertex t;
   t = pq[i]; pq[i] = pq[j]; pq[j] = t;
   qp[pq[i]] = i;
   qp[pq[j]] = j;
}

static void fixUp(int k, double prty[]) {
   while (k > 1 && greater(k/2, k)) {
      exch(k/2, k);
      k = k/2;
   }
}

static void fixDown(int k, double prty[]) {
   int j;
   while (2*k <= N) {
      j = 2*k;
      if (j < N && greater(j, j+1)) j++;
      if (!greater(k, j)) break;
      exch(k, j);
      k = j;
   }
}

void PQinit(int maxN) {
   pq = malloc((maxN+1) * sizeof(Vertex));
   qp = malloc(maxN * sizeof(int));
   N = 0;
}

/* Supõe-se que teremos sempre N ≤ maxN. */

int PQempty(void) {
   return N == 0;
}

void PQinsert(Vertex v, double prty[]) {
   qp[v] = ++N;
   pq[N] = v;
   fixUp(N, prty);
}

Vertex PQdelmin(double prty[]) {
   exch(1, N);
   --N;
   fixDown(1, prty);
   return pq[N+1];
}

void PQdec(Vertex w, double prty[]) {
   fixUp(qp[w], prty);
}

void PQfree() {
   free(pq);
   free(qp);
}

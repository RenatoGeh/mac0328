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

/* Biblioteca para construção de grafos aleatórios. */

#ifndef GRAPH_RAND_H_
#define GRAPH_RAND_H_

#ifdef DIGRAPH_MATRIX_H_
#include "DIGRAPHmatrix.h"
#else
#include "DIGRAPHlists.h"
#endif

/* Constrói um grafo aleatório com vértices 0..V-1 e exatamente E
 * arestas. A função supõe que E <= V*(V-1). Se E for próximo de
 * V*(V-1), a função pode consumir muito tempo. (Código inspirado no
 * Programa 17.7 de Sedgewick.) */
Digraph GRAPHrand1(int V, int E);

/* Essa constrói um grafo aleatório com vértices 0..V-1. Cada um dos
 * V*(V-1) possíveis arestas é criado com probabilidade p, sendo p
 * calculado de modo que o número esperado de arestas seja E. A função
 * supõe que V >= 2 e E <= V*(V-1). (Código inspirado no Program 17.8
 * de Sedgewick.) */
Digraph GRAPHrand2(int V, int E);

#endif

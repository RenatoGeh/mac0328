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

#ifndef DIGRAPH_RAND_H_
#define DIGRAPH_RAND_H_

#ifndef GRAPH
#define GRAPH 0
#endif

#if GRAPH == 0
#include "DIGRAPHlists.h"
#else
#include "DIGRAPHmatrix.h"
#endif

/* Constrói um digrafo aleatório com vértices 0..V-1 e exatamente A
 * arcos. A função supõe que A <= V*(V-1). Se A for próximo de V*(V-1),
 * a função pode consumir muito tempo. (Código inspirado no Programa
 * 17.7 de Sedgewick.) */
Digraph DIGRAPHrand1(int V, int A);

/* Essa constrói um digrafo aleatório com vértices 0..V-1. Cada um dos
 * V*(V-1) possíveis arcos é criado com probabilidade p, sendo p
 * calculado de modo que o número esperado de arcos seja A. A função
 * supõe que V >= 2 e A <= V*(V-1). (Código inspirado no Program 17.8
 * de Sedgewick.) */
Digraph DIGRAPHrand2(int V, int A);

#endif

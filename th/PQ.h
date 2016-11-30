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

#ifndef PQ_H_
#define PQ_H_

#ifndef Vertex
#define Vertex int
#endif

/* PQinit inicializa uma nova fila de prioridade com maxN elementos no
 * máximo. */
void PQinit(int maxN);

/* PQempty retorna se a fila de prioridae está vazia. */
int PQempty(void);

/* PQinsert insere um novo elemento v com prioridades prty. */
void PQinsert(Vertex v, double prty[]);

/* PQdelmin retorna e remove da fila o menor elemento da fila. */
Vertex PQdelmin(double prty[]);

/* PQdec realinha a heap após a remoção de um elemento. */
void PQdec(Vertex w, double prty[]);

/* Libera a fila de prioridade. */
void PQfree();

#endif

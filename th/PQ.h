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

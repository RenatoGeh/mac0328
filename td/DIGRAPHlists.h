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

/* Biblioteca para representação de digrafos em formato de lista de
 * adjacência. */

#ifndef DIGRAPH_LISTS_H_
#define DIGRAPH_LISTS_H_

#ifndef Vertex
#define Vertex int
#endif

/* A lista de adjacência de um vértice v é composta por nós do
 * tipo node. Cada nó da lista corresponde a um arco e contém um
 * vizinho w de v e o endereço do nó seguinte da lista. Um link é um
 * ponteiro para um node. */
typedef struct node *link;
struct node {
   Vertex w;
   link next;
};

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura digraph
 * representa um digrafo. O campo adj é um ponteiro para o vetor de
 * listas de adjacência, o campo V contém o número de vértices e o
 * campo A contém o número de arcos do digrafo. */
struct digraph {
   int V;
   int A;
   link *adj;
   int *pre;
   int *pos;
   int *pai;
};

/* Um Digraph é um ponteiro para um digraph. */
typedef struct digraph *Digraph;

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinit()
 * constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit(int V);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHdestroy()
 * libera a memória do digrafo G. */
void DIGRAPHdestroy(Digraph G);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsertA()
 * insere um arco v-w no digrafo G. A função supõe que v e w são
 * distintos, positivos e menores que G->V. Se o digrafo já tem um arco
 * v-w, a função não faz nada. */
void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w);

/* REPRESENTAÇÃO POR LISTA DE ADJACÊNCIA: A função DIGRAPHremoveA()
 * remove do digrafo G o arco v-w. A função supõe que v e w são
 * distintos, positivos e menores que G->V. Se não existe arco v-w, a
 * função não faz nada. */
void DIGRAPHremoveA(Digraph G, Vertex v, Vertex w);

/* REPRESENTAÇÃO POR LISTA DE ADJACÊNCIA: A função DIGRAPHshow()
 * imprime, para cada vértice v do digrafo G, em uma linha, todos os
 * vértices adjacentes a v. */
void DIGRAPHshow(Digraph G);

/* REPRESENTAÇÃO POR LISTA DE ADJACÊNCIA: A função DIGRAPHindeg()
 * retorna o grau de entrada de um vértice v do digrafo G. */
int DIGRAPHindeg(Digraph G, Vertex v);

/* REPRESENTAÇÃO POR LISTA DE ADJACÊNCIA: A função DIGRAPHindeg()
 * retorna o grau de saída de um vértice v do digrafo G. */
int DIGRAPHoutdeg(Digraph G, Vertex v);

/* REPRESENTAÇÃO POR LISTA DE ADJACÊNCIA: A função DIGRAPHdraw()
 * cria um arquivo .dot que representa um digrafo em Graphviz Dot.
 * Para mais informações sobre como desenhar grafos, veja
 * http://www.graphviz.org/. */
void DIGRAPHdraw(Digraph G, const char *filename);

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

/* A função DIGRAPHdfs() visita todos os vértices e todos os arcos do
 * digrafo G. A função atribui um número de ordem pre[x] a cada vértice
 * x: o k-ésimo vértice descoberto recebe número de ordem k.  (Código
 * inspirado no programa 18.3 de Sedgewick.) */
void DIGRAPHdfs(Digraph G);

#ifdef TEST
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHlists_test()
 * testa as funções de manipulação de digrafos. */
void DIGRAPHlists_test();
#endif

#endif

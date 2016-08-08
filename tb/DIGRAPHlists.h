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

#endif

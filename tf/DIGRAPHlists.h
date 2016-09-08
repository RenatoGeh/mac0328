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
// Data:       2016-09-07
//
// Este arquivo faz parte da tarefa F
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

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef BOOLEAN_TYPE
#define BOOLEAN_TYPE
typedef int bool;
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
   int *sc;
   int *ord;
   int *visit;
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

/* Esta função decide se o digrafo G tem um ciclo. (Se a resposta for
 * negativa, G tem uma numeração topológica.) */
bool DIGRAPHcycle(Digraph G);

/* Esta função retorna -1 se não existe um ciclo, guardando uma
 * numeração topológica inversa no campo pos do digrafo dado. Se existe
 * um ciclo, retorna um vértice que está contido no ciclo. */
Vertex DIGRAPHcycleOrTopo(Digraph G);

/* A função DIGRAPHinputArcs() recebe um arquivo gráfico que descreve
 * um digrafo G. A primeira linha do arquivo corresponde ao número V de
 * arcos de G, e as linhas restantes (até EOF) correspondem aos pares
 * de arcos ([0..V-1], [0..V-1]) de G. Em seguida, retorna G. */
Digraph DIGRAPHinputArcs();

/* Esta função implementa o algoritmo de Kosaraju-Sharir de cálculo das
 * componentes fortes de um digrafo G. A função atribui um rótulo sc[v]
 * (os rótulos são 0,1,2,...) a cada vértice v de G de modo que dois
 * vértices tenham o mesmo rótulo se e somente se os dois pertencem à
 * mesma componente forte. A função devolve o número (quantidade) de
 * componentes fortes de G. (O código é adaptado do Programa 19.10 de
 * Sedgewick.) */
int DIGRAPHscKS(Digraph G);

/* Constrói o inverso do digrafo G. */
Digraph DIGRAPHreverse(Digraph G);

/* A função DIGRAPHreach() recebe vértices s e t de um digrafo G e
 * decide se t está ao alcance de s ou não. */
bool DIGRAPHreach(Digraph G, Vertex s, Vertex t);

#ifdef TEST
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHlists_test()
 * testa as funções de manipulação de digrafos. */
void DIGRAPHlists_test();
#endif

#endif

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

/* Biblioteca para representação de digrafos com pesos em formato de
 * lista de adjacência. */

#ifndef WDIGRAPH_LISTS_H_
#define WDIGRAPH_LISTS_H_

#ifndef Vertex
#define Vertex int
#endif

#define TRUE 1
#define FALSE 0
typedef int boolean;

/* A lista de adjacência de um vértice v é composta por nós do
 * tipo node. Cada nó da lista corresponde a um arco e contém um
 * vizinho w de v e o endereço do nó seguinte da lista. Além disso,
 * cada aresta tem um custo cst. Um link é um ponteiro para um node. */
typedef struct node *link;
struct node {
   Vertex w;
   double cst;
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
   int *color;
   double *dist;
   int *num;
   Vertex *frj;
};

/* Um Digraph é um ponteiro para um digraph. */
typedef struct digraph *Digraph;
typedef Digraph Graph;

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinit()
 * constrói um digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit(int V);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHdestroy()
 * libera a memória do digrafo G. */
void DIGRAPHdestroy(Digraph G);

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHinsertA()
 * insere um arco v-w com custo cst no digrafo G. A função supõe que v
 * e w são distintos, positivos e menores que G->V. Se o digrafo já tem
 * um arco v-w, a função não faz nada. */
void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w, double cst);

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
Digraph DIGRAPHrand2(int V, int A, double cmin, double cmax);

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
boolean DIGRAPHcycle(Digraph G);

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
boolean DIGRAPHreach(Digraph G, Vertex s, Vertex t);

/* A função DIGRAPHbfs() implementa o algoritmo de busca em largura.
 * Ela visita todos os vértices do digrafo G que estão ao alcance do
 * vértice s.  A ordem em que os vértices são descobertos é registrada
 * no vetor num[]. (Código inspirado no programa 18.9 de Sedgewick.) */
void DIGRAPHbfs(Digraph G, Vertex s);

/* Para cada vértice v do digrafo G, esta função armazena em dist[v] a
 * distância de s a v.  Também armazena no vetor pai[] o vetor de pais
 * da árvore de distâncias. (Código inspirado no programa 18.9 de
 * Sedgewick.) */
void DIGRAPHdist(Digraph G, Vertex s);

/* Insere uma aresta v-w no grafo G. */
void GRAPHinsertE(Graph G, Vertex v, Vertex w, double cst);

/* Remove uma aresta v-w do grafo G. */
void GRAPHremoveE(Graph G, Vertex v, Vertex w);

/* Esta função decide se o grafo G admite bipartição. Em caso
 * afirmativo, a função atribui uma cor, 0 ou 1, a cada vértice de G de
 * tal forma que toda aresta tenha pontas de cores diferentes. As cores
 * dos vértices são armazenadas no vetor color[] indexado pelos
 * vértices. (Código inspirado no programa 18.6 de Sedgewick.) */
boolean GRAPHtwocolor(Graph G);

/* A função GRAPHhasCycle() decide se o grafo G tem um ciclo não
 * trivial. */
boolean GRAPHhasCycle(Graph G);

/* Cria um grafo G com V vértices. Seja dist a função de distância
 * euclideana, existe uma aresta v-w em G sse dist(v, w) <= d. */
Graph GRAPHclosePoints(int V, double d);

/* Recebe um grafo G e, para cada vértice v em G adiciona k arestas
 * v-w_i, onde os vértices w_i são escolhidos aleatoriamente. No caso
 * de já existir tal aresta, não adiciona a aresta. */
void GRAPHaddRandEdges(Graph G, int k);

/* Recebe um grafo G e computa a distância média entre dois vértices
 * distintos. Caso G seja desconexo, retorna G->V+1. */
double GRAPHsmallWorld(Graph G);

/* Retorna o representante de "infinito" do digrafo. Ou seja, retorna a
 * soma dos custos positivos mais um. */
double DIGRAPHinf(Digraph G);

/* Recebe um digrafo G com cusstos positivos nos arcos e um vértice s.
 * Calcula as distâncias dos vértices em relação ao vértice s. Armazena
 * em dist e a SPT em pai. */
void DIGRAPHsptD0(Digraph G, Vertex s);

/* Recebe um digrafo G com custos positivos nos arcos e um vértice s.
 * Calcula uma SPT com raiz s e armazena a SPT no vetor pai[]. As
 * distâncias a partir de s são armazenadas no vetor dist[]. (Se um
 * vértice v não está ao alcance de s, pai[v] vale -1.)
 * Esta função implementa o algoritmo de Dijkstra. Ela supõe que G é
 * representado por listas de adjacência e tem no máximo 1000 vértices.
 * (O código foi inspirado no Programa 20.3 de Sedgewick.) */
void DIGRAPHsptD1(Digraph G, Vertex s);

/* Recebe um digrafo G com custos positivos nos arcos e um vértice s.
 * Calcula uma SPT com raiz s. A SPT é armazenada no vetor pai[]. As
 * distâncias a partir de s são armazenadas no vetor dist[]. (Se um
 * vértice v não está ao alcance de s, pai[v] vale -1.) Esta função
 * implementa o algoritmo de Dijkstra. Ela supõe que G é representado
 * por listas de adjacência e tem no máximo 1000 vértices.  (O código
 * foi inspirado nos Programas 20.4, e 21.1 de Sedgewick.) */
void DIGRAPHsptD2(Digraph G, Vertex s);

/* Recebe um digrafo G com custos nos arcos e um vetor de supostas
 * distâncias dist a partir de um vértice s e retorna verdadeiro se
 * esse vetor representa um potencial. */
int DIGRAPHcheckDist(Digraph G, Vertex s, double *dist);

/* Recebe um vértice t e um vetor de pais T com tamanho n representando
 * uma árvore radicada. Recebe também um ponteiro para um inteiro que
 * devolve o tamanho do caminho Retorna um vetor contendo a sequência
 * de vértices do caminho da raíz de T até t. */
Vertex* DIGRAPHpath(Vertex t, Vertex *T, int n, int *m);

#ifdef TEST
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função DIGRAPHlists_test()
 * testa as funções de manipulação de digrafos. */
void DIGRAPHlists_test();
#endif

#endif

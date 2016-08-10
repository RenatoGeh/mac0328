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

/* Este programa escolhe v pontos aleatórios em um quadrado [0,1)x[0,1)
 * e constrói um grafo em que existe uma aresta se e somente se a
 * distância entre dois vértices p e q é menor ou igual a d.
 * Opcionalmente, se dado um nome de arquivo como terceiro argumento
 * na linha de comando, o programa imprime um arquivo com representação
 * Graphviz Dot. É então possível desenhar o grafo com o seguintes
 * comando:
 *   $ neato -Tpng graph.dot > graph.png
 * Onde graph.dot é o nome dado como terceiro argumento na linha de
 * comando. Para mais informações, leia o README.txt. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef GRAPH
#define GRAPH 0
#endif

#if GRAPH == 0
#define GRAPH_HEADER "DIGRAPHlists.h"
#else
#define GRAPH_HEADER "DIGRAPHmatrix.h"
#endif

#include GRAPH_HEADER

typedef struct {
   double x;
   double y;
} pair;

/* Gera um número pseudo-aleatório no intervalo [0, 1). */
double randd() {
   return (double) rand() / (RAND_MAX + 1.0);
}

/* Gera v pontos pseudo-aleatórios dada uma semente seed para o gerador
 * de números pseudo-aleatórios. */
pair* generate_points(int v, unsigned int seed) {
   int i;
   pair *pts;

   srand(seed);
   pts = (pair*) malloc(v * sizeof(pair));
   for (i = 0; i < v; i++) {
      pts[i].x = randd();
      pts[i].y = randd();
   }

   return pts;
}

/* Retorna a distância euclideana entre dois ponteiros para pares de
 * coordenadas p = &(p->x, p->y) e q = &(q->x, q->y). A distância é
 * a raíz quadrada da soma dos quadrados das diferenças entre cada
 * coordenada. */
double distance(pair *p, pair *q) {
   double sqx, sqy;
   sqx = p->x-q->x;
   sqy = p->y-q->y;
   sqx *= sqx;
   sqy *= sqy;
   return sqrt(sqx + sqy);
}

/* Cria um digrafo em que existe um arco entre dois vértices quaisquer
 * p e q se e somente se a distância do ponto p até q é menor ou igual
 * a d. Note que esse digrafo sempre será simétrico (portanto será um
 * grafo). Os v vértices são gerados a partir de um gerador de números
 * pseudo-aleatórios de acordo com uma semente seed. */
Digraph compile_graph(int v, double d, pair *pts) {
   int i, j;
   Digraph G;

   G = DIGRAPHinit(v);

   for (i = 0; i < v; i++) {
      for (j = i + 1; j < v; j++) {
         if (distance(&pts[i], &pts[j]) <= d) {
            DIGRAPHinsertA(G, i, j);
            DIGRAPHinsertA(G, j, i);
         }
      }
   }

   return G;
}

/* Testa se o digrafo G, dada uma distância d, tem uma aresta se e
 * somente se a distância entre os pontos de cada par de vértices
 * p e q são menores ou igual a d. Se existe algum par de pontos que
 * tenha distância maior que d, retorna 1. Senão retorna 0. */
int test_graph(Digraph G, double d, pair *pts) {
   int i;

   for (i = 0; i < G->V; i++) {
#if GRAPH == 0
      link it = G->adj[i];
      while (it != NULL) {
         if (distance(&pts[i], &pts[it->w]) > d)
         return 1;
         it = it->next;
      }
#else
      int j;
      for (j = 0; j < G->V; j++) {
         if (i == j || !(G->adj[i][j])) continue;
         if (distance(&pts[i], &pts[j]) > d)
            return 1;
      }
#endif
   }

   return 0;
}

#define IMG_SIZE_X 200
#define IMG_SIZE_Y 200
/* Desenha um digrafo G em um arquivo .dot com nome filename. Os
 * vértices são desenhados nas posições escaladas dos pontos pts. Ou
 * seja, multiplicam-se of pontos (que estão no intervalo [0,1)x[0,1))
 * por uma constante inteira (e.g. 200) que significa a posição na
 * imagem resultante. Não se guarante que a imagem terá a dimensão da
 * constante. */
void draw_graph(Digraph G, pair *pts, char *filename) {
   int i;
   FILE *out;

   out = fopen(filename, "w");
   if (out == NULL) {
      printf("Erro ao criar arquivo %s.\n", filename);
      return;
   }

   fprintf(out, "digraph {\n");
   for (i = 0; i < G->V; i++)
      fprintf(out, "v_%d [label=\"%d\", pos=\"%d, %d!\", shape=circle]"
         ";\n", i, i, (int)(IMG_SIZE_X * pts[i].x),
         (int)(IMG_SIZE_Y * pts[i].y));
   for (i = 0; i < G->V; i++) {
#if GRAPH == 0
      link it = G->adj[i];
      while (it != NULL) {
         fprintf(out, "v_%d -> v_%d;\n", i, it->w);
         it = it->next;
      }
#else
      int j;
      for (j = 0; j < G->V; j++)
         if (G->adj[i][j])
            fprintf(out, "v_%d -> v_%d;\n", i, j);
#endif
   }
   fprintf(out, "}\n");
   fclose(out);
}
#undef IMG_SIZE_X
#undef IMG_SIZE_Y

#define SEED 123456

int main(int argc, char *args[]) {
   int v;
   char *filename;
   double d;
   pair *pts;
   Digraph G;

   if (argc < 3) {
      puts("Uso: ./ep v d [filename]\n"
         "  v: numero maximo de pontos/vertices.\n"
         "  d: distancia para se criar uma aresta no grafo.\n"
         "  filename: cria um arquivo filename com a representacao do "
         "grafo em Graphviz Dot (argumento opcional).");
      return 1;
   }

   v = atoi(args[1]);
   d = atof(args[2]);
   filename = NULL;

   if (argc > 2)
      filename = args[3];

#ifdef TEST
   puts("O programa ira testar a biblioteca "GRAPH_HEADER" primeiro.");
#if GRAPH == 0
   DIGRAPHlists_test();
#else
   DIGRAPHmatrix_test();
#endif
#endif

   printf("Gerando %d pontos pseudo-aleatorios com uma semente de "
         "%d...\n", v, SEED);
   pts = generate_points(v, SEED);
   printf("Compilando o grafo a partir de %d vertices e distancia "
         "%f...\n", v, d);
   G = compile_graph(v, d, pts);

   printf("Grafo criado, com %d vertices e %d arcos (%d arestas) a "
      "partir da distancia %.3f.\n", v, G->A, G->A / 2, d);

   if (test_graph(G, d, pts))
      puts("O grafo gerado nao passou no teste.");
   else
      puts("O grafo gerado passou no teste.");

   if (v < 100 && G->A < 1000) {
      puts("Desenhando grafo na saida padrao.");
      DIGRAPHshow(G);
   }

   if (filename != NULL) {
      printf("Desenhando grafo no arquivo %s.\n", filename);
      draw_graph(G, pts, filename);
   }

   DIGRAPHdestroy(G);
   free(pts);

   return 0;
}

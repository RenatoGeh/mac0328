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
void draw_graph(Digraph G, pair *pts) {
  int i;
  FILE *out;

  out = fopen("graph.dot", "w");
  if (out == NULL) {
    puts("Erro ao criar arquivo graph.dot.");
    return;
  }

  fprintf(out, "digraph {\n");
  for (i = 0; i < G->V; i++)
    fprintf(out, "v_%d [label=\"%d\", pos=\"%d, %d!\", shape=circle];"
        "\n", i, i, (int)(IMG_SIZE_X * pts[i].x),
        (int)(IMG_SIZE_Y * pts[i].y));
  for (i = 0; i < G->V; i++) {
#if GRAPH == 0
    link it = G->adj[i];
    while (it != NULL) {
      fprintf(out, "v_%d -> v_%d;\n", i, it->w);
      it = it->next;
    }
#else
    for (j = 0; j < G->V; j++)
      if (G->adj[i][j])
        fprintf(out, "v_%d -> v_%d;\n", i, j);
#endif
  }
  fprintf(out, "}\n");
  fclose(out);
}

#define SEED 123456

int main(int argc, char *args[]) {
  int v;
  double d;
  pair *pts;
  Digraph G;

  if (argc < 3) {
    puts("Uso: ./ep v d\n"
        "  v: numero maximo de pontos/vertices.\n"
        "  d: distancia para se criar uma aresta no grafo.");
    return 1;
  }

  v = atoi(args[1]);
  d = atof(args[2]);

  pts = generate_points(v, SEED);
  G = compile_graph(v, d, pts);

  printf("Grafo criado, com %d vertices e %d arcos (%d arestas) a "
      "partir da distancia %.3f.\n", v, G->A, G->A / 2, d);

  if (test_graph(G, d, pts)) {
    puts("Nao passou no teste.");
  } else {
    puts("Passou no teste.");
  }

  puts("Desenhando grafo no arquivo graph.dot.");
  draw_graph(G, pts);

  DIGRAPHdestroy(G);
  free(pts);

  return 0;
}

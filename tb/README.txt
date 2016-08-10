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

1. Compilando

Para se compilar o programa, use o Makefile. Como temos duas possíveis
bibliotecas (DIGRAPHlists e DIGRAPHmatrix), o Makefile foi criado com
o intuito de se poder compilar o programa com ambas as bibliotecas.

Foi criada uma variável GRAPH no Makefile. Esta variável indica se
estamos tratando de DIGRAPHlists ou DIGRAPHmatrix. Podemos ter dois
possíveis valores para GRAPH:

   GRAPH=lists
   GRAPH=matrix

Para configurarmos o valor de GRAPH no Makefile, rodamos o make com
a variável como parâmetro.

   $ make GRAPH=lists
   $ make GRAPH=matrix

O primeiro comando irá compilar com listas de adjacência e o segundo
com matrizes de adjacência.

Como as bibliotecas foram feitas para que possamos utilizar ambas as
possíveis configurações (listas ou matrizes), quando mudamos os valores
de GRAPH todos os arquivos fontes serão compilados com as suas
representações adequadas. Portanto, se escolhermos GRAPH=matrix, a
função de criação de digrafos (DIGRAPHinit) utilizará matrizes de
adjacência, assim como no programa em main.c.

Se você não quiser usar o Makefile, é possível passar os parâmetros
GRAPH direto pelo gcc. Por exemplo:

   $ gcc -ansi -pedantic -Wall -Wno-unused-result -DGRAPH=0 main.c

Quando passamos o parâmetro GRAPH direto pelo gcc, temos que:

   - (gcc) -DGRAPH=0 == GRAPH=lists  (make)
   - (gcc) -DGRAPH=1 == GRAPH=matrix (make)

Além de como vamos representar os digrafos, o Makefile também permite
que compilemos o programa com uma função de testes ou não. Leia a seção
3 para mais informações.

1.1 DIGRAPHlists

O Makefile usa DIGRAPHlists por default. Portanto

   $ make

compilará o programa normalmente com DIGRAPHlists como biblioteca. Ou
seja, irá se comportar do mesmo jeito que:

   $ make GRAPH=lists

Deste jeito, a biblioteca DIGRAPHlists.h será usada ao invés da
DIGRAPHmatrix.h. As funções em main.c utilizarão listas de adjacências
e não matrizes.

1.2 DIGRAPHmatrix

Para compilarmos usando matrizes de adjacências, devemos chamar o
Makefile da seguinte forma:

   $ make GRAPH=matrix

Desta forma a biblioteca DIGRAPHmatrix.h será usada ao invés de
DIGRAPHlists.h.

2. Execução

Após compilarmos, teremos um arquivo executável `ep`:

   Uso: ./ep v d [filename]
      v: numero maximo de pontos/vertices.
      d: distancia para se criar uma aresta no grafo.
      filename: cria um arquivo filename com a representacao do grafo
      em Graphviz Dot (argumento opcional).

Os parâmetros v e d são explicitadas no enunciado. O parâmetro filename
é opcional e não consta no enunciado da tarefa. Se não providenciarmos
um filename, o arquivo não produzirá um arquivo fonte .dot.
Descreveremos o que filename é a seguir.

2.1. Graphviz

Graphviz (graph visualizer) é um compilador para linguagem dot. A
linguagem dot define um digrafo (ou grafo), e permite que desenhemos
grafos a partir de um arquivo fonte .dot.

   http://www.graphviz.org/

O arquivo filename dado na linha de comando da tarefa é o arquivo de
destino para criar um arquivo .dot para melhor visualizar o grafo
gerado. Para transformarmos o arquivo .dot gerado em um arquivo de
imagem PNG, usamos o compilador neato:

   $ neato -Tpng filename.dot > filename.png

Isso gerará um arquivo PNG que é a representação em imagem do grafo
representado por filename.dot.

2.1.1 Ubuntu

Para instalar o Graphviz no Ubuntu:

   sudo apt-get install graphviz

2.1.2 Arch Linux

Para instalar o Graphviz no Arch Linux:

   sudo pacman -S graphviz

3. Testes

Os testes, com exceção do teste da função geradora do grafo de pontos
pseudo-aleatórios, foram feitos para serem compilados se e somente se
uma variável no Makefile for verdadeira. Por default, a variável está
como verdadeiro. Ou seja,

   $ make

É igual a:

   $ make TEST=true

Para não compilar os testes, use:

   $ make TEST=false

Os testes para matrizes de adjacência são diferentes dos testes de
listas de adjacência. Portanto,

   $ make TEST=true GRAPH=lists

Gerará um código diferente de

   $ make TEST=true GRAPH=matrix

O programa discutido na seção 2 irá automaticamente executar os testes
da biblioteca especificada por GRAPH antes de gerar o grafo com os
pontos pseudo-aleatórios se TEST=true.

Se você desejar passar a variável direto para o gcc, passe-o com
qualquer valor para compilar com testes. Para não compilar os testes,
não defina a macro TEST.

   $ (gcc) -DTEST=1 == TEST=true  (make)
   $ (gcc)          == TEST=false (make)

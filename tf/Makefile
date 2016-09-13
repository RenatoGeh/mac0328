#/* DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.\
// TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS\
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE\
// SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM.  DECLARO\
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA\
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.\
//\
// Autor:      Renato Lui Geh\
// Numero USP: 8536030\
// Sigla:      RENATOLU\
// Data:       2016-08-15\
//\
// Este arquivo faz parte da tarefa C\
// da disciplina MAC0328.\
//\
////////////////////////////////////////////////////////////// */

# Makefile.
# Leia README.txt para instruções.

CFLAGS = -ansi -pedantic -Wall -Wno-unused-result
LIBS = -lm

GRAPH = lists
TEST = true

ifeq ($(TEST), true)
	CFLAGS += -DTEST=1
endif

ifeq ($(GRAPH), lists)
	CFLAGS += -DGRAPH=0
else
	CFLAGS += -DGRAPH=1
endif

DEPS = DIGRAPH$(GRAPH).o DIGRAPH$(GRAPH)_test.o

all: ep

debug: CFLAGS += -g -D DEBUG=1
debug: ep

simple:
	gcc compsfortes.c DIGRAPHlists.c $(CFLAGS) $(LIBS)

ep: compsfortes.o $(DEPS)
	gcc $^ -o $@ $(LIBS)

compsfortes.o: compsfortes.c
	gcc -c $(CFLAGS) $^

DIGRAPHlists.o: DIGRAPHlists.c DIGRAPHlists.h
	gcc -c $(CFLAGS) $^

DIGRAPHlists_test.o: DIGRAPHlists_test.c DIGRAPHlists.h
	gcc -c $(CFLAGS) $^

DIGRAPHmatrix.o: DIGRAPHmatrix.c DIGRAPHmatrix.h
	gcc -c $(CFLAGS) $^

DIGRAPHmatrix_test.o: DIGRAPHmatrix_test.c DIGRAPHmatrix.h
	gcc -c $(CFLAGS) $^

.PHONY: clean
clean:
	rm *.out *.gch *.o *.png *.dot ep .*.swp


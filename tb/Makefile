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
// Data:       2016-08-07\
//\
// Este arquivo faz parte da tarefa B\
// da disciplina MAC0328.\
//\
////////////////////////////////////////////////////////////// */

# Makefile.
# Leia README.txt para instruções.

CFLAGS = -ansi -pedantic -Wall -Wno-unused-result
LIBS = -lm

GRAPH = lists

ifeq ($(GRAPH), lists)
	CFLAGS += -DGRAPH=0
else
	CFLAGS += -DGRAPH=1
endif

DEPS = DIGRAPH$(GRAPH).o DIGRAPHrand.o GRAPHrand.o

all: ep

debug: CFLAGS += -g -D DEBUG=1
debug: ep

ep: main.o $(DEPS)
	gcc $^ -o $@ $(LIBS)

main.o: main.c
	gcc -c $(CFLAGS) $^

DIGRAPHlists.o: DIGRAPHlists.c DIGRAPHlists.h
	gcc -c $(CFLAGS) $^

DIGRAPHmatrix.o: DIGRAPHmatrix.c DIGRAPHmatrix.h
	gcc -c $(CFLAGS) $^

DIGRAPHrand.o: DIGRAPHrand.c DIGRAPHrand.h DIGRAPHlists.h \
	DIGRAPHmatrix.h
	gcc -c $(CFLAGS) $^

GRAPHrand.o: GRAPHrand.c GRAPHrand.h DIGRAPHlists.h DIGRAPHmatrix.h
	gcc -c $(CFLAGS) $^

.PHONY: clean
clean:
	rm *.out *.gch *.o *.png *.dot ep


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


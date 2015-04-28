SOURCES = grafo_lista.c grafo_matriz.c grafo.c lista.c
HEADERS = grafo_lista.h grafo_matriz.h grafo.h lista.h fila.h

all: programa

programa: main.c $(SOURCES) $(HEADERS)
	gcc -std=c99 main.c $(SOURCES) -o programa

run:
	./programa DFS

#include <string.h> /* memcpy */
#include <stdlib.h>
#include <stdio.h>

#include "grafo.h"

static void ler_arestas(Grafo *grafo, int m);
static void ler_commandos(Grafo *grafo, void (*fn)(const Grafo*, int, vertice_fn, aresta_fn, void *));

/**
 * O programa principal receberá sempre um argumento.
 * Se este argumento for 'B', realiza a busca em largura,
 * caso contrário, a busca em profundidade.
 */
int main(int argc, char *argv[])
{
    Grafo *grafo;
    int n, m;

    if (argc < 2) {
        return 1;
    }

    scanf("%d %d\n", &n, &m);

    grafo = criar_grafo(n, 1, MATRIZ_DE_ADJACENCIA);
//    grafo = criar_grafo(7, 1, MATRIZ_DE_ADJACENCIA);

    ler_arestas(grafo, m);
//    ler_arestas(grafo, 15);
    
    ler_commandos(grafo, ordenacao_topologica);

    destruir_grafo(grafo);

    return 0;
}

void ler_arestas(Grafo *grafo, int m)
{
    int u, v;
    
//    int us[15] = {2, 5, 2, 0, 4, 0, 1, 4, 1, 5, 0, 1, 5, 3, 2};
//    int vs[15] = {5, 0, 0, 3, 6, 4, 5, 3, 2, 4, 6, 4, 3, 6, 3};
    
    int i;
    for (i = 0; i < m; ++i)
    {
        scanf("%d %d\n", &u, &v);
        adicionar_aresta(grafo, u, v, 1);
//        adicionar_aresta(grafo, us[i], vs[i], 1);
    }
}

/**
 * Estrutura que armazena as condições e retorno da busca.
 */
struct busca
{
    int grafo_tamanho;

    int origem;
    int destino;
    int *predecessor;
};

#define PARAR 0
#define CONTINUAR 1

/**
 * Callback passada para o algoritmo de busca que preenche apropriadamente o resultado da
 * busca.
 */
static int copia_predecessor(int vertice,
                             const int *cor, const int *d, const int *predecessor, struct busca *busca)
{
    /* Argumentos não utilizados. */
    (void) cor;
    (void) d;
    
    /* Se está processando o vértice destino, copie o vetor predecessor. */
    if (vertice == busca->destino)
    {
        memcpy(busca->predecessor, predecessor, busca->grafo_tamanho * sizeof(int));
        return CONTINUAR; /* A busca pode ser interrompida aqui. */
    }
    
    return CONTINUAR; /* Continue a busca. */
}

static void preenche(int *vetor, int valor, int tamanho)
{
    int i;
    for (i = 0; i < tamanho; ++i)
        vetor[i] = valor;
}

void ler_commandos(Grafo *grafo, void (*busca_fn)(const Grafo*, int, vertice_fn, aresta_fn, void *))
{
    struct busca busca;
    busca.predecessor = (int *) malloc(n_vertices(grafo) * sizeof(int));
    busca.grafo_tamanho = n_vertices(grafo);

    busca.origem = cabeca_ordenacao_topologica(grafo);
    busca.destino = cauda_ordenacao_topologica(grafo);
    
//    imprimir_grafo(grafo);
//    printf("%d", busca.origem);
//    printf("%d", busca.destino);

    preenche(busca.predecessor, -1, n_vertices(grafo));
    busca_fn(grafo, busca.origem, (vertice_fn) copia_predecessor, NULL, &busca);

    free(busca.predecessor);
}

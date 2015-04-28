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

    if (argc < 2)
        return 1;

    scanf("%d %d\n", &n, &m);

    grafo = criar_grafo(n, 1, MATRIZ_DE_ADJACENCIA);

    ler_arestas(grafo, m);
    ler_commandos(grafo, argv[1][0] == 'B' ? busca_em_largura : busca_em_profundidade);

    destruir_grafo(grafo);

    return 0;
}

void ler_arestas(Grafo *grafo, int m)
{
    int u, v;

    int i;
    for (i = 0; i < m; ++i)
    {
        scanf("%d %d\n", &u, &v);
        adicionar_aresta(grafo, u, v, 1);
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
        return 0; /* A busca pode ser interrompida aqui. */
    }

    return 1; /* Continue a busca. */
}

static void imprimir_caminho(const int *predecessor, int destino)
{
    if (destino == -2) /* Chegou na raiz. */
        return;

    imprimir_caminho(predecessor, predecessor[destino]);
    printf("%d ", destino);
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

    while (scanf("%d %d", &busca.origem, &busca.destino) != EOF)
    {
        preenche(busca.predecessor, -1, n_vertices(grafo));
        busca_fn(grafo, busca.origem, (vertice_fn) copia_predecessor, NULL, &busca);
        busca.predecessor[busca.origem] = -2; /* -2 indica a raiz. */

        if (busca.predecessor[busca.destino] != -1) /* Se tiver caminho. */
            imprimir_caminho(busca.predecessor, busca.destino);
        printf("\n");
    }

    free(busca.predecessor);
}

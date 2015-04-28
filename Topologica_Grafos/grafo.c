#include "grafo.h"

#include "grafo_matriz.h"
#include "grafo_lista.h"

#include <stdlib.h>

#define DISPATCHER(signature, R, ...) \
    do { \
        if (grafo == NULL) \
            return R; \
        switch (grafo->representacao) \
        { \
        case MATRIZ_DE_ADJACENCIA: \
            return signature ## _m(grafo->matriz, __VA_ARGS__); \
        case LISTA_DE_ADJACENCIA: \
            return signature ## _l(grafo->lista, __VA_ARGS__); \
        } \
        return R; \
    } while (0)

#define DISPATCHER_NO_ARG(signature, R) \
    do { \
        if (grafo == NULL) \
            return R; \
        switch (grafo->representacao) \
        { \
        case MATRIZ_DE_ADJACENCIA: \
            return signature ## _m(grafo->matriz); \
        case LISTA_DE_ADJACENCIA: \
            return signature ## _l(grafo->lista); \
        } \
        return R;\
    } while (0)

struct grafo
{
    union
    {
        GrafoM *matriz;
        GrafoL *lista;
    };
    int representacao;
};

Grafo *criar_grafo(int n, int digrafo, Representacao representacao)
{
    if (n < 0)
        return NULL;

    Grafo *grafo = (Grafo *) malloc(sizeof(Grafo));
    grafo->representacao = representacao;

    switch (representacao)
    {
    case MATRIZ_DE_ADJACENCIA:
        grafo->matriz = criar_grafo_m(n, digrafo);
        break;

    case LISTA_DE_ADJACENCIA:
        grafo->lista = criar_grafo_l(n, digrafo);
        break;

    default:
        free(grafo);
        return NULL;
    }

    return grafo;
}

void destruir_grafo(Grafo *grafo)
{
    if (grafo == NULL)
        return;

    switch (grafo->representacao)
    {
    case MATRIZ_DE_ADJACENCIA:
        destruir_grafo_m(grafo->matriz);
        break;

    case LISTA_DE_ADJACENCIA:
        destruir_grafo_l(grafo->lista);
        break;
    }

    free(grafo);
}

Grafo *transposto(const Grafo *grafo)
{
    if (grafo == NULL)
        return NULL;

    Grafo *resultado = (Grafo *) malloc(sizeof(Grafo));
    resultado->representacao = grafo->representacao;

    switch (grafo->representacao)
    {
    case MATRIZ_DE_ADJACENCIA:
        resultado->matriz = transposto_m(grafo->matriz);
        break;

    case LISTA_DE_ADJACENCIA:
        resultado->lista = transposto_l(grafo->lista);
        break;
    }

    return resultado;
}

int e_digrafo(const Grafo *grafo)
{
    DISPATCHER_NO_ARG(e_digrafo, 0);
}

int n_vertices(const Grafo *grafo)
{
    DISPATCHER_NO_ARG(n_vertices, 0);
}

int existe_aresta(const Grafo *grafo, int u, int v)
{
    DISPATCHER(existe_aresta, 0, u, v);
}

void adicionar_aresta(Grafo *grafo, int u, int v, int peso)
{
    DISPATCHER(adicionar_aresta, , u, v, peso);
}

void remover_aresta(Grafo *grafo, int u, int v)
{
    DISPATCHER(remover_aresta, , u, v);
}

int peso_aresta(const Grafo *grafo, int u, int v)
{
    DISPATCHER(peso_aresta, 0, u, v);
}

void imprimir_grafo(const Grafo *grafo)
{
    DISPATCHER_NO_ARG(imprimir_grafo, );
}

void adjacentes(const Grafo *grafo, int u, int *v, int max)
{
    DISPATCHER(adjacentes, , u, v, max);
}

void busca_em_profundidade(const Grafo *grafo, int s,
        vertice_fn processa_vertice, aresta_fn processa_aresta, void *args)
{
    if (grafo == NULL)
        return;

    switch (grafo->representacao)
    {
    case MATRIZ_DE_ADJACENCIA:
        busca_em_profundidade_m(grafo->matriz, s, (vertice_fn_m) processa_vertice,
                (aresta_fn_m) processa_aresta, args);
        break;

    case LISTA_DE_ADJACENCIA:
        busca_em_profundidade_l(grafo->lista, s, (vertice_fn_l) processa_vertice,
                (aresta_fn_l) processa_aresta, args);
        break;
    }
}

void busca_em_largura(const Grafo *grafo, int s,
        vertice_fn processa_vertice, aresta_fn processa_aresta, void *args)
{
    if (grafo == NULL)
        return;

    switch (grafo->representacao)
    {
    case MATRIZ_DE_ADJACENCIA:
        busca_em_largura_m(grafo->matriz, s, (vertice_fn_m) processa_vertice,
                (aresta_fn_m) processa_aresta, args);
        break;

    case LISTA_DE_ADJACENCIA:
        busca_em_largura_l(grafo->lista, s, (vertice_fn_l) processa_vertice,
                (aresta_fn_l) processa_aresta, args);
        break;
    }
}

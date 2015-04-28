#include "grafo_lista.h"

#include <stdlib.h>
#include <stdio.h>

#include "lista.h"
#include "fila.h"

typedef struct aresta Aresta;

struct aresta
{
    int peso;
    int destino;
};

struct grafo_l
{
    int n;
    int digrafo;
    Lista **listas;
};

int cmp_aresta(const Aresta *a, const Aresta *b)
{
    return a->destino - b->destino;
}

GrafoL *criar_grafo_l(int n, int digrafo)
{
    if (n < 0)
        return NULL;

    GrafoL *grafo = (GrafoL *) malloc(sizeof(GrafoL));

    grafo->n = n;
    grafo->digrafo = digrafo;
    grafo->listas = (Lista **) malloc(n * sizeof(Lista *));

    int i;
    for (i = 0; i < n; ++i)
        grafo->listas[i] = criar_lista_ordenada(Aresta, (cmp_fn) cmp_aresta);

    return grafo;
}

void destruir_grafo_l(GrafoL *grafo)
{
    if (grafo == NULL)
        return;

    int i;
    for (i = 0; i < grafo->n; ++i)
        destruir_lista(grafo->listas[i]);

    free(grafo->listas);
    free(grafo);
}

GrafoL *transposto_l(const GrafoL *grafo)
{
    if (grafo == NULL || !grafo->digrafo)
        return NULL;

    GrafoL *resultado = criar_grafo_l(grafo->n, 1);

    int i;
    for (i = 0; i < grafo->n; ++i)
    {
        Aresta *it = NULL;
        foreach(it, grafo->listas[i])
            adicionar_aresta_l(resultado, it->destino, i, it->peso);
    }

    return resultado;
}

int e_digrafo_l(const GrafoL *grafo)
{
    if (grafo == NULL)
        return 0;

    return grafo->digrafo;
}

int n_vertices_l(const GrafoL *grafo)
{
    if (grafo == NULL)
        return 0;

    return grafo->n;
}

int existe_aresta_l(const GrafoL *grafo, int u, int v)
{
    if (grafo == NULL || u < 0 || v < 0 || u >= grafo->n || v >= grafo->n)
        return 0;

    Aresta *it;
    foreach(it, grafo->listas[u])
    {
        if (it->destino > v)
            break;

        if (it->destino == v)
            return 1;
    }

    return 0;
}

void adicionar_aresta_l(GrafoL *grafo, int u, int v, int peso)
{
    if (grafo == NULL || u < 0 || v < 0 || u >= grafo->n || v >= grafo->n)
        return;

    Aresta aresta = {.peso = peso, .destino = v};
    entrar_ordenado(grafo->listas[u], aresta);
    if (!grafo->digrafo)
    {
        aresta.destino = u;
        entrar_ordenado(grafo->listas[v], aresta);
    }
}

void remover_aresta_l(GrafoL *grafo, int u, int v)
{
    if (grafo == NULL || u < 0 || v < 0 || u >= grafo->n || v >= grafo->n)
        return;

    Aresta aresta = {.destino = v};
    remover_ordenado(grafo->listas[u], aresta);
    if (!grafo->digrafo)
    {
        aresta.destino = u;
        remover_ordenado(grafo->listas[v], aresta);
    }
}

int peso_aresta_l(const GrafoL *grafo, int u, int v)
{
    if (grafo == NULL || u < 0 || v < 0 || u >= grafo->n || v >= grafo->n)
        return 0;

    Aresta *it;
    foreach(it, grafo->listas[u])
        if (it->destino == v)
            return it->peso;

    return 0;
}

void imprimir_grafo_l(const GrafoL *grafo)
{
    if (grafo == NULL)
        return;

    int i;
    for (i = 0; i < grafo->n; ++i)
    {
        printf("%d. ", i);

        Aresta *it;
        foreach(it, grafo->listas[i])
            printf("%d(%d) ", it->destino, it->peso);

        printf("\n");
    }
}

void adjacentes_l(const GrafoL *grafo, int u, int *v, int max)
{
    if (grafo == NULL || u < 0 || u >= grafo->n)
        return;

    int i = 0;
    Aresta *it;

    foreach(it, grafo->listas[u])
    {
        v[i++] = it->destino;
        if (i == max-1)
            break;
    }

    v[i] = -1;
}

#define BRANCO 0
#define CINZA  1
#define PRETO 2

#define INF -1
#define NIL -1

#define PARAR 0
#define CONTINUAR 1

static int visitar_profundidade(const GrafoL *grafo, int u,
        vertice_fn_l processa_vertice, aresta_fn_l processa_aresta, void *args,
        int *cor, int *d, int *p)
{
    cor[u] = CINZA;

    if (processa_vertice && processa_vertice(u, cor, d, p, args) == PARAR)
        return PARAR;

    Aresta *aresta;
    foreach(aresta, grafo->listas[u])
    {
        int v = aresta->destino;

        if (processa_aresta && processa_aresta(u, v, cor, d, p, args) == PARAR)
            return PARAR;

        if (cor[v] == BRANCO)
        {
            p[v] = u;
            d[v] = d[u] + 1;
            if (visitar_profundidade(grafo, v, processa_vertice, processa_aresta, args,
                        cor, d, p) == PARAR)
                return PARAR;
        }
    }

    cor[u] = PRETO;

    return CONTINUAR;
}

void busca_em_profundidade_l(const GrafoL *grafo, int s,
        vertice_fn_l processa_vertice, aresta_fn_l processa_aresta, void *args)
{
    if (grafo == NULL || s < 0 || s >= grafo->n)
        return;

    int *cor = (int *) malloc(grafo->n * sizeof(int));
    int *d = (int *) malloc(grafo->n * sizeof(int));
    int *p = (int *) malloc(grafo->n * sizeof(int));

    int i;
    for (i = 0; i < grafo->n; ++i)
    {
        cor[i] = BRANCO;
        p[i] = NIL;
        d[i] = INF;
    }

    d[s] = 0;
    visitar_profundidade(grafo, s, processa_vertice, processa_aresta, args, cor, d, p);

    free(cor);
    free(d);
    free(p);
}

void busca_em_largura_l(const GrafoL *grafo, int s,
        vertice_fn_l processa_vertice, aresta_fn_l processa_aresta, void *args)
{
    if (grafo == NULL || s < 0 || s >= grafo->n)
        return;

    int *cor = (int *) malloc(grafo->n * sizeof(int));
    int *d = (int *) malloc(grafo->n * sizeof(int));
    int *p = (int *) malloc(grafo->n * sizeof(int));

    int i;
    for (i = 0; i < grafo->n; ++i)
    {
        cor[i] = BRANCO;
        d[i] = INF;
        p[i] = NIL;
    }

    cor[s] = CINZA;
    d[s] = 0;
    p[s] = NIL;

    Fila *fila = criar_fila(int);
    entrar_fila(fila, s);

    while (!esta_vazia_fila(fila))
    {
        int u, v;
        sair_fila(fila, u);
        if (processa_vertice && processa_vertice(u, cor, d, p, args) == PARAR)
            break;

        Aresta *aresta;
        foreach(aresta, grafo->listas[u])
        {
            v = aresta->destino;

            if (processa_aresta && processa_aresta(u, v, cor, d, p, args) == PARAR)
            {
                esvaziar_fila(fila);
                break;
            }

            if (cor[v] == BRANCO)
            {
                cor[v] = CINZA;
                d[v] = d[u] + 1;
                p[v] = u;
                entrar_fila(fila, v);
            }
        }

        cor[u] = PRETO;
    }

    destruir_fila(fila);
    free(cor);
    free(d);
    free(p);
}

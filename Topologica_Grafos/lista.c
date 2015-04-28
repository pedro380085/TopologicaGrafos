#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no No;

struct no
{
    No *proximo;
    char entrada[];
};

struct lista
{
    No *inicio;
    int tamanho_elemento;
    No *iter;
    cmp_fn cmp;
};


static No *criar_no(const void *entrada, int tamanho_elemento, No *proximo)
{
    No *no = (No *) malloc(sizeof(No) + tamanho_elemento);

    no->proximo = proximo;
    memcpy(no->entrada, entrada, tamanho_elemento);

    return no;
}

static void ler_no(const No *no, void *saida, int tamanho_elemento)
{
    memcpy(saida, no->entrada, tamanho_elemento);
}

static void escrever_no(No *no, const void *entrada, int tamanho_elemento)
{
    memcpy(no->entrada, entrada, tamanho_elemento);
}

Lista *criar_lista_generica(int tamanho_elemento)
{
    if (tamanho_elemento < 1)
        return NULL;

    Lista *lista = (Lista *) malloc(sizeof(Lista));

    lista->tamanho_elemento = tamanho_elemento;
    lista->inicio = NULL;
    lista->iter = NULL;
    lista->cmp = NULL;

    return lista;
}


Lista *criar_lista_generica_ordenada(int tamanho_elemento, cmp_fn cmp)
{
    Lista *lista = criar_lista_generica(tamanho_elemento);
    if (lista == NULL)
        return NULL;

    lista->cmp = cmp;

    return lista;
}

void destruir_lista_generica(Lista *lista)
{
    if (lista == NULL)
        return;

    esvaziar_lista(lista);
    free(lista);
}

void entrar_inicio_lista_generica(Lista *lista, const void *entrada)
{
    if (lista == NULL || entrada == NULL || lista->cmp != NULL)
        return;

    lista->inicio = criar_no(entrada, lista->tamanho_elemento, lista->inicio);
}

void sair_inicio_lista_generica(Lista *lista, void *saida)
{
    if (lista == NULL || lista->inicio == NULL)
        return;

    No *no = lista->inicio;
    if (saida != NULL)
        ler_no(no, saida, lista->tamanho_elemento);

    lista->inicio = no->proximo;
    free(no);
}

void entrar_fim_lista_generica(Lista *lista, const void *entrada)
{
    if (lista == NULL || entrada == NULL || lista->cmp != NULL)
        return;

    No **ultimo = &(lista->inicio);
    while (*ultimo != NULL)
        ultimo = &((*ultimo)->proximo);

    *ultimo = criar_no(entrada, lista->tamanho_elemento, NULL);
}

void sair_fim_lista_generica(Lista *lista, void *saida)
{
    if (lista == NULL || lista->inicio == NULL)
        return;

    No **penultimo = &(lista->inicio);
    while ((*penultimo)->proximo != NULL)
        penultimo = &((*penultimo)->proximo);

    if (saida != NULL)
        ler_no(*penultimo, saida, lista->tamanho_elemento);

    free(*penultimo);
    *penultimo = NULL;
}

void entrar_ordenado_lista_generica(Lista *lista, const void *entrada)
{
    if (lista == NULL || entrada == NULL || lista->cmp == NULL)
        return;

    No **ptr = &(lista->inicio);
    while ((*ptr != NULL) && lista->cmp(entrada, (*ptr)->entrada) > 0)
        ptr = &((*ptr)->proximo);

    if ((*ptr != NULL) && lista->cmp(entrada, (*ptr)->entrada) == 0)
        escrever_no(*ptr, entrada, lista->tamanho_elemento);
    else
        *ptr = criar_no(entrada, lista->tamanho_elemento, *ptr);
}

void remover_ordenado_lista_generica(Lista *lista, void *saida)
{
    if (lista == NULL || saida == NULL || lista->cmp == NULL)
        return;

    No **ptr = &(lista->inicio);
    while ((*ptr != NULL) && lista->cmp(saida, (*ptr)->entrada) > 0)
        ptr = &((*ptr)->proximo);

    if ((*ptr == NULL) || lista->cmp(saida, (*ptr)->entrada) < 0)
        return;

    ler_no(*ptr, saida, lista->tamanho_elemento);

    No *tmp = *ptr;
    *ptr = (*ptr)->proximo;
    free(tmp);
}

void esvaziar_lista(Lista *lista)
{
    No *tmp = lista->inicio;

    while (tmp != NULL)
    {
        lista->inicio = tmp->proximo;
        free(tmp);
        tmp = lista->inicio;
    }
}

int esta_vazia_lista(const Lista *lista)
{
    return lista->inicio == NULL;
}

void primeiro_lista(Lista *lista, void **saida)
{
    lista->iter = lista->inicio;
    proximo_lista(lista, saida);
}

void proximo_lista(Lista *lista, void **saida)
{
    if (lista->iter == NULL)
    {
        *saida = NULL;
        return;
    }

    *saida = lista->iter->entrada;
    lista->iter = lista->iter->proximo;
}

#ifndef FILA_H
#define FILA_H

#include "lista.h"

/**
 * @brief A Fila é uma uma Lista com restrições nas operações de inserção e remoção.
 *
 * A fila é implementada através de macros que selecionam as posições corretas na
 * inserção e remoção de elementos em uma lista.
 *
 */
typedef Lista Fila;

/**
 * @brief Cria uma fila genérica (= criar uma lista).
 */
#define criar_fila(tipo) \
    criar_lista_generica(sizeof(tipo))

/**
 * @brief Destrói a fila (= destruir a lista).
 */
#define destruir_fila(fila) \
    destruir_lista_generica(fila)

/**
 * @brief Insere elemento na fila (= entrar no fim da lista).
 */
#define entrar_fila(fila, entrada) \
    entrar_fim_lista_generica(fila, &entrada)

/**
 * @brief Remove elemento da fila (= sair do início da lista).
 */
#define sair_fila(fila, saida) \
    sair_inicio_lista_generica(fila, &saida)

/**
 * @brief Verifica se a fila está vazia (= verificar se a lista está vazia).
 */
#define esta_vazia_fila(fila) \
    esta_vazia_lista(fila)

/**
 * @brief Esvazia a fila (= esvaziar a lista).
 */
#define esvaziar_fila(fila) \
    esvaziar_lista(fila)

#endif

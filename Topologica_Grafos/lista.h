#ifndef LISTA_H
#define LISTA_H

/**
 * @brief Função de comparação para ser utilizada em listas ordenadas.
 *
 * @param Elemento genérico.
 * @param Elemento genérico.
 *
 * @return 0 se os elementos são iguais, maior 0 se o primeiro é maior
 * que o segundo, ou menor 0 caso contrário.
 */
typedef int (*cmp_fn)(const void *, const void *);

/**
 * @brief Lista genérica ordenada ou não.
 *
 * Esta estrutura contém uma lista genérica (ordenada ou não).
 * A estrutura pode armazenar qualquer tipo de elemento, criando cópias bytewise internas
 * dos elementos de entrada.
 *
 * Nas listas ordenadas, deverão ser utilizadas as operações de inserção e remoção
 * ordenadas.
 *
 * Nas listas não ordenadas, poderão ser inseridos e removidos elementos no início e no
 * fim da lista apenas.
 */
typedef struct lista Lista;

/**
 * @brief Cria uma lista genérica não ordenada de elementos de tamanho @param
 * tamanho_elemento em bytes.
 *
 * @param tamanho_elemento Tamanho dos elementos que serão armazenados.
 *
 * @return Lista criada.
 */
Lista *criar_lista_generica(int tamanho_elemento);

/**
 * @brief Cria uma lista genérica ordenada de elementos de tamanho @param
 * tamanho_elemento em bytes.
 *
 * @param tamanho_elemento Tamanho dos elementos que serão armazenados.
 * @param cmp Função de comparação dos elementos.
 *
 * @return Lista criada.
 */
Lista *criar_lista_generica_ordenada(int tamanho_elemento, cmp_fn cmp);

/**
 * @brief Destrói uma lista ordenada ou não.
 *
 * @param lista Lista a ser destruída.
 */
void destruir_lista_generica(Lista *lista);

/**
 * @brief Insere elemento no início da lista NÃO ORDENADA.
 *
 * @param lista Lista não ordenada.
 * @param entrada Endereço do elemento a ser copiado.
 */
void entrar_inicio_lista_generica(Lista *lista, const void *entrada);

/**
 * @brief Remove elemento do início da lista NÃO ORDENADA.
 *
 * @param lista Lista não ordenada.
 * @param entrada Endereço para onde o elemento será copiado. Pode ser NULL.
 */
void sair_inicio_lista_generica(Lista *lista, void *saida);

/**
 * @brief Insere elemento no fim da lista NÃO ORDENADA.
 *
 * @param lista Lista não ordenada.
 * @param entrada Endereço do elemento a ser copiado.
 */
void entrar_fim_lista_generica(Lista *lista, const void *entrada);

/**
 * @brief Remove elemento do fim da lista NÃO ORDENADA.
 *
 * @param lista Lista não ordenada.
 * @param entrada Endereço para onde o elemento será copiado. Pode ser NULL.
 */
void sair_fim_lista_generica(Lista *lista, void *saida);

/**
 * @brief Insere elemento na lista ORDENADA. Atualiza caso o elemento já exista.
 *
 * @param lista Lista ordenada.
 * @param entrada Endereço do elemento a ser copiado.
 */
void entrar_ordenado_lista_generica(Lista *lista, const void *entrada);

/**
 * @brief Remove elemento igual @param saida na fila ORDENADA. Caso o elemento seja
 * encontrado, @param saída é atualizado.
 *
 * @param lista Lista ordenada.
 * @param saida Endereço do elemento a ser buscado e atualizado.
 */
void remover_ordenado_lista_generica(Lista *lista, void *saida);

/**
 * @brief Esvazia uma lista.
 *
 * @param lista Lista a ser esvaziada.
 */
void esvaziar_lista(Lista *lista);

/**
 * @brief Verifica se a lista está vazia.
 *
 * @param lista Lista a ser consultada.
 *
 * @return 1 se a lista está vazia, 0 caso contrário.
 */
int esta_vazia_lista(const Lista *lista);

/**
 * @brief Iterador de acesso ao primeiro elemento da lista.
 *
 * Atenção: Alterar o elemento via iteradores pode causar inconsistências na lista.
 *
 * @param[in,out] lista Lista a ser iterada.
 * @param[in,out] saida Iterador que apontará para o primeiro elemento da lista.
 */
void primeiro_lista(Lista *lista, void **saida);

/**
 * @brief Iterador de acesso ao próximo elemento da lista.
 *
 * Atenção: Alterar o elemento via iteradores pode causar inconsistências na lista.
 *
 * @param[in,out] lista Lista a ser iterada.
 * @param[in,out] saida Iterador que apontará para o próximo elemento da lista.
 */
void proximo_lista(Lista *lista, void **saida);


/**
 * Macros auxiliares para manipulação das listas
 */

#define entrar_lista(lista, entrada, modo) \
    entrar_ ## modo ## _lista_generica(lista, &entrada)

#define entrar_ordenado(lista, entrada) \
    entrar_ordenado_lista_generica(lista, &entrada)

#define sair_lista(lista, saida, modo) \
    sair_ ## modo ## _lista_generica(lista, &saida)

#define remover_ordenado(lista, saida) \
    remover_ordenado_lista_generica(lista, &saida)

#define criar_lista(tipo) \
    criar_lista_generica(sizeof(tipo))

#define criar_lista_ordenada(tipo, cmp) \
    criar_lista_generica_ordenada(sizeof(tipo), cmp)

#define destruir_lista(lista) \
    destruir_lista_generica(lista)

#define foreach(saida, lista) \
    for(primeiro_lista(lista, (void **) &saida); saida != NULL; proximo_lista(lista, (void **) &saida))

#endif

#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

typedef struct grafo_m GrafoM;

/**
 * @brief Callback de processamento de vértices nas buscas.
 *
 * @param[in]     Índice do vértice
 * @param[in]     Vetor de cores
 * @param[in]     Vetor de distâncias
 * @param[in]     Vetor predecessor
 * @param[in,out] Argumento definido pelo usuário
 *
 * @return 1 se desejar continuar a busca, 0 caso contrário.
 */
typedef int (*vertice_fn_m)(int, const int*, const int*, const int*, void *);

/**
 * @brief Callback de processamento de arestas nas buscas.
 *
 * @param[in]     Índice do vértice de origem
 * @param[in]     Índice do vértice de destino
 * @param[in]     Vetor de cores
 * @param[in]     Vetor de distâncias
 * @param[in]     Vetor predecessor
 * @param[in,out] Argumento definido pelo usuário
 *
 * @return 1 se desejar continuar a busca, 0 caso contrário.
 */
typedef int (*aresta_fn_m)(int, int, const int*, const int*, const int*, void *);

/**
 * @brief Cria um novo grafo ponderado de tamanho @param n representado internamente como
 * uma matriz de adjacências. As arestas serão direcionadas se @param digrafo for
 * diferente de 0.
 *
 * @param n Tamanho do grafo.
 * @param digrafo 1, se o grafo é um dígrafo, ou 0, caso contrário.
 *
 * @return Grafo recém-criado.
 */
GrafoM *criar_grafo_m(int n, int digrafo);

/**
 * @brief Libera memória utilizada pelo grafo.
 *
 * @param grafo Grafo a ser destruído.
 */
void destruir_grafo_m(GrafoM *grafo);

/**
 * @brief Retorna o transposto de um dígrafo.
 *
 * @param grafo Grafo a ser transposto.
 *
 * @return Transposto, se é um dígrafo, NULL, caso contrário.
 */
GrafoM *transposto_m(const GrafoM *grafo);

/**
 * @brief Verifica se é um dígrafo.
 *
 * @param grafo Grafo a ser consultado.
 *
 * @return 1, se é dígrafo, 0, caso contrário.
 */
int e_digrafo_m(const GrafoM *grafo);

/**
 * @brief Retorna o número de vértices do grafo.
 *
 * @param grafo Grafo a ser consultado.
 *
 * @return Número de vértices.
 */
int n_vertices_m(const GrafoM *grafo);

/**
 * @brief Verifica se a aresta uv existe.
 *
 * @param grafo Grafo a ser consultado.
 * @param u Origem da aresta.
 * @param v Destino da aresta.
 *
 * @return 1, se aresta existe, 0, caso contrário.
 */
int existe_aresta_m(const GrafoM *grafo, int u, int v);

/**
 * @brief Adiciona a aresta uv com peso @param peso.
 *
 * @param grafo Grafo a ser modificado.
 * @param u Origem da aresta.
 * @param v Destino da aresta.
 * @param peso Peso da aresta.
 */
void adicionar_aresta_m(GrafoM *grafo, int u, int v, int peso);

/**
 * @brief Remove a aresta uv do grafo.
 *
 * @param grafo Grafo a ser modificado.
 * @param u Origem da aresta.
 * @param v Destino da aresta.
 */
void remover_aresta_m(GrafoM *grafo, int u, int v);

/**
 * @brief Retorna o peso da aresta uv.
 *
 * @param grafo Grafo a ser consultado.
 * @param u Origem da aresta.
 * @param v Destino da aresta.
 *
 * @return Peso da aresta uv, ou 0, caso aresta não exista.
 */
int peso_aresta_m(const GrafoM *grafo, int u, int v);

/**
 * @brief Imprime o grafo.
 *
 * @param grafo Grafo a ser impresso.
 */
void imprimir_grafo_m(const GrafoM *grafo);

/**
 * @brief Obtém posições para ordem topológica.
 *
 * @param grafo Grafo a ser analisado.
 */
int cabeca_ordenacao_topologica_m(const GrafoM *grafo);
int cauda_ordenacao_topologica_m(const GrafoM *grafo);

/**
 * @brief Indica os vértices adjacentes ao vértice @param u. O resultado será salvo no
 * vetor @param v. O valor -1 indicará o fim dos vértices adjacentes.
 *
 * @param grafo Grafo a ser consultado.
 * @param u Vértice de origem.
 * @param[out] v Vetor que receberá os vértices adjacentes.
 * @param max Tamanho do vetor @param v.
 */
void adjacentes_m(const GrafoM *grafo, int u, int *v, int max);

/**
 * @brief Realiza busca em profundidade a partir do vértice @param u. As callbacks
 * processa_vertice e processa_aresta devem retornar 1 se desejar que a busca continue ou
 * 0, caso contrário. Estas callbacks recebem o vetor de cor, o vetor de distâncias e o
 * vetor predecessor.
 *
 * @param grafo Grafo a ser consultado.
 * @param s Vértice inicial da busca.
 * @param processa_vertice Função a ser executada quando um vértice é alcançado.
 * @param processa_aresta Função a ser executada quando uma aresta é alcançada.
 */
void busca_em_profundidade_m(const GrafoM *grafo, int s,
        vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args);

/**
 * @brief Realiza busca em profundidade a partir do vértice @param u. As callbacks
 * processa_vertice e processa_aresta devem retornar 1 se desejar que a busca continue ou
 * 0, caso contrário. Estas callbacks recebem o vetor de cor, o vetor de distâncias e o
 * vetor predecessor.
 *
 * @param grafo Grafo a ser consultado.
 * @param s Vértice inicial da busca.
 * @param processa_vertice Função a ser executada quando um vértice é alcançado.
 * @param processa_aresta Função a ser executada quando uma aresta é alcançada.
 */
void busca_em_largura_m(const GrafoM *grafo, int s,
        vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args);

#endif /* GRAFO_MATRIZ_H */

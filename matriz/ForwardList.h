#pragma once
#include "Nodes.h"

typedef enum
{
    REPLACE = 0,
    SUM = 1,
} Operacao;

typedef struct ForwardList *pForwardList;

/**
 * @brief Constroi uma nova lista encadeada:: estrutura de lista encadeada
 *  Aloca memoria para uma nova lista encadeada e retorna seu ponteiro.
 * @param tipo
 * Tipo da lista encadeada, se eh uma lista de linhas ou de colunas.
 * @return pForwardList
 * Ponteiro para a nova lista encadeada alocada.
 * @note
 * O usuario eh responsavel por liberar os ponteiros utilizando a funcao forward_list_destroi().
 */
pForwardList ForwardList_cria(Direction tipo);

/**
 * @brief Insere um valor na lista encadeada:: int
 *  Insere um valor na lista encadeada na posicao position.
 * @param lista
 * Ponteiro para a lista encadeada a ser inserido o valor.
 * @param new_node
 * Ponteiro para a celula a ser inserida na lista.
 * @return int
 * 1 foi tratado uma ocorrencia de colisao (foi inserido um valor em uma celula ja existente), 0 caso contrario.
 * @note
 * O valor eh inserido na lista encadeada na posicao position.
 */
int ForwardList_insere(pForwardList lista, pNode new_node, Operacao op);

/**
 * @brief Le um valor da lista encadeada:: float
 * Le um valor da lista encadeada na posicao position.
 * @param lista
 * Ponteiro para a lista encadeada a ser lido o valor.
 * @param position
 * Posicao da lista a ser lido o valor.
 * @return float
 * Valor lido da lista.
 * @note
 * O valor eh lido da lista encadeada na posicao position.
 */
float ForwardList_le_valor(pForwardList lista, int position);

/**
 * @brief Retorna o ponteiro para a celula head da lista encadeada:: estrutura de node
 * Retorna o ponteiro para a celula head da lista encadeada.
 * @param lista
 * Ponteiro para a lista encadeada a ser lido o valor.
 * @return pNode
 * Ponteiro para a celula head da lista.
 * @note
 * O ponteiro eh retornado da lista encadeada.
 */
pNode ForwardList_retorna_head(pForwardList lista);

/**
 * @brief Retorna o tipo da lista encadeada:: enum Direction
 * Retorna o tipo da lista encadeada, se eh uma lista de linhas ou de colunas.
 * @param lista
 * Ponteiro para a lista encadeada a ser lido o valor.
 * @return Direction
 * Tipo da lista encadeada.
 * @note
 * O tipo eh retornado da lista encadeada.
 */
Direction ForwardList_retorna_tipo(pForwardList lista);

/**
 * @brief Retorna o tamanho da lista encadeada:: int
 * Retorna o tamanho da lista encadeada.
 * @param lista
 * Ponteiro para a lista encadeada a ser lido o valor.
 * @return int
 * Tamanho da lista encadeada.
 * @note
 * O tamanho eh retornado da lista encadeada.
 */
int ForwardList_retorna_tamanho(pForwardList lista);

/**
 * @brief Retorna a multiplicacao de uma linha por uma coluna de uma multiplicacao matricial:: float
 * @param linha
 * Ponteiro para a lista encadeada da linha.
 * @param coluna
 * Ponteiro para a lista encadeada da coluna.
 * @return float
 * Valor da multiplicacao da linha pela coluna de uma multiplicacao matricial.
*/
float ForwardList_multiplica_linha_por_coluna(pForwardList linha, pForwardList coluna);

/**
 * @brief Destroi uma lista encadeada:: estrutura de lista encadeada
 *  Libera a memoria alocada para uma lista encadeada.
 * @param lista
 * Ponteiro para a lista encadeada a ser liberada.
 * @return void
 * @note
 * O ponteiro para a lista eh manualmente setado para NULL apos liberado por seguranca.
 */
void ForwardList_destroi(pForwardList lista);

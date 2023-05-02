#pragma once
#include "Nodes.h"

typedef enum
{
    ROW=0,
    COLUMN=1
} Direction;

typedef enum
{
    REPLACE=0,
    SUM=1,
} Operacao;

typedef struct ForwardList
{
    Node *head;
    int size;
    Direction tipo;
} ForwardList;

/**
 * @brief Constroi uma nova lista encadeada:: estrutura de lista encadeada
 *  Aloca memoria para uma nova lista encadeada e retorna seu ponteiro.
 * @param tipo
 * Tipo da lista encadeada, se eh uma lista de linhas ou de colunas.
 * @return ForwardList*
 * Ponteiro para a nova lista encadeada alocada.
 * @note
 * O usuario eh responsavel por liberar os ponteiros utilizando a funcao forward_list_destroi().
 */
ForwardList *ForwardList_cria(Direction tipo);

/**
 * @brief Insere um valor na lista encadeada:: estrutura de lista encadeada
 *  Insere um valor na lista encadeada na posicao position.
 * @param lista
 * Ponteiro para a lista encadeada a ser inserido o valor.
 * @param new_node
 * Ponteiro para a celula a ser inserida na lista.
 * @return void
 * @note
 * O valor eh inserido na lista encadeada na posicao position.
 */
void ForwardList_insere(ForwardList *lista, Node **new_node, Operacao op);

/**
 * @brief Le um valor da lista encadeada:: estrutura de lista encadeada
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
float ForwardList_le_valor(ForwardList *lista, int position);

/**
 * @brief Destroi uma lista encadeada:: estrutura de lista encadeada
 *  Libera a memoria alocada para uma lista encadeada.
 * @param lista
 * Ponteiro para a lista encadeada a ser liberada.
 * @return void
 * @note
 * O ponteiro para a lista eh manualmente setado para NULL apos liberado por seguranca.
 */
void ForwardList_destroi(ForwardList *lista);

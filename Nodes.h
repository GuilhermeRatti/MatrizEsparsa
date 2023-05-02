#pragma once

typedef struct Node
{
    float value;
    int row;
    int column;
    struct Node *next_inrow;
    struct Node *next_incolumn;
} Node;

/**
 * @brief Constroi uma nova celula:: estrutura de celula
 *  Aloca memoria para uma nova celula e retorna seu ponteiro.
 * @param value
 * Valor a ser inserido na celula.
 * @param row
 * Linha da celula.
 * @param column
 * Coluna da celula.
 * @return Node*
 * Ponteiro para a nova celula alocada.
 * @note
 * O usuario eh responsavel por liberar os ponteiros utilizando a funcao node_destroi().
 */
Node *Node_cria(float value, int row, int column);

/**
 * @brief Destroi uma celula:: estrutura de celula
 *  Libera a memoria alocada para uma celula.
 * @param node
 * Ponteiro para a celula a ser liberada.
 * @return void
 * @note
 * O ponteiro para a celula eh manualmente setado para NULL apos liberado por seguranca.
 */
void Node_destroi(Node *node);
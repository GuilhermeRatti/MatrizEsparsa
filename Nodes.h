#pragma once

typedef enum
{
    ROW = 0,
    COLUMN = 1
} Direction;

typedef struct Node *pNode;

/**
 * @brief Constroi uma nova celula:: estrutura de celula
 *  Aloca memoria para uma nova celula e retorna seu ponteiro.
 * @param value
 * Valor a ser inserido na celula.
 * @param row
 * Linha da celula.
 * @param column
 * Coluna da celula.
 * @return pNode
 * Ponteiro para a nova celula alocada.
 * @note
 * O usuario eh responsavel por liberar os ponteiros utilizando a funcao node_destroi().
 */
pNode Node_cria(float value, int row, int column);

/**
 * @brief Retorna a celula anterior:: estrutura de celula
 *  Retorna a celula anterior a celula dada.
 * @param node
 * Ponteiro para a celula a ser analisada.
 * @param direction
 * Direcao da celula a ser analisada.
 * @return pNode
 * Ponteiro para a celula posterior de acordo com a direcao.
 */
pNode Node_get_next(pNode node, Direction direction);

/**
 * @brief Altera a celula anterior:: estrutura de celula
 *  Altera a celula anterior a celula dada.
 * @param node
 * Ponteiro para a celula a ser analisada.
 * @param next
 * Ponteiro para a nova celula posterior a celula dada.
 * @param direction
 * Direcao da celula a ser analisada.
 * @return void
 * @note
 * Mudanca por referencia
 */
void Node_set_next(pNode node, pNode next, Direction direction);

/**
 * @brief Retorna o valor da celula:: estrutura de celula
 *  Retorna o valor da celula dada.
 * @param node
 * Ponteiro para a celula a ser analisada.
 * @return float
 * Valor da celula.
 */
float Node_get_value(pNode node);

/**
 * @brief Altera o valor da celula:: estrutura de celula
 *  Altera o valor da celula dada.
 * @param node
 * Ponteiro para a celula a ser analisada.
 * @param value
 * Novo valor da celula.
 * @return void
 * @note
 * Mudanca por referencia
 */
void Node_set_value(pNode node, float value);

/**
 * @brief Retorna a coluna da celula:: estrutura de celula
 *  Retorna a coluna da celula dada.
 * @param node
 * Ponteiro para a celula a ser analisada.
 * @return int
 * coluna da celula.
 */
int Node_get_column(pNode node);

/**
 * @brief Retorna a linha da celula:: estrutura de celula
 *  Retorna a linha da celula dada.
 * @param node
 * Ponteiro para a celula a ser analisada.
 * @return int
 * linha da celula.
 */
int Node_get_row(pNode node);

/**
 * @brief Destroi uma celula:: estrutura de celula
 *  Libera a memoria alocada para uma celula.
 * @param node
 * Ponteiro para a celula a ser liberada.
 * @return void
 */
void Node_destroi(pNode node);
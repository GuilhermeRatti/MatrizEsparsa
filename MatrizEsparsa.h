#pragma once
#include "ForwardList.h"

typedef struct MatrizEsparsa
{
    ForwardList **head_rows;
    ForwardList **head_columns;
    int rows;
    int columns;
} MatrizEsparsa;

/**
 * @brief Constroi uma nova matriz esparsa:: estrutura de matriz esparsa
 *  Aloca memoria para uma nova matriz esparsa e retorna seu ponteiro.
 * @param rows
 * Numero de linhas da matriz.
 * @param columns
 * Numero de colunas da matriz.
 * @return MatrizEsparsa*
 * Ponteiro para a nova matriz esparsa alocada.
 * @note
 * O usuario eh responsavel por liberar os ponteiros utilizando a funcao matriz_esparsa_destroi().
 */
MatrizEsparsa *MatrizEsparsa_cria(int rows, int columns);

/**
 * @brief Insere um valor na matriz esparsa:: estrutura de matriz esparsa
 *  Insere um valor na matriz esparsa na posicao (row, column).
 * @param matriz
 * Ponteiro para a matriz esparsa a ser inserido o valor.
 * @param row
 * Linha da matriz a ser inserido o valor.
 * @param column
 * Coluna da matriz a ser inserido o valor.
 * @param value
 * Valor a ser inserido na matriz.
 * @param op
 * Operacao a ser realizada na insercao do valor.
 * @return void
 * @note
 * O valor eh inserido nas listas encadeadas da matriz esparsa na posicao (row, column).
 */
void MatrizEsparsa_insere(MatrizEsparsa *matriz, int row, int column, float value, Operacao op);

/**
 * @brief Le um valor da matriz esparsa:: estrutura de matriz esparsa
 * Le um valor da matriz esparsa na posicao (row, column).
 * @param matriz
 * Ponteiro para a matriz esparsa a ser lido o valor.
 * @param row
 * Linha da matriz a ser lido o valor.
 * @param column
 * Coluna da matriz a ser lido o valor.
 * @return float
 * Valor lido da matriz.
 * @note
 * O valor eh lido das listas encadeadas da matriz esparsa na posicao (row, column). 
 * Eh selecionada a lista encadeada de linhas ou de colunas dependendo da menor posicao entre row e column.
*/
float MatrizEsparsa_le_valor(MatrizEsparsa *matriz, int row, int column);

/**
 * @brief Soma duas matrizes esparsas:: estrutura de matriz esparsa
 * Soma duas matrizes esparsas e retorna uma nova matriz esparsa com o resultado.
 * @param matriz1
 * Ponteiro para a primeira matriz esparsa a ser somada.
 * @param matriz2
 * Ponteiro para a segunda matriz esparsa a ser somada.
 * @return MatrizEsparsa*
 * Ponteiro para a nova matriz esparsa alocada com o resultado da soma.
 * @note
 * Eh criada uma nova matriz esparsa com o resultado da soma das duas matrizes esparsas.
 * Eh selecionada a lista encadeada de linhas ou de colunas dependendo da menor posicao entre row e column.
 */
MatrizEsparsa* MatrizEsparsa_soma(MatrizEsparsa *matriz1, MatrizEsparsa *matriz2);

/**
 * @brief Destroi uma matriz esparsa:: estrutura de matriz esparsa
 *  Libera a memoria alocada para uma matriz esparsa.
 * @param matriz
 * Ponteiro para a matriz esparsa a ser liberada.
 * @return void
 * @note
 * O ponteiro para a matriz eh manualmente setado para NULL apos liberado por seguranca.
 */
void MatrizEsparsa_destroi(MatrizEsparsa *matriz);
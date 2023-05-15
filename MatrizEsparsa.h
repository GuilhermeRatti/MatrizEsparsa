#pragma once
#include "ForwardList.h"

typedef struct MatrizEsparsa *pMatrizEsparsa;

/**
 * @brief Constroi uma nova matriz esparsa:: estrutura de matriz esparsa
 *  Aloca memoria para uma nova matriz esparsa e retorna seu ponteiro.
 * @param rows
 * Numero de linhas da matriz.
 * @param columns
 * Numero de colunas da matriz.
 * @return pMatrizEsparsa
 * Ponteiro para a nova matriz esparsa alocada.
 * @note
 * O usuario eh responsavel por liberar os ponteiros utilizando a funcao matriz_esparsa_destroi().
 */
pMatrizEsparsa MatrizEsparsa_cria(int rows, int columns);

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
void MatrizEsparsa_insere(pMatrizEsparsa matriz, int row, int column, float value, Operacao op);

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
float MatrizEsparsa_le_valor(pMatrizEsparsa matriz, int row, int column);

/**
 * @brief Soma duas matrizes esparsas:: estrutura de matriz esparsa
 * Soma duas matrizes esparsas e retorna uma nova matriz esparsa com o resultado.
 * @param matriz1
 * Ponteiro para a primeira matriz esparsa a ser somada.
 * @param matriz2
 * Ponteiro para a segunda matriz esparsa a ser somada.
 * @return pMatrizEsparsa
 * Ponteiro para a nova matriz esparsa alocada com o resultado da soma.
 * @note
 * Eh criada uma nova matriz esparsa com o resultado da soma das duas matrizes esparsas.
 * Eh selecionada a lista encadeada de linhas ou de colunas dependendo da menor posicao entre row e column.
 */
pMatrizEsparsa MatrizEsparsa_soma(pMatrizEsparsa matriz1, pMatrizEsparsa matriz2);

/**
 * @brief Multiplica uma matriz por um escalar:: estrutura de matriz esparsa
 * Multiplica uma matriz esparsa por um escalar e retorna uma nova matriz esparsa com o resultado.
 * @param matriz
 * Ponteiro para a matriz esparsa a ser multiplicada.
 * @param escalar
 * Escalar a ser multiplicado pela matriz.
 * @return pMatrizEsparsa
 * Ponteiro para a nova matriz esparsa alocada com o resultado da multiplicacao.
 * @note
 * Eh criada uma nova matriz esparsa com o resultado da multiplicacao da matriz esparsa pelo escalar.
*/
pMatrizEsparsa MatrizEsparsa_mult_por_escalar(pMatrizEsparsa matriz, float escalar);

/**
 * @brief Multiplica duas matrizes esparsas:: estrutura de matriz esparsa
 * Multiplica duas matrizes esparsas e retorna uma nova matriz esparsa com o resultado.
 * @param matriz1
 * Ponteiro para a primeira matriz esparsa a ser multiplicada.
 * @param matriz2
 * Ponteiro para a segunda matriz esparsa a ser multiplicada.
 * @return pMatrizEsparsa
 * Ponteiro para a nova matriz esparsa alocada com o resultado da multiplicacao.
 * @note
 * Eh obrigatorio que o numero de colunas da primeira matriz seja igual ao numero de linhas da segunda matriz. 
 * Sera realizada uma multiplicacao a direita da matriz 1 pela matriz 2; matriz1 * matriz2, e nao matriz2 * matriz1.
 * Eh criada uma nova matriz esparsa com o resultado da multiplicacao das duas matrizes esparsas.
 */
pMatrizEsparsa MatrizEsparsa_mult_por_matriz(pMatrizEsparsa matriz1, pMatrizEsparsa matriz2);

/**
 * @brief Multiplica duas matrizes esparsas ponto a ponto:: estrutura de matriz esparsa
 * Multiplica duas matrizes esparsas ponto a ponto e retorna uma nova matriz esparsa com o resultado.
 * @param matriz1
 * Ponteiro para a primeira matriz esparsa a ser multiplicada.
 * @param matriz2
 * Ponteiro para a segunda matriz esparsa a ser multiplicada.
 * @return pMatrizEsparsa
 * Ponteiro para a nova matriz esparsa alocada com o resultado da multiplicacao.
 * @note
 * Eh obrigatorio que as dimensoes das duas matriz sejam iguais. 
 * Eh criada uma nova matriz esparsa com o resultado da multiplicacao das duas matrizes esparsas.
 */
pMatrizEsparsa MatrizEsparsa_mult_ponto_a_ponto(pMatrizEsparsa matriz1, pMatrizEsparsa matriz2);

/**
 * @brief Troca duas linhas de lugar de uma matriz esparsa:: estrutura de matriz esparsa
 * Troca duas linhas de lugar de uma matriz esparsa.
 * @param matriz
 * Ponteiro para a matriz esparsa a ser trocada as linhas.
 * @param row1
 * Linha 1 a ser trocada.
 * @param row2
 * Linha 2 a ser trocada.
 * @return pMatrizEsparsa
 * Ponteiro para a matriz esparsa com as linhas trocadas.
*/
pMatrizEsparsa MatrizEsparsa_troca_linhas(pMatrizEsparsa matriz, int row1, int row2);

/**
 * @brief Troca duas colunas de lugar de uma matriz esparsa:: estrutura de matriz esparsa
 * Troca duas colunas de lugar de uma matriz esparsa.
 * @param matriz
 * Ponteiro para a matriz esparsa a ser trocada as colunas.
 * @param column1
 * Coluna 1 a ser trocada.
 * @param column2
 * Coluna 2 a ser trocada.
 * @return pMatrizEsparsa
 * Ponteiro para a matriz esparsa com as colunas trocadas.
*/
pMatrizEsparsa MatrizEsparsa_troca_colunas(pMatrizEsparsa matriz, int column1, int column2);

/**
 * @brief Transpoe uma matriz esparsa:: estrutura de matriz esparsa
 * Transpoe uma matriz esparsa.
 * @param matriz
 * Ponteiro para a matriz esparsa a ser transposta.
 * @return pMatrizEsparsa
*/
pMatrizEsparsa MatrizEsparsa_transposicao(pMatrizEsparsa matriz);

/**
 * @brief Seleciona uma "fatia" de uma matriz esparsa:: estrutura de matriz esparsa
 * Seleciona uma "fatia de matriz esparsa".
 * @param matriz
 * Ponteiro para a matriz esparsa a ser fatiada.
 * @param row_inicio
 * Linha inicial da matriz.
 * @param column_inicio
 * Coluna inicial da matriz.
 * @param row_fim
 * Linha final da matriz.
 * @param column_fim
 * Coluna final da matriz.
 * @return pMatrizEsparsa
 * Ponteiro para a matriz esparsa fatiada.
*/
pMatrizEsparsa MatrizEsparsa_slice(pMatrizEsparsa matriz, int row_inicio, int column_inicio, int row_fim, int column_fim);

pMatrizEsparsa MatrizEsparsa_convolucao(pMatrizEsparsa matriz, pMatrizEsparsa kernel);

/**
 * @brief Imprime uma matriz esparsa no formato de matriz densa:: void
 * Imprime uma matriz esparsa.
 * @param matriz
 * Ponteiro para a matriz esparsa a ser impressa.
 * @return void
 */
void MatrizEsparsa_print_denso(pMatrizEsparsa matriz);

/**
 * @brief Imprime uma matriz esparsa no formato de matriz esparsa:: void
 * Imprime uma matriz esparsa.
 * @param matriz
 * Ponteiro para a matriz esparsa a ser impressa.
 * @return void
 */
void MatrizEsparsa_print_esparso(pMatrizEsparsa matriz);

/**
 * @brief Destroi uma matriz esparsa:: estrutura de matriz esparsa
 *  Libera a memoria alocada para uma matriz esparsa.
 * @param matriz
 * Ponteiro para a matriz esparsa a ser liberada.
 * @return void
 * @note
 * O ponteiro para a matriz eh manualmente setado para NULL apos liberado por seguranca.
 */
void MatrizEsparsa_destroi(pMatrizEsparsa matriz);
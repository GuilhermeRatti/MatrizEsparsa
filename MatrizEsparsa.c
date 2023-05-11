#include "MatrizEsparsa.h"
#include "ForwardList.h"
#include "Nodes.h"
#include <stdio.h>
#include <stdlib.h>

struct MatrizEsparsa
{
    pForwardList *head_rows;
    pForwardList *head_columns;
    int rows;
    int columns;
} MatrizEsparsa;

// Funcao que cria uma matriz esparsa
// Entrada: numero de linhas e colunas da matriz
// Saida: ponteiro para a matriz criada
// Complexidade: O(n) (linear)
pMatrizEsparsa MatrizEsparsa_cria(int rows, int columns)
{
    pMatrizEsparsa matriz = (pMatrizEsparsa)malloc(sizeof(struct MatrizEsparsa));
    matriz->rows = rows;
    matriz->columns = columns;

    matriz->head_rows = (pForwardList *)calloc(rows, sizeof(pForwardList));
    matriz->head_columns = (pForwardList *)calloc(columns, sizeof(pForwardList));

    int i;
    for (i = 0; i < rows; i++)
        matriz->head_rows[i] = ForwardList_cria(ROW);

    for (i = 0; i < columns; i++)
        matriz->head_columns[i] = ForwardList_cria(COLUMN);

    return matriz;
}

// Funcao que insere um valor na matriz esparsa
// Entrada: ponteiro para a matriz, linha, coluna e valor a ser inserido
// Saida: nenhum
// Complexidade: O(n) (linear)
void MatrizEsparsa_insere(pMatrizEsparsa matriz, int row, int column, float value, Operacao op)
{
    if (row >= matriz->rows ||
        column >= matriz->columns)
        exit(printf("MatrizEsparsa_insere: indices invalidos!\n"));

    if (value == 0)
    {
        printf("MatrizEsparsa_insere: valor 0 nao pode ser inserido!\n");
        return;
    }

    pNode new = Node_cria(value, row, column);

    int ocorreu_colisao;
    ocorreu_colisao = ForwardList_insere(matriz->head_rows[row], new, op);
    if (!ocorreu_colisao)
        ForwardList_insere(matriz->head_columns[column], new, op);
}

// Funcao que le um valor da matriz esparsa
// Entrada: ponteiro para a matriz, linha e coluna
// Saida: valor lido
// Complexidade: O(1) (constante)
float MatrizEsparsa_le_valor(pMatrizEsparsa matriz, int row, int column)
{
    if (row >= matriz->rows ||
        column >= matriz->columns)
        exit(printf("MatrizEsparsa_le_valor: indices invalidos!\n"));

    float target;
    if (row < column)
        target = ForwardList_le_valor(matriz->head_columns[column], row);
    else
        target = ForwardList_le_valor(matriz->head_rows[row], column);

    return target;
}

// Funcao que le uma linha da matriz esparsa
// Entrada: ponteiro para a matriz e linha
// Saida: ponteiro para a lista encadeada com os valores da linha
// Complexidade: O(n^2) (quadratica)
pMatrizEsparsa MatrizEsparsa_soma(pMatrizEsparsa matriz1, pMatrizEsparsa matriz2)
{
    if (matriz1->columns != matriz2->columns ||
        matriz1->rows != matriz2->rows)
        exit(printf("MatrizEsparsa_soma: matrizes de tamanhos diferentes!\n"));

    // Performar uma copia da matriz1 para a matriz de saida
    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz1->rows, matriz1->columns);

    int i;
    for (i = 0; i < matriz1->rows; i++)
    {
        pNode node = ForwardList_retorna_head(matriz1->head_rows[i]);
        while (node != NULL)
        {
            MatrizEsparsa_insere(saida,
                                 Node_get_row(node),
                                 Node_get_column(node),
                                 Node_get_value(node),
                                 SUM);

            node = Node_get_next(node, ROW);
        }
    }

    // Somar os valores da matriz2 na matriz de saida por meio da funcao de inserir tambem
    for (i = 0; i < matriz2->rows; i++)
    {
        pNode node = ForwardList_retorna_head(matriz2->head_rows[i]);
        while (node != NULL)
        {
            MatrizEsparsa_insere(saida,
                                 Node_get_row(node),
                                 Node_get_column(node),
                                 Node_get_value(node),
                                 SUM);

            node = Node_get_next(node, ROW);
        }
    }

    return saida;
}

// Funcao que multiplica uma matriz esparsa por um escalar
// Entrada: ponteiro para a matriz e escalar
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n) (linear)
pMatrizEsparsa MatrizEsparsa_mult_por_escalar(pMatrizEsparsa matriz, float escalar)
{
    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->rows, matriz->columns);

    int i;
    for (i = 0; i < matriz->rows; i++)
    {
        pNode node = ForwardList_retorna_head(matriz->head_rows[i]);
        while (node != NULL)
        {
            MatrizEsparsa_insere(saida,
                                 Node_get_row(node),
                                 Node_get_column(node),
                                 Node_get_value(node) * escalar,
                                 REPLACE);

            node = Node_get_next(node, ROW);
        }
    }

    return saida;
}

// Funcao que multiplica uma matriz esparsa por outra matriz esparsa
// Entrada: ponteiro para a matriz e escalar
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n^2) (quadratica)
pMatrizEsparsa MatrizEsparsa_mult_por_matriz(pMatrizEsparsa matriz1, pMatrizEsparsa matriz2)
{
    if (matriz1->columns != matriz2->rows)
        exit(printf("MatrizEsparsa_mul_por_matriz: matrizes de tamanhos invalidos!\n"));

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz1->rows, matriz2->columns);

    int i, j;
    for (i = 0; i < matriz2->columns; i++)
    {
        for (j = 0; j < matriz1->rows; j++)
        {
            if (ForwardList_retorna_head(matriz1->head_rows[j]) == NULL ||
                ForwardList_retorna_head(matriz2->head_columns[i]) == NULL)
                continue; // Se uma das linhas ou colunas for nula, nao ha necessidade de multiplicar (0 * x = 0

            // Multiplicar a linha da matriz1 pela coluna da matriz2
            float valor = ForwardList_multiplica_linha_por_coluna(matriz1->head_rows[j], matriz2->head_columns[i]);
            // Se o resultado for diferente de 0, entao seu valor sera representado por uma celula na i-esima coluna e j-esima linha com valor igual a "valor"
            if (valor != 0)
                MatrizEsparsa_insere(saida, j, i, valor, REPLACE);
        }
    }

    return saida;
}

// Funcao que multiplica uma matriz esparsa por outra matriz esparsa ponto a ponto
// Entrada: ponteiro para a matriz e escalar
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n^2) (quadratica)
pMatrizEsparsa MatrizEsparsa_mult_ponto_a_ponto(pMatrizEsparsa matriz1, pMatrizEsparsa matriz2)
{
    if (matriz1->columns != matriz2->columns ||
        matriz1->rows != matriz2->rows)
        exit(printf("MatrizEsparsa_mul_ponto_a_ponto: matrizes de tamanhos diferentes!\n"));

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz1->rows, matriz1->columns);

    int i;

    // For loop para percorrer ambas as matrizes pelas suas forward lists de linhas, multiplicando seus elementos ponto a ponto
    // Dessa maneira, ja iremos acessar todos as celulas ponto a ponto
    for (i = 0; i < matriz1->rows; i++)
    {
        pNode iter_list1 = ForwardList_retorna_head(matriz1->head_rows[i]);
        pNode iter_list2 = ForwardList_retorna_head(matriz2->head_rows[i]);

        // Se alguma das duas listas chegar no seu fim, nao ha necessidade de continuar, pois 0 * X = 0
        while (iter_list1 != 0 &&
               iter_list2 != 0)
        {
            if (Node_get_column(iter_list1) == Node_get_column(iter_list2))
            {
                float valor = Node_get_value(iter_list1) * Node_get_value(iter_list2);

                // So temos interesse em adicionar valores nao nulos na matriz
                if (valor != 0)
                    MatrizEsparsa_insere(saida,
                                         Node_get_row(iter_list1),
                                         Node_get_column(iter_list1),
                                         valor,
                                         REPLACE);

                iter_list1 = Node_get_next(iter_list1, ROW);
                iter_list2 = Node_get_next(iter_list2, ROW);
            }
            // Pequena verificacao para checar qual lista devemos deslocar
            else if (Node_get_column(iter_list1) < Node_get_column(iter_list2))
                iter_list1 = Node_get_next(iter_list1, ROW);

            else
                iter_list2 = Node_get_next(iter_list2, ROW);
        }
    }

    return saida;
}

// Funcao que troca duas linhas de uma matriz esparsa
// Entrada: ponteiro para a matriz e duas linhas a serem trocadas
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n^2) (quadratica)
pMatrizEsparsa MatrizEsparsa_troca_linhas(pMatrizEsparsa matriz, int row1, int row2)
{
    if (row1 >= matriz->rows ||
        row2 >= matriz->rows ||
        row1 < 0 ||
        row2 < 0)
        exit(printf("MatrizEsparsa_troca_linhas: linha invalida!\n"));

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->rows, matriz->columns);

    int i, linha;
    for (i = 0; i < matriz->rows; i++)
    {
        pNode iter_list = ForwardList_retorna_head(matriz->head_rows[i]);

        if (i == row1)
            linha = row2;

        else if (i == row2)
            linha = row1;

        else
            linha = i;

        while (iter_list != 0)
        {
            MatrizEsparsa_insere(saida,
                                 linha,
                                 Node_get_column(iter_list),
                                 Node_get_value(iter_list),
                                 REPLACE);
            iter_list = Node_get_next(iter_list, ROW);
        }
    }

    return saida;
}

// Funcao que troca duas colunas de uma matriz esparsa
// Entrada: ponteiro para a matriz e duas colunas a serem trocadas
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n^2) (quadratica)
pMatrizEsparsa MatrizEsparsa_troca_colunas(pMatrizEsparsa matriz, int column1, int column2)
{
    if (column1 >= matriz->columns ||
        column2 >= matriz->columns ||
        column1 < 0 ||
        column2 < 0)
        exit(printf("MatrizEsparsa_troca_colunas: coluna invalida!\n"));

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->rows, matriz->columns);

    int i, coluna;
    for (i = 0; i < matriz->columns; i++)
    {
        pNode iter_list = ForwardList_retorna_head(matriz->head_columns[i]);

        if (i == column1)
            coluna = column2;

        else if (i == column2)
            coluna = column1;

        else
            coluna = i;

        while (iter_list != 0)
        {
            MatrizEsparsa_insere(saida,
                                 Node_get_row(iter_list),
                                 coluna,
                                 Node_get_value(iter_list),
                                 REPLACE);
            iter_list = Node_get_next(iter_list, COLUMN);
        }
    }

    return saida;
}

// Funcao que destroi uma matriz esparsa
// Entrada: ponteiro para a matriz
// Saida: nenhum
// Complexidade: O(n) (linear)
void MatrizEsparsa_destroi(pMatrizEsparsa matriz)
{
    int i;
    for (i = 0; i < matriz->columns; i++)
        ForwardList_destroi(matriz->head_columns[i]);

    for (i = 0; i < matriz->rows; i++)
        free(matriz->head_rows[i]);

    free(matriz->head_columns);
    free(matriz->head_rows);
    free(matriz);
}
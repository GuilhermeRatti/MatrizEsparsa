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
    if(matriz1->columns != matriz2->rows)
        exit(printf("MatrizEsparsa_mul_por_matriz: matrizes de tamanhos invalidos!\n"));
    
    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz1->rows, matriz2->columns);

    int i,j;
    for(i=0;i<matriz2->columns;i++)
    {
        for(j=0;j<matriz1->rows;j++)
        {
            if(ForwardList_retorna_head(matriz1->head_rows[j]) == NULL ||
               ForwardList_retorna_head(matriz2->head_columns[i]) == NULL)
                continue; // Se uma das linhas ou colunas for nula, nao ha necessidade de multiplicar (0 * x = 0

            // Multiplicar a linha da matriz1 pela coluna da matriz2
            float valor = ForwardList_multiplica_linha_por_coluna(matriz1->head_rows[j], matriz2->head_columns[i]);
            // Se o resultado for diferente de 0, entao seu valor sera representado por uma celula na i-esima coluna e j-esima linha com valor igual a "valor"
            if(valor != 0)
                MatrizEsparsa_insere(saida, j, i, valor, REPLACE);
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
#include "MatrizEsparsa.h"
#include "ForwardList.h"
#include "Nodes.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma matriz esparsa
// Entrada: numero de linhas e colunas da matriz
// Saida: ponteiro para a matriz criada
// Complexidade: O(n) (linear)
MatrizEsparsa *MatrizEsparsa_cria(int rows, int columns)
{
    MatrizEsparsa *matriz = (MatrizEsparsa *)malloc(sizeof(MatrizEsparsa));
    matriz->rows = rows;
    matriz->columns = columns;

    matriz->head_rows = (ForwardList **)calloc(rows, sizeof(ForwardList *));
    matriz->head_columns = (ForwardList **)calloc(columns, sizeof(ForwardList *));

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
// Complexidade: O(1) (constante)
void MatrizEsparsa_insere(MatrizEsparsa *matriz, int row, int column, float value, Operacao op)
{
    if(row >= matriz->rows || 
       column >= matriz->columns)
        exit(printf("MatrizEsparsa_insere: indices invalidos!\n"));

    Node *new = Node_cria(value, row, column);
    ForwardList_insere(matriz->head_rows[row], &new, op);
    if (new != NULL)
        ForwardList_insere(matriz->head_columns[column], &new, op);
}

// Funcao que le um valor da matriz esparsa
// Entrada: ponteiro para a matriz, linha e coluna
// Saida: valor lido
// Complexidade: O(1) (constante)
float MatrizEsparsa_le_valor(MatrizEsparsa *matriz, int row, int column)
{
    if(row >= matriz->rows || 
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
MatrizEsparsa *MatrizEsparsa_soma(MatrizEsparsa *matriz1, MatrizEsparsa *matriz2)
{
    if(matriz1->columns != matriz2->columns || 
       matriz1->rows != matriz2->rows)
        exit(printf("MatrizEsparsa_soma: matrizes de tamanhos diferentes!\n"));
    
    // Performar uma copia da matriz1 para a matriz de saida
    MatrizEsparsa *saida = MatrizEsparsa_cria(matriz1->rows, matriz1->columns);

    int i;
    for (i = 0; i < matriz1->rows; i++)
    {
        Node *node = matriz1->head_rows[i]->head;
        while (node != NULL)
        {
            MatrizEsparsa_insere(saida, node->row, node->column, node->value, SUM);
            node = node->next_inrow;
        }
    }

    // Somar os valores da matriz2 na matriz de saida por meio da funcao de inserir tambem
    for (i = 0; i < matriz2->rows; i++)
    {
        Node *node = matriz2->head_rows[i]->head;
        while (node != NULL)
        {
            MatrizEsparsa_insere(saida, node->row, node->column, node->value, SUM);
            node = node->next_inrow;
        }
    }

    return saida;
}

// Funcao que destroi uma matriz esparsa
// Entrada: ponteiro para a matriz
// Saida: nenhum
// Complexidade: O(n) (linear)
void MatrizEsparsa_destroi(MatrizEsparsa *matriz)
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
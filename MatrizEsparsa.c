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
// Complexidade: O(n) (linear)
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
// Complexidade: O(n) linear
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
        while (iter_list1 != NULL &&
               iter_list2 != NULL)
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

// Funcao que soma elementos de uma matriz esparsa
// Entrada: ponteiro para a matriz
// Saida: soma dos elementos da matriz
// Complexidade: O(n) (linear)
float _MatrizEsparsa_soma_elementos(pMatrizEsparsa matriz)
{
    int i;
    float soma = 0;
    for (i = 0; i < matriz->rows; i++)
    {
        pNode node = ForwardList_retorna_head(matriz->head_rows[i]);
        while (node != NULL)
        {
            soma += Node_get_value(node);
            node = Node_get_next(node, ROW);
        }
    }

    return soma;
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

        while (iter_list != NULL)
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

        while (iter_list != NULL)
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

// Funcao que retorna a transposta de uma matriz esparsa
// Entrada: ponteiro para a matriz
// Saida: ponteiro para a matriz transposta
// Complexidade: n^2 + n; O(n^2) (quadratica)
// A funcao MatrizEsparsa_insere tem complexidade O(n) (linear), mas levando em consideracao que o n da funcao de MatrizEsparsa_insere cresce apos cada chamada
// Seu fator N cresce de acordo com a sequencia: 1, 2, 3, 4... n-2, n-1, n; que pode ser rearranjado associando termos equidistantes: n+1, n+1, n+1...
// Logo, como a complexidade isolada da funcao MatrizEsparsa_transposta seria linear (n), temos uma complexidade de n*(n+1), que tem big O de O(n^2)
pMatrizEsparsa MatrizEsparsa_transposicao(pMatrizEsparsa matriz)
{
    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->columns, matriz->rows);

    int i;
    for (i = 0; i < matriz->columns; i++)
    {
        pNode iter_list = ForwardList_retorna_head(matriz->head_columns[i]);
        while (iter_list != NULL)
        {
            MatrizEsparsa_insere(saida,
                                 Node_get_column(iter_list), // O truque aqui esta no fato que os atributos de linha e coluna foram invertidos
                                 Node_get_row(iter_list),    // Logo, o resultado sera uma transposicao
                                 Node_get_value(iter_list),
                                 REPLACE);
            iter_list = Node_get_next(iter_list, COLUMN);
        }
    }

    return saida;
}

// Funcao que retorna a fatia selecionada da matriz
// Entrada: ponteiro para a matriz, linha e coluna inicial e final
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n) linear
pMatrizEsparsa MatrizEsparsa_slice(pMatrizEsparsa matriz, int row_inicio, int column_inicio, int row_fim, int column_fim)
{
    if (row_inicio > row_fim || column_inicio > column_fim)
        exit(printf("MatrizEsparsa_slice: indices invalidos!\n"));

    pMatrizEsparsa saida = MatrizEsparsa_cria(row_fim - row_inicio + 1, column_fim - column_inicio + 1);
    int foi_preenchida_pelo_menos_1_vez = 0;

    int i;
    for (i = row_inicio; i < row_fim; i++)
    {
        pNode iter_list = ForwardList_retorna_head(matriz->head_rows[i]);
        while (iter_list != NULL)
        {
            if (Node_get_column(iter_list) >= column_inicio && Node_get_column(iter_list) <= column_fim)
            {
                MatrizEsparsa_insere(saida,
                                     Node_get_row(iter_list) - row_inicio,
                                     Node_get_column(iter_list) - column_inicio,
                                     Node_get_value(iter_list),
                                     REPLACE);
                foi_preenchida_pelo_menos_1_vez = 1;
            }
            else if (Node_get_column(iter_list) > column_fim)
                break;
        }
    }

    if (foi_preenchida_pelo_menos_1_vez == 0)
    {
        MatrizEsparsa_destroi(saida);
        saida = NULL;
    }

    return saida;
}

// Funcao que retorna a matriz resultante da convolucao entre a matriz e o kernel
// Entrada: ponteiro para a matriz e ponteiro para o kernel
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n^2) (quadratica)
pMatrizEsparsa MatrizEsparsa_convolucao(pMatrizEsparsa matriz, pMatrizEsparsa kernel)
{
    if (matriz->rows != matriz->columns || kernel->rows != kernel->columns)
        exit(printf("MatrizEsparsa_convolucao: matriz e kernel devem ser quadrados!\n"));

    if (kernel->rows % 2 == 0)
        exit(printf("MatrizEsparsa_convolucao: kernel deve ter dimensao impar!\n"));

    int i, j;
    int kernel_size = kernel->rows;
    int kernel_center = kernel_size / 2;

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->rows, matriz->columns);

    for (i = 0; i < matriz->rows; i++)
    {
        for (j = 0; j < matriz->columns; j++)
        {
            pMatrizEsparsa slice = MatrizEsparsa_slice(matriz, i - kernel_center, j - kernel_center, i + kernel_center, j + kernel_center);

            if (slice != NULL)
            {
                pMatrizEsparsa mult = MatrizEsparsa_mult_ponto_a_ponto(slice, kernel);
                float soma = _MatrizEsparsa_soma_elementos(mult);
                MatrizEsparsa_insere(saida, i, j, soma, REPLACE);

                MatrizEsparsa_destroi(slice);
                MatrizEsparsa_destroi(mult);
            }
        }
    }

    return saida;
}

// Funcao que retorna a matriz inversa de uma matriz esparsa
// Entrada: ponteiro para a matriz
// Saida: ponteiro para a matriz inversa
// Complexidade: O(n^3) (cubica) (devido a ter que iterar por (linhas x colunas) e para cada iteracao, a chamada de MatrizEsparsa_le_valor, que tem O(n))
void MatrizEsparsa_print_denso(pMatrizEsparsa matriz)
{
    int i, j;
    for (i = 0; i < matriz->rows; i++)
    {
        for (j = 0; j < matriz->columns; j++)
        {
            printf("%f ", MatrizEsparsa_le_valor(matriz, i, j));
        }
        printf("\n");
    }
}

// Funcao que imprime uma matriz esparsa
// Entrada: ponteiro para a matriz
// Saida: nenhum
// Complexidade: O(n) linear
void MatrizEsparsa_print_esparso(pMatrizEsparsa matriz)
{
    int i;
    for (i = 0; i < matriz->rows; i++)
    {
        printf("Linha %d: ", i);
        pNode iter_list = ForwardList_retorna_head(matriz->head_rows[i]);
        while (iter_list != NULL)
        {
            printf("%f ", Node_get_value(iter_list));
            iter_list = Node_get_next(iter_list, ROW);
        }
        printf("\n");
    }
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
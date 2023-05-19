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
// Complexidade: l + c => O(l+c) => O(n) (linear) em relacao as dimensoes
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
// Complexidade: O(el + ec) => O(n) (linear), sendo el elementos na linha e ec elementos na coluna
// Levando em consideracao que o n da funcao de MatrizEsparsa_insere cresce apos cada chamada
// Seu fator N cresce de acordo com a sequencia: 1, 2, 3, 4... n-2, n-1, n; que pode ser rearranjado associando termos equidistantes: n+1, n+1, n+1... n+1
// O que eh equivalente a uma complexidade linear O(n)
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
    // ForwardList_insere tem complexidade O(n) (linear)
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

    // Verifica por qual dimensao a possibilidade de haver menos iteracoes eh maior
    // Se a linha for menor que a coluna, percorre as linhas pela lista referente a posicao coluna
    // e vice-versa
    if (row < column)
        target = ForwardList_le_valor(matriz->head_columns[column], row);
    else
        target = ForwardList_le_valor(matriz->head_rows[row], column);

    return target;
}

// Complexidade O(1)
pNode _MatrizEsparsa_seleciona_linha(pMatrizEsparsa matriz, int linha)
{
    if (linha < 0)
        return NULL;
    else if (linha >= matriz->rows)
        return NULL;
    return ForwardList_retorna_head(matriz->head_rows[linha]);
}

// Funcao que le uma linha da matriz esparsa
// Entrada: ponteiro para a matriz e linha
// Saida: ponteiro para a lista encadeada com os valores da linha
// Complexidade: O(e1 + e2) = O(et) => O(n) (linear), sendo e1 a quantidade de elementos na matriz 1,
// e2 a quantidade de elementos na matriz 2 e et a quantidade de total de elementos somados (combinacao linear de e1 com e2) que resulta em uma funcao linear
pMatrizEsparsa MatrizEsparsa_soma(pMatrizEsparsa matriz1, pMatrizEsparsa matriz2)
{
    if (matriz1->columns != matriz2->columns ||
        matriz1->rows != matriz2->rows)
        exit(printf("MatrizEsparsa_soma: matrizes de tamanhos diferentes!\n"));

    // Performar uma copia da matriz1 para a matriz de saida
    // Compleidade O(n) (linear)
    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz1->rows, matriz1->columns);

    int i;
    // Percorre todos os elementos da matriz1 e insere na matriz de saida, complexidade O(n) (linear), sendo n o numero de elementos na matriz1
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

    // Somar os valores da matriz2 tambem, complexidade O(n) (linear), sendo n o numero de elementos na matriz2
    // Trataremos casos de colisao com uma soma
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
// Complexidade: O(e^2) => O(n^2) (quadratica), sendo e a quantidade de elementos na matriz
pMatrizEsparsa MatrizEsparsa_mult_por_escalar(pMatrizEsparsa matriz, float escalar)
{
    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->rows, matriz->columns);

    int i;
    // Percorre todos os elementos e da matriz 1 e multiplica por um escalar O(n) (linear)
    for (i = 0; i < matriz->rows; i++)
    {
        pNode node = ForwardList_retorna_head(matriz->head_rows[i]);
        while (node != NULL)
        {
            // Para cada elemento, insere um novo elemento na matriz de saida multiplicado pelo escalar O(n) (linear)
            MatrizEsparsa_insere(saida,
                                 Node_get_row(node),
                                 Node_get_column(node),
                                 Node_get_value(node) * escalar,
                                 REPLACE);

            node = Node_get_next(node, ROW); // Complexidade O(1)
        }
    }
    // Complexidade total O(n^2) (quadratica)
    // ????? A complexidade de uma multiplicacao ponto a ponto e por escalar eh mais complexa que matriz por matriz?????
    // Nem o pior caso de uma matriz por matriz chega a n^2, visto que o pior eh n*raiz(n)
    // Curioso, ou estou errado, ou fiz funcoes com complexidade excessiva ou isso eh bem contra intuitivo...

    return saida;
}

// Funcao que multiplica uma matriz esparsa por outra matriz esparsa
// Entrada: ponteiro para a matriz e escalar
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n*raiz(n)) (exponencial de 3/2), sendo n a quantidade de elementos total et = e1 + e2, e1 elementos da matriz 1 e e2 elementos da matriz 2
pMatrizEsparsa MatrizEsparsa_mult_por_matriz(pMatrizEsparsa matriz1, pMatrizEsparsa matriz2)
{
    if (matriz1->rows != matriz2->columns)
        exit(printf("MatrizEsparsa_mul_por_matriz: matrizes de tamanhos invalidos!\n"));

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz1->rows, matriz2->columns);

    int i, j;
    // Percorre todas as colunas c2 da matriz2
    for (i = 0; i < matriz2->columns; i++) // LOOP [2]
    {
        if (ForwardList_retorna_head(matriz2->head_columns[i]) == NULL)
            continue; // Se uma das linhas ou colunas for nula, nao ha necessidade de multiplicar (0 * x = 0)
                      // Isso poupara tempo de processamento consideravel no caso de matrizes esparsas

        // Percorre todas as linhas da matriz1
        // O pior caso seria uma matriz completamente quadrada preenchida (densa) na qual cada linha tem e1 = e2 = l1*c2 elementos,
        // Logo o conjunto dos 2 LOOPS [1] e [2] resultara em uma complexidade de O(e) (linear) no pior caso
        // No melhor caso, onde multiplicamos 1*N por N*1, apesar de termos e1 = e2, e1 != c2 * l1, pois c2 = l1 = 1,
        // portanto, no melhor caso teremos uma complexidade de c2*l1 = 1, O(1) constante
        for (j = 0; j < matriz1->rows; j++) // LOOP [2]
        {
            if (ForwardList_retorna_head(matriz1->head_rows[j]) == NULL)
                continue; // Se uma das linhas ou colunas for nula, nao ha necessidade de multiplicar (0 * x = 0)

            // Multiplicar a linha da matriz1 pela coluna da matriz2
            // Como o pior caso seria se as matrizes fossem densas e quadradas, entao e1=e2=l^2
            // Logo, como o pior caso de uma multiplicacao de linha por coluna sera quando temos que iterar por toda dimensao l, a complexidade sera O(l)
            // Mas traduzindo para uma complexidade em funcao da quantidade de elementos, teremos que: l^2 = e => l = raiz(e) => O(raiz(e))
            // No melhor caso, 1*N por N*1, teremos que iterar por l = N = e, portanto, O(e)
            float valor = ForwardList_multiplica_linha_por_coluna(matriz1->head_rows[j], matriz2->head_columns[i]);

            // Se o resultado for diferente de 0, entao seu valor sera representado por uma celula na i-esima coluna e j-esima linha com valor igual a "valor"
            // A complexidade de insercao eh a quantidade de elementos na linha i ou coluna j da matriz
            // Mas como foi analisado acima, a quantidade de elementos no pior caso sera raiz(e) => O(raiz(e))
            // No melhor caso teremos que o tamanho da linha sera igual a quantidade de elementos, logo l = e => O(e)
            if (valor != 0)
                MatrizEsparsa_insere(saida, j, i, valor, REPLACE);
        }
        // Como resultado temos uma complexidade de O(e) * (O(raiz(e)) + O(raiz(e)) = O(e*raiz(e)) (exponencial de 3/2) para o pior caso
        // E para o melhor caso temos uma complexidade de O(1) * (O(e) + O(e)) = O(e) linear
    }
    // Observacao: eh possivel afirmar que casos de matrizes !NAO QUADRADAS! sao MENOS COMPLEXAS que casos de matrizes !QUADRADAS!, em funcao de E nao nulos
    // Por exemplo, tendo duas matrizes 1xN * Nx1, teremos que e = N*1
    // a complexidade da sequencia de loops LOOP[1] e LOOP[2] de O(1) constante (pois a matriz2 tem 1 unica coluna e a matri1 1 unica linha)
    // e a complexidade do ForwardList_multiplica_linha_por_coluna de O(N) linear, resultando em uma complexidade total de O(1)*O(N) = O(N) = O(e) linear

    // Enquanto isso, uma multiplicacao de mesma quantidade de N elementos, mas disposta de forma quadrada, temos:
    // raiz(N)xraiz(N) * raiz(N)xraiz(N), e = raiz(N)^2 = N,
    // a complexidade dos 2 loops LOOP[1] e LOOP[2] sera O(e) = O(N) linear, como demonstrado na funcao acima,
    // e a complexidade do ForwardList_multiplica_linha_por_coluna de O(raiz(e)) = O(raiz(N)),
    //  resultando em uma complexidade total de O(N*raiz(N)) = O(e*raiz(e)) (exponencial de 3/2).

    // Podemos concluir que dados E elementos nao nulos, a complexidade de uma multiplicacao matricial ira variar de O(E*raiz(E)) e O(E),
    // a depender da disposicao na matriz, de tal forma que o melhor caso seria uma matriz 1xE * Ex1,
    // e o pior caso seria uma matriz quadrada raiz(E)xraiz(E) * raiz(E)xraiz(E)

    return saida;
}

// Funcao que multiplica uma matriz esparsa por outra matriz esparsa ponto a ponto
// Entrada: ponteiro para a matriz e escalar
// Saida: ponteiro para a matriz resultante
// Complexidade: O(n^2) quadratica, sendo n a qtd de elementos n nulos
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
        // Portanto, podemos pular para a proxima linha
        // O conjunto de ambos os while resulta em uma complexidade de O(n), sendo n a quantidade de elementos nao nulos
        while (iter_list1 != NULL &&
               iter_list2 != NULL)
        {
            if (Node_get_column(iter_list1) == Node_get_column(iter_list2))
            {
                float valor = Node_get_value(iter_list1) * Node_get_value(iter_list2);

                // So temos interesse em adicionar valores nao nulos na matriz
                // Tambem eh complexidade de O(n), linear
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
    // Complexidade total: O(n*n) = O(n^2) quadratica, sendo e a qtd de elementos nao nulos

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
    {
        printf("MatrizEsparsa_troca_linhas: linha invalida!\n");
        return NULL;
    }

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->rows, matriz->columns);

    int i, linha;
    // Itera por todos os elementos: O(n)
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
            // Insere cada elemento, complexidade O(n)
            MatrizEsparsa_insere(saida,
                                 linha,
                                 Node_get_column(iter_list),
                                 Node_get_value(iter_list),
                                 REPLACE);
            iter_list = Node_get_next(iter_list, ROW);
        }
    }

    // Complexidade resultante O(n*n) = O(n^2)
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
    {
        printf("MatrizEsparsa_troca_colunas: coluna invalida!\n");
        return NULL;
    }

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->rows, matriz->columns);

    int i, coluna;
    // Itera por todos os elementos: O(n)
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
            // Insere cada elemento, complexidade O(n)
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
pMatrizEsparsa MatrizEsparsa_transposicao(pMatrizEsparsa matriz)
{
    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->columns, matriz->rows);

    int i;
    for (i = 0; i < matriz->columns; i++)
    {
        pNode iter_list = ForwardList_retorna_head(matriz->head_columns[i]);
        // For + while: Itera por todos os elementos: O(n)
        while (iter_list != NULL)
        {
            // Funcao de inserir tem complexidade O(n)
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
// Complexidade: O(n^2) quadratica
pMatrizEsparsa MatrizEsparsa_slice(pMatrizEsparsa matriz, int row_inicio, int column_inicio, int row_fim, int column_fim)
{
    if (row_inicio > row_fim || column_inicio > column_fim)
    {
        printf("MatrizEsparsa_slice: indices invalidos!\n");
        return NULL;
    }

    int slice_row_size, slice_col_size, row_offset = 0, col_offset = 0;

    slice_row_size = row_fim - row_inicio + 1;
    slice_col_size = column_fim - column_inicio + 1;

    if (column_inicio < 0)
    {
        col_offset = -column_inicio;
        column_inicio = 0;
    }
    else if (column_fim > matriz->columns)
        column_fim = matriz->columns - 1;

    if (row_inicio < 0)
    {
        row_offset = -row_inicio;
        row_inicio = 0;
    }
    if (row_fim > matriz->rows)
        row_fim = matriz->rows - 1;

    pMatrizEsparsa saida = MatrizEsparsa_cria(slice_row_size, slice_col_size);

    int i;
    for (i = row_inicio; i <= row_fim; i++)
    {
        pNode iter_list = ForwardList_retorna_head(matriz->head_rows[i]);
        // For + while: percorre todos os elementos O(n)
        while (iter_list != NULL)
        {
            if (Node_get_column(iter_list) >= column_inicio && Node_get_column(iter_list) <= column_fim)
            {
                // Funcao de inserir O(n)
                MatrizEsparsa_insere(saida,
                                     Node_get_row(iter_list) - row_inicio + row_offset,
                                     Node_get_column(iter_list) - column_inicio + col_offset,
                                     Node_get_value(iter_list),
                                     REPLACE);
            }
            else if (Node_get_column(iter_list) > column_fim)
                break;

            iter_list = Node_get_next(iter_list, ROW);
        }
    }

    return saida;
}

// Funcao que retorna a convolucao da matriz pelo kernel
// Entrada: ponteiro para a matriz e kernel
// Saida: ponteiro para a matriz resultante
// Complexidade: E*K^2 (elementos nao nulos da matriz * elementos nao nulos do kernel^2), com pior caso quando a matriz eh completamente preenchida e E = K
// logo O(E^3) => O(n^3) (cubica)
pMatrizEsparsa MatrizEsparsa_convolucao(pMatrizEsparsa matriz, pMatrizEsparsa kernel)
{
    if (kernel->rows % 2 == 0 || kernel->columns % 2 == 0)
    {
        printf("MatrizEsparsa_convolucao: kernel deve ter dimensoes impar!\n");
        return NULL;
    }

    int i, k;
    int kernel_center_row = kernel->rows / 2;
    int kernel_center_col = kernel->columns / 2;

    pNode selected_rows[kernel->rows];
    int next_step_rows[kernel->rows];

    pMatrizEsparsa saida = MatrizEsparsa_cria(matriz->rows, matriz->columns);

    // O algoritimo implementado foi feito para tratar a convolucao de forma esparsa e somente operar a multiplicacao ponto a ponto pelo kernel
    // em situacoes que englobariam elementos nao nulos, seguindo uma selecao concorrente de N listas encadeadas de linhas,
    // sendo N o numero de linhas de um kernel, tendo o centro de seu kernel exatamente sobre a posicao i, para qualquer i do for abaixo
    for (i = 0; i < matriz->rows; i++)
    {
        // Para cada i, sao selecionadas as as linhas que a primeira iteracao do kernel englobaria (algumas linhas serao negativas, mas isso esta sendo tratado)
        for (k = 0; k < kernel->rows; k++)
        {
            // O(1)
            selected_rows[k] = _MatrizEsparsa_seleciona_linha(matriz, i - kernel_center_row + k);
            next_step_rows[k] = 0; // Funcao auxiliar que sera esclarecida abaixo
        }

        // O centro do kernel por linha ficara "fixo" na coluna i, mas vai variar de 0 ao maximo de colunas, de acordo com as posicoes dos elementos
        // nao nulos nas linhas selecionadas. Instanciamos ele inicialmente como 0 entao.
        int column_center = 0;

        while (1)
        {
            int continue_iterating = 0, nearest_column = matriz->columns;
            // Entraremos num loop com condicao de parada como o momento em que nao existam mais elementos nao nulos em todas as linhas analisadas ao mesmo tempo
            for (k = 0; k < kernel->rows; k++)
            {
                if (selected_rows[k] != NULL)
                {
                    if (Node_get_column(selected_rows[k]) <= nearest_column)
                    {
                        nearest_column = Node_get_column(selected_rows[k]);
                        next_step_rows[k] = 1;
                    }
                    // se ainda existir uma linha com um elemento nao nulo, flag = 1
                    continue_iterating = 1;
                }
            }

            // se eventualmente flag=0, n existem mais elementos a serem iterados com o kernel centrado na linha i
            if (!continue_iterating)
                break;

            while (column_center <= (nearest_column + kernel_center_col))
            {
                // For + while + while: complexidade O(n), sendo n qtd de elementos n nulos na matriz com pior caso onde a matriz eh completamente preenchida
                // para cada novo centro de kernel sendo iterado, eh feita uma convolucao a partir do centro do kernel anterior, nunca antes
                // dessa forma, no maximo (pior caso) teremos que iterar sobre todos os elementos da coluna da matriz, por linha O(l*c), l*c = n, O(n)
                // e no minimo uma quantidade de O(nl + kl/2), sendo nl a qtd de elementos n nulos na linha e kl a dimensao de linhas do kernel, com nl + kl/2 >= c
                // logo, no minimo O(n + (kl/2)*l + (kc/2)*c) = O(n), linear, com n+(kl/2)*l + (kc/c)*2 <= l*c
                if (column_center < (nearest_column - kernel_center_col))
                    column_center = nearest_column - kernel_center_col;

                // Complexidade O(K^2), quadratica
                pMatrizEsparsa slice = MatrizEsparsa_slice(matriz,
                                                           i - kernel_center_row,              // linha de inicio
                                                           column_center - kernel_center_col,  // coluna de inicio
                                                           i + kernel_center_row,              // linha de fim
                                                           column_center + kernel_center_col); // coluna de fim

                // Complexidade O(K^2), quadratica
                pMatrizEsparsa mult = MatrizEsparsa_mult_ponto_a_ponto(slice, kernel);
                float soma = _MatrizEsparsa_soma_elementos(mult);
                if (soma != 0)
                    MatrizEsparsa_insere(saida,
                                         i,
                                         column_center,
                                         soma,
                                         REPLACE);
                // Complexidade O(K), linear
                MatrizEsparsa_destroi(mult);
                MatrizEsparsa_destroi(slice);

                if (column_center >= matriz->columns)
                    break;
                else
                    column_center++;
            }

            for (k = 0; k < kernel->columns; k++)
            {
                // A ideia do next step rows eh concorrentemente dar um next em todos os nodes que ja foram iterados pelo kernel com centro naquela posicao coluna
                // para que na proxima iteracao, o kernel possa ser centrado na proxima posicao coluna nao nula mais proxima
                if (next_step_rows[k])
                {
                    next_step_rows[k] = 0;
                    selected_rows[k] = Node_get_next(selected_rows[k], ROW);
                }
            }
        }
        // Complexidade resultante: O(n^3), cubica
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
            printf("%.0f ", MatrizEsparsa_le_valor(matriz, i, j));
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

// Funcao que imprime uma matriz esparsa em um arquivo
// Entrada: ponteiro para a matriz e nome do arquivo
// Saida: nenhum
// Complexidade: O(n) linear
void MatrizEsparsa_escreve_binario(pMatrizEsparsa matriz, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo para escrita\n");
        return;
    }

    fwrite(&matriz->rows, sizeof(int), 1, arquivo);
    fwrite(&matriz->columns, sizeof(int), 1, arquivo);

    int i;
    for (i = 0; i < matriz->rows; i++)
    {
        pNode iter_list = ForwardList_retorna_head(matriz->head_rows[i]);
        while (iter_list != NULL)
        {
            int column = Node_get_column(iter_list);
            float value = Node_get_value(iter_list);
            fwrite(&i, sizeof(int), 1, arquivo);
            fwrite(&column, sizeof(int), 1, arquivo);
            fwrite(&value, sizeof(float), 1, arquivo);
            iter_list = Node_get_next(iter_list, ROW);
        }
    }

    fclose(arquivo);
}

// Funcao que le uma matriz esparsa de um arquivo
// Entrada: nome do arquivo
// Saida: ponteiro para a matriz
// Complexidade: O(n^2) linear
pMatrizEsparsa MatrizEsparsa_le_binario(char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo para leitura\n");
        return NULL;
    }

    int rows, columns;
    fread(&rows, sizeof(int), 1, arquivo);
    fread(&columns, sizeof(int), 1, arquivo);

    pMatrizEsparsa matriz = MatrizEsparsa_cria(rows, columns);

    // Complexidade O(n)
    while (feof(arquivo) == 0)
    {
        int row, column;
        float value;
        fread(&row, sizeof(int), 1, arquivo);
        fread(&column, sizeof(int), 1, arquivo);
        fread(&value, sizeof(float), 1, arquivo);

        // Complexidade O(n)
        MatrizEsparsa_insere(matriz, row, column, value, REPLACE);
    }

    fclose(arquivo);

    return matriz;
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
#include "Nodes.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    float value;
    int row;
    int column;
    struct Node *next_inrow;
    struct Node *next_incolumn;
};

// Funcao que cria uma celula
// Entrada: nenhum
// Saida: ponteiro para a celula criada
// Complexidade: O(1) (constante)
pNode Node_cria(float value, int row, int column)
{
    pNode node = (pNode)calloc(1, sizeof(struct Node));
    node->next_inrow = NULL;
    node->next_incolumn = NULL;
    node->value = value;
    node->row = row;
    node->column = column;

    return node;
}

// Funcao que retorna a celula anterior
// Entrada: ponteiro para a celula e direcao
// Saida: ponteiro para a celula anterior
// Complexidade: O(1) (constante)
pNode Node_get_next(pNode node, Direction direction)
{
    if (direction == ROW)
        return node->next_inrow;
    else
        return node->next_incolumn;
}

// Funcao que altera a celula anterior
// Entrada: ponteiro para a celula, ponteiro para a nova celula e direcao
// Saida: nenhum (muda por referencia)
// Complexidade: O(1) (constante)
void Node_set_next(pNode node, pNode next, Direction direction)
{
    if (direction == ROW)
        node->next_inrow = next;
    else
        node->next_incolumn = next;
}

// Funcao que retorna a linha da celula
// Entrada: ponteiro para a celula
// Saida: linha da celula
// Complexidade: O(1) (constante)
float Node_get_value(pNode node)
{
    return node->value;
}

// Funcao que altera o valor da celula
// Entrada: ponteiro para a celula e novo valor
// Saida: nenhum (muda por referencia)
// Complexidade: O(1) (constante)
void Node_set_value(pNode node, float value)
{
    node->value = value;
}

// Funcao que retorna a linha da celula
// Entrada: ponteiro para a celula
// Saida: linha da celula
// Complexidade: O(1) (constante)
int Node_get_row(pNode node)
{
    return node->row;
}

// Funcao que retorna a coluna da celula
// Entrada: ponteiro para a celula
// Saida: coluna da celula
// Complexidade: O(1) (constante)
int Node_get_column(pNode node)
{
    return node->column;
}

// Funcao que destroi uma celula
// Entrada: ponteiro para a celula
// Saida: nenhum
// Complexidade: O(1) (constante)
void Node_destroi(pNode node)
{
    free(node);
    node = NULL;
}
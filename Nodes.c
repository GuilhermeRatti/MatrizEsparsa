#include "Nodes.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma celula
// Entrada: nenhum
// Saida: ponteiro para a celula criada
// Complexidade: O(1) (constante)
Node *Node_cria(float value, int row, int column)
{
    Node *node = (Node *)calloc(1, sizeof(Node));
    node->next_inrow = NULL;
    node->next_incolumn = NULL;
    node->value = value;
    node->row = row;
    node->column = column;

    return node;
}

// Funcao que destroi uma celula
// Entrada: ponteiro para a celula
// Saida: nenhum
// Complexidade: O(1) (constante)
void Node_destroi(Node *node)
{
    free(node);
    node = NULL;
}
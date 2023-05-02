#include "ForwardList.h"
#include "Nodes.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma lista encadeada
// Entrada: nenhum
// Saida: ponteiro para a lista criada
// Complexidade: O(1) (constante)
ForwardList *ForwardList_cria(Direction tipo)
{
    ForwardList *lista = (ForwardList *)calloc(1, sizeof(ForwardList));
    lista->head = NULL;
    lista->size = 0;
    lista->tipo = tipo;

    return lista;
}

// Funcao que insere um valor na lista encadeada
// Entrada: ponteiro para a lista, valor a ser inserido e posicao a ser inserido
// Saida: nenhum
// Complexidade: O(n) (linear) + O(1) (constante) = O(n) (linear)
void ForwardList_insere(ForwardList *lista, Node **node, Operacao op)
{
    Node *aux = lista->head, *past_node = NULL;
    // Seleciona a posicao a ser inserida na lista
    while (aux != NULL)
    {
        
        if (lista->tipo == COLUMN)
        {
            if (aux->row >= (*node)->row)
                break;

            past_node = aux;    
            aux = aux->next_incolumn;
        }

        else
        {
            if (aux->column >= (*node)->column)
                break;
            
            past_node = aux;
            aux = aux->next_inrow;
        }
    }

    // Caso estejamos sobrescrevendo uma posicao ja preenchida, entao eh mais facil mudar o valor e retornar
    // isso funciona porque se estivermos alterando uma celula ja existente, entao vamos alterar seu valor tanto
    // na lista de linhas quanto na lista de colunas, entao nao precisamos nos preocupar com a outra lista
    if(aux!=NULL)
    {
        if ((lista->tipo == ROW && aux->column == (*node)->column) ||
            (lista->tipo == COLUMN && aux->row == (*node)->row))
        {
            if(op==REPLACE)
            {
                aux->value = (*node)->value;
                Node_destroi(*node);
                (*node) = NULL;
            }
            // Caso na verdade estamos realizando uma operacao de soma, nao vamos sobrescrever o valor
            // e sim somar o valor antigo com o novo, alem de que nao vamos dar free no node analisado
            else
                aux->value += (*node)->value;

            return;
        }
    }

    // Caso estejamos inserindo na primeira posicao da lista
    if (past_node == NULL)
    {
        lista->head = (*node);
        if (lista->tipo == COLUMN)
            (*node)->next_incolumn = aux;
        else
            (*node)->next_inrow = aux;
    }
    else // Caso estejamos inserindo em qualquer outra posicao
    {
        if (lista->tipo == COLUMN)
        {
            past_node->next_incolumn = (*node);
            (*node)->next_incolumn = aux;
        }
        else
        {
            past_node->next_inrow = (*node);
            (*node)->next_inrow = aux;
        }
    }

    lista->size++;
}

// Funcao que le um valor da lista encadeada dada uma posicao
// Entrada: ponteiro para a lista e posicao a ser lida
// Saida: valor lido
// Complexidade: O(n) (linear)
float ForwardList_le_valor(ForwardList *lista, int position)
{
    Node *aux = lista->head;
    float target = 0; // Vamos assumir que caso nenhum valor seja achado na posicao dada
                      // entao o valor eh 0
    while (aux != NULL)
    {
        if ((lista->tipo == ROW && aux->column == position) ||
            (lista->tipo == COLUMN && aux->row == position))
        {
            target = aux->value;
            break;
        }
        else if (lista->tipo == ROW && aux->column > position)
            break;

        else if (lista->tipo == COLUMN && aux->row > position)
            break;
        
        if(lista->tipo == COLUMN)
            aux = aux->next_incolumn;
        else
            aux = aux->next_inrow;
    }

    return target;
}

// Funcao que destroi uma lista encadeada
// Entrada: ponteiro para a lista
// Saida: nenhum
// Complexidade: O(n) (linear)
void ForwardList_destroi(ForwardList *lista)
{
    Node *node = lista->head, *next;
    while (node != NULL)
    {
        if (lista->tipo == COLUMN)
            next = node->next_incolumn;
        else
            next = node->next_inrow;

        Node_destroi(node);
        node = next;
    }
    node = NULL;

    free(lista);
    lista = NULL;
}
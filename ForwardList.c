#include "ForwardList.h"
#include "Nodes.h"
#include <stdio.h>
#include <stdlib.h>

struct ForwardList
{
    pNode head;
    int size;
    Direction tipo;
} ForwardList;

// Funcao que cria uma lista encadeada
// Entrada: nenhum
// Saida: ponteiro para a lista criada
// Complexidade: O(1) (constante)
pForwardList ForwardList_cria(Direction tipo)
{
    pForwardList lista = (pForwardList)calloc(1, sizeof(struct ForwardList));
    lista->head = NULL;
    lista->size = 0;
    lista->tipo = tipo;

    return lista;
}

// Funcao que insere um valor na lista encadeada
// Entrada: ponteiro para a lista, valor a ser inserido e posicao a ser inserido
// Saida: valor booleano (0 ou 1 - true ou false) dizendo se foi tratado uma situacao de colisao ou nao
// Complexidade: O(n) (linear) + O(1) (constante) = O(n) (linear)
int ForwardList_insere(pForwardList lista, pNode node, Operacao op)
{
    pNode aux = lista->head, past_node = NULL;
    // Seleciona a posicao a ser inserida na lista
    while (aux != NULL)
    {
        if (lista->tipo == COLUMN)
        {
            if (Node_get_row(aux) >= Node_get_row(node))
                break;

            past_node = aux;
            aux = Node_get_next(aux, COLUMN);
        }

        else
        {
            if (Node_get_column(aux) >= Node_get_column(node))
                break;

            past_node = aux;
            aux = Node_get_next(aux, ROW);
        }
    }

    // Caso estejamos sobrescrevendo uma posicao ja preenchida, entao eh mais facil mudar o valor e retornar
    // isso funciona porque se estivermos alterando uma celula ja existente, entao vamos alterar seu valor tanto
    // na lista de linhas quanto na lista de colunas, entao nao precisamos nos preocupar com a outra lista
    if (aux != NULL)
    {
        if ((lista->tipo == ROW && Node_get_column(aux) == Node_get_column(node)) ||
            (lista->tipo == COLUMN && Node_get_row(aux) == Node_get_row(node)))
        {
            if (op == REPLACE)
                Node_set_value(aux, Node_get_value(node));
            else
                Node_set_value(aux, Node_get_value(aux) + Node_get_value(node));
            
            Node_destroi(node);
            return 1; // Ocorreu uma colisao
        }
    }

    // Caso estejamos inserindo na primeira posicao da lista
    if (past_node == NULL)
    {
        lista->head = (node);
        if (lista->tipo == COLUMN)
            Node_set_next(node, aux, COLUMN);
        else
            Node_set_next(node, aux, ROW);
    }
    else // Caso estejamos inserindo em qualquer outra posicao
    {
        if (lista->tipo == COLUMN)
        {
            Node_set_next(past_node, (node), COLUMN);
            Node_set_next(node, aux, COLUMN);
        }
        else
        {
            Node_set_next(past_node, (node), ROW);
            Node_set_next(node, aux, ROW);
        }
    }

    lista->size++;

    return 0;
}

// Funcao que le um valor da lista encadeada dada uma posicao
// Entrada: ponteiro para a lista e posicao a ser lida
// Saida: valor lido
// Complexidade: O(n) (linear)
float ForwardList_le_valor(pForwardList lista, int position)
{
    pNode aux = lista->head;
    float target = 0; // Vamos assumir que caso nenhum valor seja achado na posicao dada
                      // entao o valor eh 0
    while (aux != NULL)
    {
        if ((lista->tipo == ROW && Node_get_column(aux) == position) ||
            (lista->tipo == COLUMN && Node_get_row(aux) == position))
        {
            target = Node_get_value(aux);
            break;
        }
        else if (lista->tipo == ROW && Node_get_column(aux) > position)
            break;

        else if (lista->tipo == COLUMN && Node_get_row(aux) > position)
            break;

        if (lista->tipo == COLUMN)
            aux = Node_get_next(aux, COLUMN);
        else
            aux = Node_get_next(aux, ROW);
    }

    return target;
}

// Funcao que retorna o tamanho da lista encadeada
// Entrada: ponteiro para a lista
// Saida: tamanho da lista
// Complexidade: O(1) (constante)
pNode ForwardList_retorna_head(pForwardList lista)
{
    return lista->head;
}

// Funcao que retorna o tamanho da lista encadeada
// Entrada: ponteiro para a lista
// Saida: tamanho da lista
// Complexidade: O(1) (constante)
int ForwardList_retorna_tamanho(pForwardList lista)
{
    return lista->size;
}

// Funcao que retorna o tipo da lista encadeada
// Entrada: ponteiro para a lista
// Saida: tipo da lista
// Complexidade: O(1) (constante)
Direction ForwardList_retorna_tipo(pForwardList lista)
{
    return lista->tipo;
}

// Funcao que multiplica uma linha por uma coluna
// Entrada: ponteiro para a linha e ponteiro para a coluna
// Saida: resultado da multiplicacao
// Complexidade: O(n) (linear)
float ForwardList_multiplica_linha_por_coluna(pForwardList linha, pForwardList coluna)
{
    pNode aux_linha = linha->head, aux_coluna = coluna->head;
    float resultado = 0;

    // Enquanto nenhuma das duas listas acaba (porque depois disso teremos 0*X = 0)
    while (aux_linha != NULL && aux_coluna != NULL)
    {
        // Se a coluna da linha for igual a linha da coluna, entao multiplicamos
        if (Node_get_column(aux_linha) == Node_get_row(aux_coluna))
        {
            resultado += Node_get_value(aux_linha) * Node_get_value(aux_coluna);
            aux_linha = Node_get_next(aux_linha, ROW);
            aux_coluna = Node_get_next(aux_coluna, COLUMN);
        }
        // Se a posicao coluna da lista de linha for maior que a posicao linha da lista de coluna, entao avancamos para o proximo elemento da lista de coluna
        else if (Node_get_column(aux_linha) > Node_get_row(aux_coluna))
            aux_coluna = Node_get_next(aux_coluna, COLUMN);
        // Senao avancamos para o proximo elemento da lista de linha
        else
            aux_linha = Node_get_next(aux_linha, ROW);
    }

    return resultado;
}

// Funcao que destroi uma lista encadeada
// Entrada: ponteiro para a lista
// Saida: nenhum
// Complexidade: O(n) (linear)
void ForwardList_destroi(pForwardList lista)
{
    pNode node = lista->head, next;
    while (node != NULL)
    {
        if (lista->tipo == COLUMN)
            next = Node_get_next(node, COLUMN);
        else
            next = Node_get_next(node, ROW);

        Node_destroi(node);
        node = next;
    }
    node = NULL;

    free(lista);
    lista = NULL;
}
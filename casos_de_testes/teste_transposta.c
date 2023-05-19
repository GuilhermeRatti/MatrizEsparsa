#include <stdio.h>
#include <stdlib.h>
#include "../matriz/MatrizEsparsa.h"

int main(int argc, char const *argv[])
{
    pMatrizEsparsa matriz1 = MatrizEsparsa_cria(5, 5);
    int i,j;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            MatrizEsparsa_insere(matriz1,i,j,i,REPLACE);
        }
    }

    printf("\nMATRIZ 1:\n");
    MatrizEsparsa_print_denso(matriz1);

    /*
        MATRIZ 1:
        0 0 0 0 0 
        1 1 1 1 1 
        2 2 2 2 2 
        3 3 3 3 3 
        4 4 4 4 4 
    */

    pMatrizEsparsa matriz2 = MatrizEsparsa_transposicao(matriz1);

    printf("\nMATRIZ 2:\n");
    MatrizEsparsa_print_denso(matriz2);
    /*
        MATRIZ 2:
        0 1 2 3 4 
        0 1 2 3 4 
        0 1 2 3 4 
        0 1 2 3 4 
        0 1 2 3 4 
    */

    MatrizEsparsa_destroi(matriz1);
    MatrizEsparsa_destroi(matriz2);

    return 0;
}

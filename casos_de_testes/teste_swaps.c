#include "MatrizEsparsa.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pMatrizEsparsa matriz1 = MatrizEsparsa_cria(3, 3);

    MatrizEsparsa_insere(matriz1, 1, 0, 1, REPLACE);
    MatrizEsparsa_insere(matriz1, 1, 1, 1, REPLACE);
    MatrizEsparsa_insere(matriz1, 1, 2, 1, REPLACE);
    MatrizEsparsa_insere(matriz1, 2, 0, 2, REPLACE);
    MatrizEsparsa_insere(matriz1, 2, 1, 2, REPLACE);
    MatrizEsparsa_insere(matriz1, 2, 2, 2, REPLACE);

    int i,j;
    printf("\nMATRIZ 1:\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            printf("%f ", MatrizEsparsa_le_valor(matriz1, i, j));
        }
        printf("\n");
    }

    //MATRIZ 1
    // 0.000000 0.000000 0.000000
    // 1.000000 1.000000 1.000000
    // 2.000000 2.000000 2.000000

    pMatrizEsparsa matriz2 = MatrizEsparsa_troca_linhas(matriz1, 0, 1);

    printf("\nMATRIZ 2:\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            printf("%f ", MatrizEsparsa_le_valor(matriz2, i, j));
        }
        printf("\n");
    }

    //MATRIZ 2
    // 1.000000 1.000000 1.000000
    // 0.000000 0.000000 0.000000
    // 2.000000 2.000000 2.000000

    pMatrizEsparsa matriz3 = MatrizEsparsa_cria(3, 3);
    MatrizEsparsa_insere(matriz3, 0, 1, 1, REPLACE);
    MatrizEsparsa_insere(matriz3, 0, 2, 2, REPLACE);
    MatrizEsparsa_insere(matriz3, 1, 1, 1, REPLACE);
    MatrizEsparsa_insere(matriz3, 1, 2, 2, REPLACE);
    MatrizEsparsa_insere(matriz3, 2, 1, 1, REPLACE);
    MatrizEsparsa_insere(matriz3, 2, 2, 2, REPLACE);

    printf("\nMATRIZ 3:\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            printf("%f ", MatrizEsparsa_le_valor(matriz3, i, j));
        }
        printf("\n");
    }

    //MATRIZ 3
    // 0.000000 1.000000 2.000000
    // 0.000000 1.000000 2.000000
    // 0.000000 1.000000 2.000000

    pMatrizEsparsa matriz4 = MatrizEsparsa_troca_colunas(matriz3, 0, 1);

    printf("\nMATRIZ 4:\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            printf("%f ", MatrizEsparsa_le_valor(matriz4, i, j));
        }
        printf("\n");
    }

    //MATRIZ 4
    // 1.000000 0.000000 2.000000
    // 1.000000 0.000000 2.000000
    // 1.000000 0.000000 2.000000

    MatrizEsparsa_destroi(matriz1);
    MatrizEsparsa_destroi(matriz2);
    MatrizEsparsa_destroi(matriz3);
    MatrizEsparsa_destroi(matriz4);

    return 0;
}

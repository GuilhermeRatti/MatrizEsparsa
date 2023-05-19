#include "../matriz/MatrizEsparsa.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pMatrizEsparsa matriz1 = MatrizEsparsa_cria(3, 3);
    MatrizEsparsa_insere(matriz1, 0, 0, 1, REPLACE);
    MatrizEsparsa_insere(matriz1, 0, 1, 2, REPLACE);
    MatrizEsparsa_insere(matriz1, 1, 0, 4, REPLACE);
    MatrizEsparsa_insere(matriz1, 1, 2, 6, REPLACE);
    MatrizEsparsa_insere(matriz1, 2, 1, 8, REPLACE);
    MatrizEsparsa_insere(matriz1, 2, 2, 9, REPLACE);

    printf("\nMATRIZ 2:\n");
    MatrizEsparsa_print_denso(matriz1);

    //MATRIZ 1
    // 1.000000 2.000000 0.000000
    // 4.000000 0.000000 6.000000
    // 0.000000 8.000000 9.000000

    pMatrizEsparsa matriz2 = MatrizEsparsa_cria(3, 3);
    MatrizEsparsa_insere(matriz2, 0, 1, 8, REPLACE);
    MatrizEsparsa_insere(matriz2, 0, 2, 7, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 0, 6, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 2, 4, REPLACE);
    MatrizEsparsa_insere(matriz2, 2, 0, 3, REPLACE);
    MatrizEsparsa_insere(matriz2, 2, 1, 2, REPLACE);

    printf("\nMATRIZ 2:\n");
    MatrizEsparsa_print_denso(matriz2);
    
    //MATRIZ 2
    // 0.000000 8.000000 7.000000
    // 6.000000 0.000000 4.000000
    // 3.000000 2.000000 0.000000

    pMatrizEsparsa matriz3 = MatrizEsparsa_mult_ponto_a_ponto(matriz1, matriz2);

    printf("\nMATRIZ 3:\n");
    MatrizEsparsa_print_denso(matriz3);

    //MATRIZ 3
    // 0.000000 16.000000 0.000000
    // 24.000000 0.000000 24.000000
    // 0.000000 16.000000 0.000000

    MatrizEsparsa_destroi(matriz1);
    MatrizEsparsa_destroi(matriz2);
    MatrizEsparsa_destroi(matriz3);

    return 0;
}

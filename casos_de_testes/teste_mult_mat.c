#include "../matriz/MatrizEsparsa.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // TESTA TAMBEM AS FUNCOES MatrizEsparsa_cria, MatrizEsparsa_insere E MatrizEsparsa_le_valor
    pMatrizEsparsa matriz = MatrizEsparsa_cria(3, 3);
    MatrizEsparsa_insere(matriz, 0, 0, 1, REPLACE);
    MatrizEsparsa_insere(matriz, 1, 1, 1, REPLACE);
    MatrizEsparsa_insere(matriz, 2, 2, 1, REPLACE);

    printf("=====================\n");
    printf("========TESTE 1======\n");
    printf("=====================\n\n");

    printf("\nMATRIZ 1:\n");
    MatrizEsparsa_print_denso(matriz);

    // MATRIZ 1
    //  1.000000 0.000000 0.000000
    //  0.000000 1.000000 0.000000
    //  0.000000 0.000000 1.000000

    pMatrizEsparsa matriz2 = MatrizEsparsa_cria(3, 3);

    MatrizEsparsa_insere(matriz2, 0, 0, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 0, 1, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 0, 2, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 0, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 1, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 2, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 2, 0, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 2, 1, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 2, 2, 2, REPLACE);

    printf("\nMATRIZ 2:\n");
    MatrizEsparsa_print_denso(matriz2);
    // MATRIZ 2
    //  2.000000 2.000000 2.000000
    //  2.000000 2.000000 2.000000
    //  2.000000 2.000000 2.000000

    pMatrizEsparsa mult1 = MatrizEsparsa_mult_por_matriz(matriz, matriz2);

    printf("\nMULT MATRIZ 1 * MATRIZ 2:\n");
    MatrizEsparsa_print_denso(mult1);

    // RESULTADO ESPERADO
    //  2.000000 2.000000 2.000000
    //  2.000000 2.000000 2.000000
    //  2.000000 2.000000 2.000000

    printf("=====================\n");
    printf("========TESTE 2======\n");
    printf("=====================\n");

    printf("\nMATRIZ 3:\n");
    pMatrizEsparsa matriz3 = MatrizEsparsa_cria(5, 3);
    MatrizEsparsa_insere(matriz3, 1, 1, 12, REPLACE);
    MatrizEsparsa_insere(matriz3, 1, 1, 7, REPLACE);
    MatrizEsparsa_insere(matriz3, 2, 0, 45, REPLACE);
    MatrizEsparsa_insere(matriz3, 2, 2, 34, REPLACE);
    MatrizEsparsa_insere(matriz3, 3, 1, 43, REPLACE);
    MatrizEsparsa_insere(matriz3, 4, 0, 83, REPLACE);
    MatrizEsparsa_insere(matriz3, 4, 2, 65, REPLACE);

    MatrizEsparsa_print_denso(matriz3);

    // MATRIZ 3
    // 0.000000  0.000000  0.000000
    // 0.000000  12.000000 7.000000
    // 45.000000 0.000000  34.000000
    // 0.000000  43.000000 0.000000
    // 83.000000 0.000000  65.000000

    printf("\nMATRIZ 4:\n");
    pMatrizEsparsa matriz4 = MatrizEsparsa_cria(3, 5);
    MatrizEsparsa_insere(matriz4, 0, 1, 54, REPLACE);
    MatrizEsparsa_insere(matriz4, 0, 2, 9, REPLACE);
    MatrizEsparsa_insere(matriz4, 0, 4, 22, REPLACE);
    MatrizEsparsa_insere(matriz4, 1, 1, 3, REPLACE);
    MatrizEsparsa_insere(matriz4, 1, 3, 233, REPLACE);
    MatrizEsparsa_insere(matriz4, 2, 2, 41, REPLACE);
    MatrizEsparsa_insere(matriz4, 2, 4, 1, REPLACE);

    MatrizEsparsa_print_denso(matriz4);

    // MATRIZ 4:
    // 0.000000 54.000000 9.000000 0.000000 22.000000
    // 0.000000 3.000000 0.000000 233.000000 0.000000
    // 0.000000 0.000000 41.000000 0.000000 1.000000

    printf("\nMULT MATRIZ 3 * MATRIZ 4:\n");
    pMatrizEsparsa mult2 = MatrizEsparsa_mult_por_matriz(matriz3, matriz4);

    MatrizEsparsa_print_denso(mult2);

    // RESULTADO ESPERADO
    // 0.000000 0.000000 0.000000 0.000000 0.000000
    // 0.000000 21.000000 0.000000 1631.000000 0.000000
    // 0.000000 2430.000000 1799.000000 0.000000 1024.000000
    // 0.000000 129.000000 0.000000 10019.000000 0.000000
    // 0.000000 4482.000000 3412.000000 0.000000 1891.000000

    MatrizEsparsa_destroi(matriz);
    MatrizEsparsa_destroi(matriz2);
    MatrizEsparsa_destroi(mult1);
    MatrizEsparsa_destroi(matriz3);
    MatrizEsparsa_destroi(matriz4);
    MatrizEsparsa_destroi(mult2);

    return 0;
}

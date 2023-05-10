#include "MatrizEsparsa.h"
#include "ForwardList.h"
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
    printf("%f ", MatrizEsparsa_le_valor(matriz, 0, 0));
    printf("%f ", MatrizEsparsa_le_valor(matriz, 0, 1));
    printf("%f\n", MatrizEsparsa_le_valor(matriz, 0, 2));
    printf("%f ", MatrizEsparsa_le_valor(matriz, 1, 0));
    printf("%f ", MatrizEsparsa_le_valor(matriz, 1, 1));
    printf("%f\n", MatrizEsparsa_le_valor(matriz, 1, 2));
    printf("%f ", MatrizEsparsa_le_valor(matriz, 2, 0));
    printf("%f ", MatrizEsparsa_le_valor(matriz, 2, 1));
    printf("%f\n", MatrizEsparsa_le_valor(matriz, 2, 2));

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
    printf("%f ", MatrizEsparsa_le_valor(matriz2, 0, 0));
    printf("%f ", MatrizEsparsa_le_valor(matriz2, 0, 1));
    printf("%f\n", MatrizEsparsa_le_valor(matriz2, 0, 2));
    printf("%f ", MatrizEsparsa_le_valor(matriz2, 1, 0));
    printf("%f ", MatrizEsparsa_le_valor(matriz2, 1, 1));
    printf("%f\n", MatrizEsparsa_le_valor(matriz2, 1, 2));
    printf("%f ", MatrizEsparsa_le_valor(matriz2, 2, 0));
    printf("%f ", MatrizEsparsa_le_valor(matriz2, 2, 1));
    printf("%f\n", MatrizEsparsa_le_valor(matriz2, 2, 2));
    // MATRIZ 2
    //  2.000000 2.000000 2.000000
    //  2.000000 2.000000 2.000000
    //  2.000000 2.000000 2.000000

    pMatrizEsparsa mult1 = MatrizEsparsa_mult_por_matriz(matriz, matriz2);

    printf("\nMULT MATRIZ 1 * MATRIZ 2:\n");
    printf("%f ", MatrizEsparsa_le_valor(mult1, 0, 0));
    printf("%f ", MatrizEsparsa_le_valor(mult1, 0, 1));
    printf("%f\n", MatrizEsparsa_le_valor(mult1, 0, 2));
    printf("%f ", MatrizEsparsa_le_valor(mult1, 1, 0));
    printf("%f ", MatrizEsparsa_le_valor(mult1, 1, 1));
    printf("%f\n", MatrizEsparsa_le_valor(mult1, 1, 2));
    printf("%f ", MatrizEsparsa_le_valor(mult1, 2, 0));
    printf("%f ", MatrizEsparsa_le_valor(mult1, 2, 1));
    printf("%f\n", MatrizEsparsa_le_valor(mult1, 2, 2));

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

    printf("%f ", MatrizEsparsa_le_valor(matriz3,0,0));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,0,1));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,0,2));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,1,0));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,1,1));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,1,2));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,2,0));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,2,1));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,2,2));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,3,0));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,3,1));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,3,2));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,4,0));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,4,1));
    printf("%f ", MatrizEsparsa_le_valor(matriz3,4,2));

    // MATRIZ 3
    // 0.000000  0.000000  0.000000
    // 0.000000  12.000000 7.000000
    // 45.000000 0.000000  34.000000
    // 0.000000  43.000000 0.000000
    // 83.000000 0.000000  65.000000

    pMatrizEsparsa matriz4 = MatrizEsparsa_cria(3, 5);
    MatrizEsparsa_insere(matriz4, 0, 1, 54, REPLACE);
    MatrizEsparsa_insere(matriz4, 0, 2, 9, REPLACE);
    MatrizEsparsa_insere(matriz4, 0, 4, 22, REPLACE);
    MatrizEsparsa_insere(matriz4, 1, 1, 3, REPLACE);
    MatrizEsparsa_insere(matriz4, 1, 3, 233, REPLACE);
    MatrizEsparsa_insere(matriz4, 2, 2, 41, REPLACE);
    MatrizEsparsa_insere(matriz4, 2, 4, 1, REPLACE);

    printf("%f ", MatrizEsparsa_le_valor(matriz4,0,0));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,0,1));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,0,2));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,0,3));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,0,4));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,1,0));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,1,1));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,1,2));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,1,3));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,1,4));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,2,0));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,2,1));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,2,2));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,2,3));
    printf("%f ", MatrizEsparsa_le_valor(matriz4,2,4));

    pMatrizEsparsa mult2 = MatrizEsparsa_mult_por_matriz(matriz3,matriz4);

    MatrizEsparsa_destroi(matriz);
    MatrizEsparsa_destroi(matriz2);
    MatrizEsparsa_destroi(mult1);
    MatrizEsparsa_destroi(matriz3);
    MatrizEsparsa_destroi(matriz4);
    MatrizEsparsa_destroi(mult2);

    return 0;
}

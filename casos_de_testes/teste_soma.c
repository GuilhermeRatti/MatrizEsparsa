#include "MatrizEsparsa.h"
#include "ForwardList.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // TESTA TAMBEM AS FUNCOES MatrizEsparsa_cria, MatrizEsparsa_insere E MatrizEsparsa_le_valor
    pMatrizEsparsa matriz = MatrizEsparsa_cria(2, 2);
    MatrizEsparsa_insere(matriz, 0, 1, 1, REPLACE);
    MatrizEsparsa_insere(matriz, 0, 0, 1, REPLACE);

    printf("\nMATRIZ 1:\n");
    printf("%f ", MatrizEsparsa_le_valor(matriz, 0, 0));
    printf("%f\n", MatrizEsparsa_le_valor(matriz, 0, 1));
    printf("%f ", MatrizEsparsa_le_valor(matriz, 1, 0));
    printf("%f\n", MatrizEsparsa_le_valor(matriz, 1, 1));
    //MATRIZ 1
    // 1.000000 1.000000
    // 0.000000 0.000000
    
    pMatrizEsparsa matriz2 = MatrizEsparsa_cria(2, 2);

    MatrizEsparsa_insere(matriz2, 0, 1, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 0, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 1, 2, REPLACE);

    printf("\nMATRIZ 2:\n");
    printf("%f ", MatrizEsparsa_le_valor(matriz2, 0, 0));
    printf("%f\n", MatrizEsparsa_le_valor(matriz2, 0, 1));
    printf("%f ", MatrizEsparsa_le_valor(matriz2, 1, 0));
    printf("%f\n", MatrizEsparsa_le_valor(matriz2, 1, 1));
    //MATRIZ 2
    // 0.000000 2.000000
    // 2.000000 2.000000

    pMatrizEsparsa soma = MatrizEsparsa_soma(matriz, matriz2);

    printf("\nSOMA MATRIZ 1 + MATRIZ 2:\n");
    printf("%f ", MatrizEsparsa_le_valor(soma, 0, 0));
    printf("%f\n", MatrizEsparsa_le_valor(soma, 0, 1));
    printf("%f ", MatrizEsparsa_le_valor(soma, 1, 0));
    printf("%f\n", MatrizEsparsa_le_valor(soma, 1, 1));

    //RESULTADO ESPERADO
    // 1.000000 3.000000
    // 2.000000 2.000000

    MatrizEsparsa_destroi(matriz);
    MatrizEsparsa_destroi(matriz2);
    MatrizEsparsa_destroi(soma);

    return 0;
}

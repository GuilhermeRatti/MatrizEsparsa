#include "../matriz/MatrizEsparsa.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // TESTA TAMBEM AS FUNCOES MatrizEsparsa_cria, MatrizEsparsa_insere E MatrizEsparsa_le_valor
    pMatrizEsparsa matriz = MatrizEsparsa_cria(2, 2);
    MatrizEsparsa_insere(matriz, 0, 1, 1, REPLACE);
    MatrizEsparsa_insere(matriz, 0, 0, 1, REPLACE);
    
    printf("\nMATRIZ 1:\n");
    MatrizEsparsa_print_denso(matriz);

    //MATRIZ 1
    // 1.000000 1.000000
    // 0.000000 0.000000
    
    pMatrizEsparsa matriz2 = MatrizEsparsa_cria(2, 2);

    MatrizEsparsa_insere(matriz2, 0, 1, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 0, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 1, 2, REPLACE);

    printf("\nMATRIZ 2:\n");
    MatrizEsparsa_print_denso(matriz2);
    
    //MATRIZ 2
    // 0.000000 2.000000
    // 2.000000 2.000000

    printf("\n PRINT ESPARSO DA MATRIZ 2:\n");
    MatrizEsparsa_print_esparso(matriz2);
    
    //MATRIZ 2 ESPARSO
    // Linha 0: 2.000000
    // Linha 1: 2.000000 2.000000
    
    pMatrizEsparsa soma = MatrizEsparsa_soma(matriz, matriz2);

    printf("\nSOMA MATRIZ 1 + MATRIZ 2:\n");
    MatrizEsparsa_print_denso(soma);

    //RESULTADO ESPERADO
    // 1.000000 3.000000
    // 2.000000 2.000000
    
    printf("\n PRINT ESPARSO DA SOMA:\n");
    MatrizEsparsa_print_esparso(soma);
    
    //RESULTADO ESPERADO
    // Linha 0: 1.000000 3.000000
    // Linha 1: 2.000000 2.000000

    MatrizEsparsa_destroi(matriz);
    MatrizEsparsa_destroi(matriz2);
    MatrizEsparsa_destroi(soma);

    return 0;
}

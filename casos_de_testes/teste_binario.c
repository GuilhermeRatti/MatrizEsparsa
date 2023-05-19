#include <stdio.h>
#include <stdlib.h>
#include "../matriz/MatrizEsparsa.h"

int main(int argc, char const *argv[])
{
    pMatrizEsparsa mat = MatrizEsparsa_cria(10,10);

    int i,j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            MatrizEsparsa_insere(mat, i, j, i+j, REPLACE);
        }
    }
    MatrizEsparsa_escreve_binario(mat, "teste.bin");

    pMatrizEsparsa mat2 = MatrizEsparsa_le_binario("teste.bin");

    printf("MATRIZ ESCRITA\n");
    MatrizEsparsa_print_denso(mat);
    printf("\n\n");
    printf("MATRIZ LIDA\n");
    MatrizEsparsa_print_denso(mat2);

    // Resultado esperado
    /**
        0 1 2 3 4 5 6 7 8 9 
        1 2 3 4 5 6 7 8 9 10 
        2 3 4 5 6 7 8 9 10 11 
        3 4 5 6 7 8 9 10 11 12 
        4 5 6 7 8 9 10 11 12 13 
        5 6 7 8 9 10 11 12 13 14 
        6 7 8 9 10 11 12 13 14 15 
        7 8 9 10 11 12 13 14 15 16 
        8 9 10 11 12 13 14 15 16 17 
        9 10 11 12 13 14 15 16 17 18 


        0 1 2 3 4 5 6 7 8 9 
        1 2 3 4 5 6 7 8 9 10 
        2 3 4 5 6 7 8 9 10 11 
        3 4 5 6 7 8 9 10 11 12 
        4 5 6 7 8 9 10 11 12 13 
        5 6 7 8 9 10 11 12 13 14 
        6 7 8 9 10 11 12 13 14 15 
        7 8 9 10 11 12 13 14 15 16 
        8 9 10 11 12 13 14 15 16 17 
        9 10 11 12 13 14 15 16 17 18
    */

    MatrizEsparsa_destroi(mat);
    MatrizEsparsa_destroi(mat2);

    return 0;
}

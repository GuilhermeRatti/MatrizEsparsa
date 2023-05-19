#include <stdio.h>
#include <stdlib.h>
#include "../matriz/MatrizEsparsa.h"

int main(int argc, char const *argv[])
{
    pMatrizEsparsa mat = MatrizEsparsa_cria(10,10);

    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            MatrizEsparsa_insere(mat,i,j,i+j,REPLACE);
        }
    }

    pMatrizEsparsa slice1 = MatrizEsparsa_slice(mat,0,0,4,4);
    pMatrizEsparsa slice2 = MatrizEsparsa_slice(mat,5,5,9,9);
    pMatrizEsparsa slice3 = MatrizEsparsa_slice(mat,8,8,11,11);
    
    printf("MATRIZ ORIGINAL\n");
    MatrizEsparsa_print_denso(mat);
    /*
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

    printf("\n\nSLICE 1 (0,0) a (4,4)\n");
    MatrizEsparsa_print_denso(slice1);
    /*
        0 1 2 3 4 
        1 2 3 4 5 
        2 3 4 5 6 
        3 4 5 6 7 
        4 5 6 7 8 
    */

    printf("\n\nSLICE 2 (5,5) a (9,9) (\n");
    MatrizEsparsa_print_denso(slice2);
    /*
        10 11 12 13 14 
        11 12 13 14 15 
        12 13 14 15 16 
        13 14 15 16 17 
        14 15 16 17 18 
    */

    printf("\n\nSLICE 3 (overstepping out of matrix) (8,8) a (11,11)\n");
    MatrizEsparsa_print_denso(slice3);
    /*
        16 17 0 0 
        17 18 0 0 
        0  0  0 0 
        0  0  0 0 
    */


    MatrizEsparsa_destroi(mat);
    MatrizEsparsa_destroi(slice1);
    MatrizEsparsa_destroi(slice2);
    MatrizEsparsa_destroi(slice3);

    return 0;
}

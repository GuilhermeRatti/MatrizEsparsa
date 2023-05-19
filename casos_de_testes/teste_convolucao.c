#include <stdio.h>
#include <stdlib.h>
#include "../matriz/MatrizEsparsa.h"

int main(int argc, char const *argv[])
{
    pMatrizEsparsa mat = MatrizEsparsa_cria(10,10);
    
    MatrizEsparsa_insere(mat,0,0,1,REPLACE);
    MatrizEsparsa_insere(mat,2,2,2,REPLACE);
    MatrizEsparsa_insere(mat,2,3,2,REPLACE);
    MatrizEsparsa_insere(mat,7,7,7,REPLACE);

    MatrizEsparsa_print_denso(mat);
    printf("\n");
    /*
        1 0 0 0 0 0 0 0 0 0 
        0 0 0 0 0 0 0 0 0 0 
        0 0 2 2 0 0 0 0 0 0 
        0 0 0 0 0 0 0 0 0 0 
        0 0 0 0 0 0 0 0 0 0 
        0 0 0 0 0 0 0 0 0 0 
        0 0 0 0 0 0 0 0 0 0 
        0 0 0 0 0 0 0 7 0 0 
        0 0 0 0 0 0 0 0 0 0 
        0 0 0 0 0 0 0 0 0 0 
    */

    pMatrizEsparsa kernel = MatrizEsparsa_cria(3,3);
    

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            MatrizEsparsa_insere(kernel,i,j,1,REPLACE);
        }
    }
    MatrizEsparsa_print_denso(kernel);
    /*
        1 1 1 
        1 1 1 
        1 1 1 
    */

    printf("\n");
    pMatrizEsparsa convolucao = MatrizEsparsa_convolucao(mat,kernel);
    /*
        1 1 0 0 0 0 0 0 0 0 
        1 3 4 4 2 0 0 0 0 0 
        0 2 4 4 2 0 0 0 0 0 
        0 2 4 4 2 0 0 0 0 0 
        0 0 0 0 0 0 0 0 0 0 
        0 0 0 0 0 0 0 0 0 0 
        0 0 0 0 0 0 7 7 7 0 
        0 0 0 0 0 0 7 7 7 0 
        0 0 0 0 0 0 7 7 7 0 
        0 0 0 0 0 0 0 0 0 0 
    */

    MatrizEsparsa_print_denso(convolucao);

    MatrizEsparsa_destroi(mat);
    
    MatrizEsparsa_destroi(kernel);
    
    MatrizEsparsa_destroi(convolucao);

    return 0;
}
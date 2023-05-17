#include <stdio.h>
#include <stdlib.h>
#include "MatrizEsparsa.h"

int main(int argc, char const *argv[])
{
    pMatrizEsparsa mat = MatrizEsparsa_cria(10,10);
    
    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            MatrizEsparsa_insere(mat,i,j,i,REPLACE);
        }
    }

    MatrizEsparsa_print_denso(mat);

    pMatrizEsparsa kernel = MatrizEsparsa_cria(3,3);


    MatrizEsparsa_print_denso(kernel);

    pMatrizEsparsa convolucao = MatrizEsparsa_convolucao(mat,kernel);

    MatrizEsparsa_print_denso(convolucao);

    MatrizEsparsa_destroi(mat);
    MatrizEsparsa_destroi(kernel);
    MatrizEsparsa_destroi(convolucao);

    return 0;
}
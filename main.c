#include "MatrizEsparsa.h"
#include "ForwardList.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    MatrizEsparsa *matriz = MatrizEsparsa_cria(2, 2);
    MatrizEsparsa_insere(matriz, 0, 1, 1, REPLACE);
    MatrizEsparsa_insere(matriz, 0, 0, 1, REPLACE);
    
    MatrizEsparsa *matriz2 = MatrizEsparsa_cria(2, 2);

    MatrizEsparsa_insere(matriz2, 1, 0, 2, REPLACE);
    MatrizEsparsa_insere(matriz2, 1, 1, 2, REPLACE);

    MatrizEsparsa *soma = MatrizEsparsa_soma(matriz, matriz2);

    printf("%f\n", MatrizEsparsa_le_valor(soma, 0, 0));
    printf("%f\n", MatrizEsparsa_le_valor(soma, 0, 1));
    printf("%f\n", MatrizEsparsa_le_valor(soma, 1, 0));
    printf("%f\n", MatrizEsparsa_le_valor(soma, 1, 1));

    MatrizEsparsa_destroi(matriz);
    MatrizEsparsa_destroi(matriz2);
    MatrizEsparsa_destroi(soma);

    return 0;
}

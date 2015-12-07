#include "matriz.h"

int main () {
    matrizEsparsa *mat = criaMatrizEsparsa (2, 3);

    insereValor (mat, 1, 2, 1);
	printMatriz (mat);
    insereValor (mat, 1, 1, 3);
	printMatriz (mat);

	printf ("Soma da linha 1: %d\n", somaLinha (mat, 1));
	printf ("Soma da coluna 1: %d\n", somaColuna (mat, 1));

    apagaMatrizEsparsa (mat);
    return 0;
}

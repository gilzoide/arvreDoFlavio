#include "matriz.h"

int main () {
    matrizEsparsa *mat = criaMatrizEsparsa (2, 3);

    insereValor (mat, 1, 1, 1);

    apagaMatrizEsparsa (mat);
    return 0;
}

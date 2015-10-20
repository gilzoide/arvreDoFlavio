#include "abb.h"
#include <stdio.h>

int main () {
	arvore A;
	iniciaArvore (&A);

	insereABB (&A, 75);
	insereABB (&A, 19);
	insereABB (&A, 18);
	insereABB (&A, 77);
	insereABB (&A, 14);

	imprimeEmOrdem (&A);
	imprimePreOrdem (&A);
	imprimePosOrdem (&A);
	labelledBracketing (&A);

	removeABB (&A, 75);
	labelledBracketing (&A);

	return 0;
}

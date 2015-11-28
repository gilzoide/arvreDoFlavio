#include "eqPolonesa.h"
#include <stdio.h>


int main () {
	arvore A;
	iniciaArvore (&A);

	leEntrada (&A);
	imprimeRPN (&A);
	imprimeInfixa (&A);

	destroiArvore (&A);
	return 0;
}

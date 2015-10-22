#include "arvoreGenealogica.h"
#include <stdio.h>


void menu () {
	puts ("1 - Inserir elemento");
	puts ("2 - Remover elemento");
	puts ("3 - Buscar elemento");
	puts ("4 - Impressão Em Ordem");
	puts ("5 - Impressão Pré Ordem");
	puts ("6 - Impressão Pós Ordem");
	puts ("7 - Impressão Labelled Bracketing");
	puts ("0 - Sair");
	printf ("> ");
}


int main () {
	arvore A;
	iniciaArvore (&A);

	int opcao, valor;

	do {
		menu ();
		scanf ("%d", &opcao);
	} while (opcao != 0);

	destroiArvore (&A);
	return 0;
}

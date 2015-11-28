#include "abb.h"
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
		switch (opcao) {
			case 1:
				printf ("Digite o valor a ser inserido > ");
				scanf ("%d", &valor);
				if (insereABB (&A, valor)) {
					puts ("Valor inserido com sucesso");
				}
				else {
					puts ("Valor já existia na árvore");
				}
				break;

			case 2:
				printf ("Digite o valor a ser removido > ");
				scanf ("%d", &valor);
				if (removeABB (&A, valor)) {
					puts ("Valor removido com sucesso");
				}
				else {
					puts ("Valor não encontrado na árvore");
				}
				break;

			case 3:
				printf ("Digite o valor a ser buscado > ");
				scanf ("%d", &valor);
				if (buscaValor (&A, valor)) {
					puts ("Valor encontrado");
				}
				else {
					puts ("Valor não encontrado");
				}
				break;

			case 4:
				imprimeEmOrdem (&A);
				break;

			case 5:
				imprimePreOrdem (&A);
				break;

			case 6:
				imprimePosOrdem (&A);
				break;

			case 7:
				labelledBracketing (&A);
				break;
		}
		puts ("");
	} while (opcao != 0);

	destroiArvore (&A);
	return 0;
}

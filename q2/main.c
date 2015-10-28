#include "arvoreGenealogica.h"
#include <stdio.h>

void menu () {
	puts ("1 - Imprimir membros da família");
	puts ("2 - Imprimir antepassados");
	puts ("3 - Imprimir árvore usando Labelled Bracketing");
	puts ("4 - Calcular grau de parentesco");
	puts ("0 - Sair");
	printf ("> ");
}


int main () {
	arvore A;
	iniciaArvore (&A);

	// total de relações
	int n, i;
	scanf ("%d", &n);
	// lê cada relação
	char filho[MAX], pai[MAX], mae[MAX];
	for (i = 0; i < n; i++) {
		scanf ("%s %s %s", filho, pai, mae);
		adicionaParentesco (&A, filho, pai, mae);
	}

	int opcao;

	do {
		menu ();
		scanf ("%d", &opcao);

		switch (opcao) {
			case 1:
				imprimeMembros (&A, 1 + 2 * n);
				break;

			case 3:
				labelledBracketing (&A);
				break;
		}
	} while (opcao != 0);

	destroiArvore (&A);
	return 0;
}

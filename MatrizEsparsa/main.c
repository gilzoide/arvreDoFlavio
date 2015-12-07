#include "matriz.h"

void menu () {
	puts ("1 - Consultar valor");
	puts ("2 - Inserir valor");
	puts ("3 - Soma de linha");
	puts ("4 - Soma de coluna");
	puts ("5 - Imprimir matriz");
	puts ("6 - Calcular determinante");
	puts ("7 - Resolver sistema linear (usando Gauss-Seidel)");
	puts ("0 - Sair");
	printf ("> ");
}

int main () {
	int numLinhas, numColunas;
	printf ("Escolha o tamanho da matriz esparsa (MxN) > ");
	scanf ("%d %d", &numLinhas, &numColunas);
	
	if (numLinhas <= 0 || numColunas <= 0) {
		fprintf (stderr, "Matriz não pode ter dimensão menor que 1\n");
		return -1;
	}

    matrizEsparsa *mat = criaMatrizEsparsa (numLinhas, numColunas);

	int opcao, y, x, valor, ret;
	do {
		menu ();
		scanf ("%d", &opcao);

		switch (opcao) {
			case 1:
				printf ("Escolha a posição da matriz a ser consultada (MxN) > ");
				scanf ("%d %d", &y, &x);
				ret = consultaValor (mat, y, x);
				if (ret != ERRO) {
					printf ("Matriz[%d][%d] = %d\n", y, x, ret);
				}
				break;

			case 2:
				printf ("Escolha o valor a ser inserido > ");
				scanf ("%d", &valor);
				printf ("Escolha em que posição da matriz o valor será inserido (MxN) > ");
				scanf ("%d %d", &y, &x);
				insereValor (mat, y, x, valor);
				break;

			case 3:
				printf ("Escolha a linha a ser somada > ");
				scanf ("%d", &y);
				ret = somaLinha (mat, y);
				if (ret != ERRO) {
					printf ("Soma da linha %d = %d\n", y, ret);
				}
				break;

			case 4:
				printf ("Escolha a coluna a ser somada > ");
				scanf ("%d", &x);
				ret = somaColuna (mat, x);
				if (ret != ERRO) {
					printf ("Soma da coluna %d = %d\n", x, ret);
				}
				break;

			case 5:
				printMatriz (mat);
				break;

		}

		puts ("");
	} while (opcao != 0);

    apagaMatrizEsparsa (mat);
    return 0;
}

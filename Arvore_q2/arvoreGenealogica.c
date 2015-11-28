#include "arvoreGenealogica.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Função recursiva auxiliar a buscaValor
no *recBuscaFilho (no *N, char nome[]) {
	if (N == NULL) {
		return NULL;
	}
	else {
		// achou!
		if (strcmp (nome, N->valor) == 0) {
			return N;
		}
		else {
			// tenta achar pela esquerda
			no *aux = recBuscaFilho (N->esquerdo, nome);
			// ou até pela direita
			if (!aux) {
				aux = recBuscaFilho (N->direito, nome);
			}

			// e retorna o achado (ou NULL se não achou)
			return aux;
		}
	}
}
// Busca um Nome na árvore genealógica. Não tá no .h pois só é preciso aqui
// Retorna seu endereço se encontrado, NULL caso contrário
no *buscaFilho (arvore *A, char nome[]) {
	return recBuscaFilho (A->raiz, nome);
}


int adicionaParentesco (arvore *A, char filho[], char pai[], char mae[]) {
	if (A->raiz == NULL) {
		no *raiz = novoNo (filho);
		raiz->esquerdo = novoNo (pai);
		raiz->direito = novoNo (mae);
		A->raiz = raiz;
	}
	else {
		no *aux = buscaFilho (A, filho);
		// filho não encontrado, ou não folha
		if (aux == NULL || aux->esquerdo != NULL || aux->direito != NULL) {
			return 0;
		}
		else {
			aux->esquerdo = novoNo (pai);
			aux->direito = novoNo (mae);
		}
	}

	A->n = A->n + 1;
	return 1;
}

// Função recursiva auxiliar a labelledBracketing
// Note que labelledBracketing usa percurso Pré Ordem
void recLabelledBracketing (no *N) {
	if (N == NULL) {
		printf ("[]");
	}
	else {
		printf ("[%s ", N->valor);
		recLabelledBracketing (N->esquerdo);
		printf (" ");
		recLabelledBracketing (N->direito);
		printf ("]");
	}
}
void labelledBracketing (arvore *A) {
	recLabelledBracketing (A->raiz);
	puts ("");
}


void imprimeMembros (arvore *A) {
	// calloc usado pra inicializar posições como NULL, usado como condição
	// de parada
	// `n * 2 + 1` é o número de ponteiros necessários (incluindo os NULLs)
	int n = A->n * 2 + 1;
	no **fila = calloc (n, sizeof (no *));
	fila[0] = A->raiz;

	// i é o apontador pro no atual sendo visitado
	int i;
	// ultimoDaGeracao aponta qual nó é o último da geração atualmente sendo
	// impressa, importante pra saber quando pula linha
	int ultimoDaGeracao = 0;
	// finalDaFila aponta onde está o final da fila, pra podermos adicionar os
	// filhos esquerdo e direito do nó atual
	int finalDaFila = 0;
	for (i = 0; fila[i] != NULL && i < n; i++) {
		// enfilera filho esquerdo, se existir
		if (fila[i]->esquerdo != NULL) {
			finalDaFila++;
			fila[finalDaFila] = fila[i]->esquerdo;
		}
		// enfilera filho direito, se existir
		if (fila[i]->direito != NULL) {
			finalDaFila++;
			fila[finalDaFila] = fila[i]->direito;
		}

		printf ("%s ", fila[i]->valor);
		if (i == ultimoDaGeracao) {
			puts ("");
			ultimoDaGeracao = finalDaFila;
		}
	}

	free (fila);
}


/*void */
void imprimeAntepassados (arvore *A, char nome[]) {
	no *buscado = buscaFilho (A, nome);

	if (buscado != NULL) {
		int n = A->n * 2 + 1;
		no **fila = calloc (n, sizeof (no *));
		fila[0] = buscado;

		// i é o apontador pro no atual sendo visitado
		int i;
		// finalDaFila aponta onde está o final da fila, pra podermos adicionar os
		// filhos esquerdo e direito do nó atual
		int finalDaFila = 0;
		for (i = 0; fila[i] != NULL && i < n; i++) {
			// enfilera filho esquerdo, se existir
			if (fila[i]->esquerdo != NULL) {
				finalDaFila++;
				fila[finalDaFila] = fila[i]->esquerdo;
			}
			// enfilera filho direito, se existir
			if (fila[i]->direito != NULL) {
				finalDaFila++;
				fila[finalDaFila] = fila[i]->direito;
			}

			if (i != 0) {
				printf ("%s ", fila[i]->valor);
			}
		}

		free (fila);
	}
	else {
		printf ("\"%s\" não encontrado\n", nome);
	}
}


int recGrauParentesco (no *filho, no *antepassado) {
	// não achou!
	if (filho == NULL) {
		return -1;
	}
	// caso base: mesma pessoa (distância 0)
	else if (filho == antepassado) {
		return 0;
	}
	else {
		int ret = recGrauParentesco (filho->esquerdo, antepassado);
		if (ret >= 0) {
			return 1 + ret;
		}

		ret = recGrauParentesco (filho->direito, antepassado);
		if (ret >= 0) {
			return 1 + ret;
		}

		return -1;
	}
}
void grauParentesco (arvore *A, char filho[], char antepassado[]) {
	no *noFilho = buscaFilho (A, filho);
	if (noFilho == NULL) {
		printf ("\"%s\" não encontrado\n", filho);
	}

	no *noAntepassado = buscaFilho (A, antepassado);
	if (noAntepassado == NULL) {
		printf ("\"%s\" não encontrado\n", antepassado);
	}

	// ambos encontrados na árvore. Calculemos o grau de parentesco
	if (noFilho != NULL && noAntepassado != NULL) {
		int ret = recGrauParentesco (noFilho, noAntepassado);
		printf ("Entre %s e %s grau de parentesco %d\n", filho, antepassado,
				ret >= 0 ? ret : 0);
	}
}

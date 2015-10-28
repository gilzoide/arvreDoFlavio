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
			no *aux = recBuscaFilho (N->esquerdo, nome);
			if (!aux) {
				aux = recBuscaFilho (N->direito, nome);
			}

			return aux;
		}
	}
}
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

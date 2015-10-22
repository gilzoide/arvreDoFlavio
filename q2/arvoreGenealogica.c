#include "arvoreGenealogica.h"

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

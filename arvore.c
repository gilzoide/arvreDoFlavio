#include "arvore.h"
#include <stdlib.h>

void iniciaArvore (arvore *A) {
	A->raiz = NULL;
}


no *novoNo (int valor) {
	no *novo = malloc (sizeof (no *));
	if (novo == NULL) {
		return NULL;
	}

	// inicializa valores: não tem filhos
	novo->valor = valor;
	novo->esquerdo = NULL;
	novo->direito = NULL;

	return novo;
}


// Função auxiliar a destroiArvore. Destrói cada nó, liberando sua memória e
// de seus filhos recursivamente.
void destroiNo (no *N) {
	if (N != NULL) {
		destroiNo (N->esquerdo);
		destroiNo (N->direito);
		free (N);
	}
}


void destroiArvore (arvore *A) {
	destroiNo (A->raiz);
	// volta A pro estado inicial: não há nós
	iniciaArvore (A);
}

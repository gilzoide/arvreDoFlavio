#include "abb.h"
#include <stdio.h>
#include <stdlib.h>

// Função recursiva auxiliar a insereABB
int recInsereABB (no **N, int valor) {
	// se chegamos ao ponto onde não há nós ainda, adiciona valor lá
	if (*N == NULL) {
		*N = novoNo (valor);
		return 1;
	}
	else {
		// valor já existente: retorna 0
		if (valor == (*N)->valor) {
			return 0;
		}
		if (valor < (*N)->valor) {
			return recInsereABB (&(*N)->esquerdo, valor);
		}
		else {
			return recInsereABB (&(*N)->direito, valor);
		}
	}
}
int insereABB (arvore *A, int valor) {
	return recInsereABB (&A->raiz, valor);
}


// Função recursiva auxiliar a removeABB
int recRemoveABB (no **N, int valor) {
	if (*N != NULL) {
		// é o nó que queremos remover
		if (valor == (*N)->valor) {
			// nó a trocar com N: primeiro filho encontrado
			no **aTrocar = &(*N)->esquerdo;
			if (*aTrocar == NULL) {
				*aTrocar = (*N)->direito;
			}
			// se não tem filho, é folha: apague-o
			if (*aTrocar == NULL) {
				free (*N);
				*N = NULL;
				return 1;
			}
			else {
				(*N)->valor = (*aTrocar)->valor;
				(*aTrocar)->valor = valor;
				return recRemoveABB (aTrocar, valor);
			}
		}
		// não é esse. Procuraê
		else if (valor < (*N)->valor) {
			return recRemoveABB (&(*N)->esquerdo, valor);
		}
		else {
			return recRemoveABB (&(*N)->direito, valor);
		}
	}
	else {
		return 0;
	}
}
int removeABB (arvore *A, int valor) {
	return recRemoveABB (&A->raiz, valor);
}


// Função recursiva auxiliar a imprimeEmOrdem
void recImprimeEmOrdem (no *N) {
	if (N != NULL) {
		recImprimeEmOrdem (N->esquerdo);
		printf ("%d ", N->valor);
		recImprimeEmOrdem (N->direito);
	}
}
void imprimeEmOrdem (arvore *A) {
	recImprimeEmOrdem (A->raiz);
	puts ("");
}


// Função recursiva auxiliar a imprimePreOrdem
void recImprimePreOrdem (no *N) {
	if (N != NULL) {
		printf ("%d ", N->valor);
		recImprimePreOrdem (N->esquerdo);
		recImprimePreOrdem (N->direito);
	}
}
void imprimePreOrdem (arvore *A) {
	recImprimePreOrdem (A->raiz);
	puts ("");
}


// Função recursiva auxiliar a imprimePosOrdem
void recImprimePosOrdem (no *N) {
	if (N != NULL) {
		recImprimePosOrdem (N->esquerdo);
		recImprimePosOrdem (N->direito);
		printf ("%d ", N->valor);
	}
}
void imprimePosOrdem (arvore *A) {
	recImprimePosOrdem (A->raiz);
	puts ("");
}


// Função recursiva auxiliar a labelledBracketing
// Note que labelledBracketing usa percurso Pré Ordem
void recLabelledBracketing (no *N) {
	if (N == NULL) {
		printf ("[]");
	}
	else {
		printf ("[%d ", N->valor);
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


// Função recursiva auxiliar a buscaValor
int recBuscaValor (no *N, int valor) {
	if (N == NULL) {
		return 0;
	}
	else {
		// achou!
		if (valor == N->valor) {
			return 1;
		}
		else if (valor < N->valor) {
			return recBuscaValor (N->esquerdo, valor);
		}
		else {
			return recBuscaValor (N->direito, valor);
		}
	}
}
int buscaValor (arvore *A, int valor) {
	return recBuscaValor (A->raiz, valor);
}

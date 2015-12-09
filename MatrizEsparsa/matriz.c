#include "matriz.h"
#include <math.h>

matrizEsparsa *criaMatrizEsparsa (int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) {
        fprintf (stderr, "Erro: número de linhas e colunas deve ser positivo não nulo!\n");
        return NULL;
    }

    matrizEsparsa *mat = malloc (sizeof (matrizEsparsa));
    if (mat == NULL) {
        return NULL;
    }

    mat->numLinhas = linhas;
    mat->linhas = calloc (linhas, sizeof (celula *));
    if (mat->linhas == NULL) {
        free (mat);
        return NULL;
    }
    mat->numColunas = colunas;
    mat->colunas = calloc (colunas, sizeof (celula *));
    if (mat->colunas == NULL) {
        free (mat->linhas);
        free (mat);
        return NULL;
    }

    return mat;
}


int insereValor (matrizEsparsa *mat, int y, int x, double valor) {
    if (y < 0 || x < 0 || y >= mat->numLinhas || x >= mat->numColunas) {
        fprintf (stderr, "Erro na inserção: posição inválida\n");
        return ERRO;
    }

	// procura a célula na linha, até que não exista, ou até a célula exatamente depois
    celula **aux;
    for (aux = &mat->linhas[y]; *aux != NULL; aux = &(*aux)->proxLinha) {
        if ((*aux)->x == x) {
            (*aux)->valor = valor;
            return 1;
        }
        else if ((*aux)->x > x) {
			break;
        }
    }

	// já cria a célula nova
	celula *cel = malloc (sizeof (celula));
	if (cel == NULL) {
		return ERRO;
	}

	cel->y = y;
	cel->x = x;
	cel->valor = valor;


	// atualiza os ponteiros (linha)
	cel->proxLinha = *aux;
	*aux = cel;

	// procura a célula na coluna, até que não exista, ou até a célula exatamente depois
	for (aux = &mat->colunas[x]; *aux != NULL; aux = &(*aux)->proxColuna) {
		if ((*aux)->y > y) {
			break;
		}
	}

	// atualiza os ponteiros (coluna)
	cel->proxColuna = *aux;
	*aux = cel;
	return 1;
}


int somaLinha (matrizEsparsa *mat, int linha) {
	if (linha < 0 || linha >= mat->numLinhas) {
		fprintf (stderr, "Linha inválida\n");
		return ERRO;
	}

	// acumula valores das células na variável 'soma'
	int soma = 0;
	celula *aux;
	for (aux = mat->linhas[linha]; aux != NULL; aux = aux->proxLinha) {
		soma += aux->valor;
	}

	return soma;
}


int somaColuna (matrizEsparsa *mat, int coluna) {
	if (coluna < 0 || coluna >= mat->numColunas) {
		fprintf (stderr, "Coluna inválida\n");
		return ERRO;
	}

	// acumula valores das células na variável 'soma'
	int soma = 0;
	celula *aux;
	for (aux = mat->colunas[coluna]; aux != NULL; aux = aux->proxColuna) {
		soma += aux->valor;
	}

	return soma;
}


int consultaValor (matrizEsparsa *mat, int y, int x) {
	if (y < 0 || x < 0 || y >= mat->numLinhas || x >= mat->numColunas) {
		fprintf (stderr, "Posição inválida\n");
		return ERRO;
	}

	celula *aux;
	for (aux = mat->linhas[y]; aux != NULL; aux = aux->proxLinha) {
		// achou o número
		if (aux->x == x) {
			return aux->valor;
		}
	}

	// se por acaso não achou uma célula, é porque é zero
	return 0;
}


void printMatriz (matrizEsparsa *mat) {
	int i, j;
	for (i = 0; i < mat->numLinhas; i++) {
		j = 0;
		celula *aux = mat->linhas[i];
		// pra cada célula existente, escreve os zeros antes, e seu valor
		for (aux = mat->linhas[i]; aux != NULL; aux = aux->proxLinha) {
			// escreve os zeros anteriores ao X atual
			while (j < aux->x) {
				printf ("%6.3f ", 0.0);
				j++;
			}
			printf ("%6.3f ", aux->valor);
			j++;
		}
		// escreve o resto dos zeros
		while (j < mat->numColunas) {
			printf ("%6.3f ", 0.0);
			j++;
		}

		// pula linha, e partiu próxima
		puts ("");
	}
}


/// Função auxiliar à 'determinante'. Copia uma matriz
void copiaMatriz (matrizEsparsa *destino, matrizEsparsa *origem) {
	// percorre matriz original, inserindo na nova qualquer valor encontrado
	int i;
	celula *aux;
	for (i = 0; i < origem->numLinhas; i++) {
		for (aux = origem->linhas[i]; aux != NULL; aux = aux->proxLinha) {
			insereValor (destino, aux->y, aux->x, aux->valor);
		}
	}
}


double determinante (matrizEsparsa *matOriginal) {
	if (matOriginal->numLinhas != matOriginal->numColunas) {
		fprintf (stderr, "Matriz não é quadrada. Determinante não existe\n");
		return ERRO;
	}

	int tam = matOriginal->numLinhas;
	matrizEsparsa *mat = criaMatrizEsparsa (tam, tam);
	copiaMatriz (mat, matOriginal);

	int m = mat->numLinhas;
	int i, j, k, temp, count;
	double fator;
	for (i = 0; i < m - 1; i++) {
		if (consultaValor (mat, i, i) == 0) {
			for (k = i; k < m; k++) {
				if (consultaValor (mat, k, i) != 0) {
					for (j = 0; j < m; j++) {
						temp = consultaValor (mat, i, j);
						insereValor (mat, i, j, consultaValor (mat, k, j));
						insereValor (mat, k, j, temp);
					}
					k = m;
				}
			}
			count++;
		}

		if (consultaValor (mat, i, i) != 0) {
			for (k = i + 1; k < m; k++) {
				fator = -1.0 * consultaValor (mat, k, i) / consultaValor (mat, i, i);
				for (j = i; j < m; j++) {
					insereValor (mat, k, j, consultaValor (mat, k, j) +
							fator * consultaValor (mat, i, j));
				}
			}
		}
	}

	double det = 1;
	for (i = 0; i < m; i++) {
		det *= consultaValor (mat, i, i);
	}

	// libera memória da nossa matriz copiada
	apagaMatrizEsparsa (mat);

	if (count % 2 == 0 || det == 0) {
		return det;
	}
	else {
		return -det;
	}
}

// constantes necessárias: Número máximo de iterações, e precisão desejada (erro máximo permitido)
#define MAX_ITER 20
#define MAX_ERRO 0.001

int gaussSeidel (matrizEsparsa *matOriginal) {
	if (matOriginal->numLinhas != matOriginal->numColunas) {
		fprintf (stderr, "Matriz não é quadrada. Falows\n");
		return ERRO;
	}

	// cria nossa matriz auxiliar, com uma coluna a mais (matriz estendida)
	int tam = matOriginal->numLinhas;
	matrizEsparsa *mat = criaMatrizEsparsa (tam, tam + 1);
	copiaMatriz (mat, matOriginal);

	// vetor de entrada/saída, sistema a ser resolvido
	double vet[tam];
	int i;
	// lê os valores de entrada
	printf ("Digite os %d valores constantes > ", tam);
	for (i = 0; i < tam; i++) {
		scanf ("%lf", &vet[i]);
	}
	// coloca os valores na coluna extra da matriz
	for (i = 0; i < tam; i++) {
		insereValor (mat, i, tam, vet[i]);		
	}

	int r, j;
	float max, erro, soma, t;
	for (r = 1; r <= MAX_ITER; r++) {
		max = 0;
		for (i = 0; i < tam; i++) {
			soma = 0;
			for (j = 0; j < tam; j++) {
				if (j != i) {
					soma += consultaValor (mat, i, j) * vet[j];
				}
			}
			t = (consultaValor (mat, i, tam) - soma) / consultaValor (mat, i, i);
			erro = fabs (vet[i] - t);
			if (erro > max) {
				max = erro;
			}
			vet[i] = t;
		}
		// para de calcular quando precisão for alcançada
		if (max < MAX_ERRO) {
			break;
		}
	}

	printf ("Resultado: ");
	for (i = 0; i < tam; i++) {
		printf("%6.3lf ", vet[i]);
	}

	// libera memória da nossa matriz copiada
	apagaMatrizEsparsa (mat);

	return 0;
}


void apagaMatrizEsparsa (matrizEsparsa *mat) {
	// apaga as células todas
	int i;
	for (i = 0; i < mat->numLinhas; i++) {
		celula *aux, *proximo;
		for (aux = mat->linhas[i]; aux != NULL; aux = proximo) {
			proximo = aux->proxLinha;
			free (aux);
		}
	}
    free (mat->linhas);
    free (mat->colunas);
    free (mat);
}

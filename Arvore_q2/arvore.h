// Tamanho máximo dos nomes
#define MAX 100

// Nosso nó, com seu valor e nós filhos
struct no_t {
	char valor[MAX];
	struct no_t *esquerdo;
	struct no_t *direito;
};
typedef struct no_t no;

// A árvore: só precisamos saber do nó raiz, e quantas pessoas tem
typedef struct {
	no *raiz;
	int n;
} arvore;


// Inicializa árvore, certificando que não há nós (raiz = NULL)
void iniciaArvore (arvore *A);

// Cria um novo nó, alocando a memória necessária
// Por padrão, é nó folha (não tem filhos)
// ATENÇÃO: lembre de desalocar a memória!
no *novoNo (char valor[]);

// Libera a memória dos nós da árvore A
void destroiArvore (arvore *A);

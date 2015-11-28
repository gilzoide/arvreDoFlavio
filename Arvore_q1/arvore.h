// Nosso nó, com seu valor e nós filhos
struct no_t {
	int valor;
	struct no_t *esquerdo;
	struct no_t *direito;
};
typedef struct no_t no;

// A árvore: só precisamos saber do nó raiz
typedef struct {
	no *raiz;
} arvore;


// Inicializa árvore, certificando que não há nós (raiz = NULL)
void iniciaArvore (arvore *A);

// Cria um novo nó, alocando a memória necessária
// Por padrão, é nó folha (não tem filhos)
// ATENÇÃO: lembre de desalocar a memória!
no *novoNo (int valor);

// Libera a memória dos nós da árvore A
void destroiArvore (arvore *A);

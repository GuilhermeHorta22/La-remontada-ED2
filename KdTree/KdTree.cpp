


/*
	KdTree:
	Uma arvore k-dimensional, onde é muito utilizada para guardar coordenadas
	Cada nivel vai ser comparado com em ordem sendo primeiro X e depois o Y
	Então o descriminador vai indicar com qual dimensão vamos comparar
	Quando for 0=X e 1=Y
	Se caso o K=3 então vai ser (x,y,z) sendo 0=X 1=Y 2=Z
	
	no cria nó eu preciso fazer um for para copiar posição por posição do vetor
	for(i=0; i<K; i++)
		novo->ponto[i] = ponto[i];
*/

#define K 2

struct kdtree
{
	int ponto[K];
	struct kdtree *esq, *dir;
};
typedef struct kdtree KdTree;

//função que cria um novo nodo para arvore KdTree
KdTree *criaNo(int ponto[K])
{
	int i;
	KdTree *novo = (*KdTree)malloc(sizeof(KdTree));
	for(i=0; i<K; i++)
		novo->ponto[i] = ponto[i];
	novo->esq = novo->dir = NULL;
	return novo;
}

//função que insere as coordendss na KdTree RECURSIVO
void insereKdTree(Tree **raiz, int ponto[K], int n)
{
	int d;
	
	if(*raiz == NULL)
		*raiz = criaNo(ponto);
	else
	{
		d = n%K;
		if(ponto[d] < (*raiz)->ponto[d])
			insereKdTree(&(*raiz)->esq,ponto, n+1);
		else
			insereKdTree(&(*raiz)->dir,ponto,n+1);
	}
}

//função que insere as coordenadas na KdTree INTERATIVA
void insereKdTreeInt(Tree **raiz, int ponto[K], int n)
{
	Tree *atual, *ant;
	int d;
	if(*raiz == NULL)
		*raiz = criaNo(ponto);
	else
	{
		atual = *raiz;
		while(atual != NULL)
		{
			d = n%K;
			ant = atual;
			if(ponto[d] < atual->ponto[d])
				atual = atual->esq;
			else
				atual = atual->dir;
			n++; //incrementar para ter um novo discriminador
		}
		d = (n-1)%K; //para voltar na dimensão do ant e comparar
		if(ponto[d] < ant->ponto[d])
			ant->esq = criaNo(ponto);
		else
			ant->dir = criaNo(ponto);
	}
}

//função que ordena uma arvore KdTree
void ordena(int ponto[TF][K], int d, int ini, int fim)
{
	int i, j, tl = fim;
	int aux[K];
	
	while(tl > ini)
	{
		for(i=ini; i<tl; i++)
		{
			if(ponto[i][d] > ponto[i+1][d])
			{
				for(j=0; j<K; j++)
					aux[j] = ponto[i][j];
				for(j=0; j<K; j++)
					ponto[i][j] = ponto[i+1][j];
				for(j=0; j<K; j++)
					ponto[i+1][j] = aux[j];
			}
		}
		tl--;
	}
}

//função que insere ordenado na arvore KdTree
void insereKdTreeOrd(kdtree **raiz, int ponto[TF][K], int n, int ini, int fim)
{
	int d, meio;
	
	if(ini <= fim)
	{
		d = n%K;
		ordena(ponto,d,ini,fim);
		meio = (ini+fim)/2;
		*raiz = criaNo(ponto[meio]);
		insereKdTreeOrd(&(*raiz)->esq, ponto, n+1, ini, meio-1);
		insereKdTreeOrd(&(*raiz)->dir, ponto, n+1, meio+1, fim)
	}
}

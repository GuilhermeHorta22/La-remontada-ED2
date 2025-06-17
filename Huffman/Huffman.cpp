

/*
	Huffman:
	Arvore de decodifica��o, onde os simbolos mais frenquente possui os menores valores
	Andar para esquerda � 0
	Andar para direita � 1
*/

struct huffman
{
	int freq;
	char simbolo;
	struct huffman *esq, *dir;
};

struct listTree
{
	struct huffman *arv;
	struct	lisTree *prox;
};
typedef struct listTree ListTree;

//fun��o que cria um novo n� para armazenar as informa��es
huffman *criaNo(char simbolo, int freq)
{
	huffman *novo = (huffman*)malloc(sizeof(huffman));
	novo->freq = freq;
	novo->simbolo = simbolo;
	novo->esq = novo->dir = NULL;
	return novo;
}

//fun��o que conta a frenquencia de um simbolo da huffman
void contFreq(char *palavra, char simbolo, int *freq)
{
	int i=0, j;
	
	while(palavra[i] != '\0')
	{
		if(simbolo == palavra[i])
			(*freq)++;
		i++;
	}
}

//fun��o que cria uma lista ordenada baseada na frequencia um simbolo
void inserirListOrd(ListTree **list, huffman *no)
{
	ListTree *ant, *atual, *novo;
	
	novo = (ListTree*)malloc(sizeof(ListTree));
	novo->arv = no;
	novo->prox = NULL;
	
	if(*list == NULL || no->freq < (*list)->arv->freq) //inserir no cabe�a da lista
	{
		novo->prox = *list;
		*list = novo;
	}
	else //procurar posi��o para inserir
	{
		atual = *list;
		ant = atual;
		while(atual != NULL && novo->arv->freq >= atual->arv->freq)
		{
			ant = atual;
			atual = atual->prox;
		}
		novo->prox = atual;
		ant->prox = novo;
	}	
}

//fun��o que cria uma arvore huffman
void inserirHuffman(ListTree **lista, char simbolo, int freq)
{
    Huffman *novoNo = criaNo(simbolo, freq);
    inserirListOrd(lista, novoNo);
}

//fun��o que busca um simbolo e retorna seu codigo
void buscaCodigo(Huffman *raiz, char simbolo, char *codigo, int profundidade, int *encontrado)
{
    if(raiz != NULL && *encontrado == 0)
    {
        if(raiz->esq == NULL && raiz->dir == NULL && raiz->simbolo == simbolo)
        {
            codigo[profundidade] = '\0';
            printf("C�digo para %c: %s\n", simbolo, codigo);
            *encontrado = 1;
        }

        if(*encontrado == 0)
        {
            codigo[profundidade] = '0';
            buscaCodigo(raiz->esq, simbolo, codigo, profundidade + 1, encontrado);
        }
        if(*encontrado == 0)
        {
            codigo[profundidade] = '1';
            buscaCodigo(raiz->dir, simbolo, codigo, profundidade + 1, encontrado);
        }
    }
}




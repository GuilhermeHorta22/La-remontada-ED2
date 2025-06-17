

/*
	Huffman:
	Arvore de decodificação, onde os simbolos mais frenquente possui os menores valores
	Andar para esquerda é 0
	Andar para direita é 1
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

//função que cria um novo nó para armazenar as informações
huffman *criaNo(char simbolo, int freq)
{
	huffman *novo = (huffman*)malloc(sizeof(huffman));
	novo->freq = freq;
	novo->simbolo = simbolo;
	novo->esq = novo->dir = NULL;
	return novo;
}

//função que conta a frenquencia de um simbolo da huffman
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

//função que cria uma lista ordenada baseada na frequencia um simbolo
void inserirListOrd(ListTree **list, huffman *no)
{
	ListTree *ant, *atual, *novo;
	
	novo = (ListTree*)malloc(sizeof(ListTree));
	novo->arv = no;
	novo->prox = NULL;
	
	if(*list == NULL || no->freq < (*list)->arv->freq) //inserir no cabeça da lista
	{
		novo->prox = *list;
		*list = novo;
	}
	else //procurar posição para inserir
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

//função que cria uma arvore huffman
void inserirHuffman(ListTree **lista, char simbolo, int freq)
{
    Huffman *novoNo = criaNo(simbolo, freq);
    inserirListOrd(lista, novoNo);
}

//função que busca um simbolo e retorna seu codigo
void buscaCodigo(Huffman *raiz, char simbolo, char *codigo, int profundidade, int *encontrado)
{
    if(raiz != NULL && *encontrado == 0)
    {
        if(raiz->esq == NULL && raiz->dir == NULL && raiz->simbolo == simbolo)
        {
            codigo[profundidade] = '\0';
            printf("Código para %c: %s\n", simbolo, codigo);
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




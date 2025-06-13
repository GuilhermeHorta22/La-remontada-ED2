#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio2.h>

struct tree
{
	int info;
	struct tree *esq, *dir;
};
typedef struct tree Tree;

struct TpPilha
{
	Tree *info;
	struct TpPilha *prox;
};
typedef struct TpPilha Pilha;

void init(Pilha **p)
{
	*p = NULL;
}

char isEmpty(Pilha *p)
{
	return p == NULL;
}

Tree *top(Pilha *p)
{
	if(!isEmpty(p))
		return p->info;
	else
		return NULL;
}

void push(Pilha **p, Tree *info)
{
	Pilha *nova = (Pilha*)malloc(sizeof(Pilha));;
	nova->info = info;
	
	nova->prox = *p;
	*p = nova;
}

Tree *pop(Pilha **p)
{
	if(!isEmpty(*p))
	{
		Pilha *aux = *p;
		Tree *ret = aux->info;
		*p = aux->prox;
		free(aux);
		return ret;
	}
	return NULL;
}

void initTree(Tree **raiz)
{
	*raiz = NULL;
}

Tree *criaNo(int info)
{
	Tree *novo = (Tree*)malloc(sizeof(Tree));
	novo->info = info;
	novo->esq = novo->dir = NULL;
	return novo;
}

void insereTree(Tree **raiz, int info)
{
	
}

//travessia em pre ordem RECURSIVO
void pre_ordem(Tree *raiz)
{
	if(raiz != NULL)
	{
		printf("%d\t",raiz->info);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

//travessia em pre ordem INTERATIVO
void pre_ordemInt(Tree *raiz)
{
	Pilha *p;
	init(&p);
	push(&p,raiz);
	
	Tree *atual = NULL;
	
	while(!isEmpty(p))
	{
		atual = pop(&p);
		printf("%d\t",atual->info);
		
		if(raiz->dir != NULL)
			push(&p,atual->dir);
		if(raiz->esq != NULL)
			push(&p,atual->esq);
	}
}

//travessia em in ordem RECURSIVO
void in_ordem(Tree *raiz)
{
	if(raiz != NULL)
	{
		in_ordem(raiz->esq);
		printf("%d\t",raiz->info);
		in_ordem(raiz->dir);
	}
}

//travessia em in ordem INTERATIVO
void in_ordemInt(Tree *raiz)
{
	Pilha *p;
	init(&p);
	
	Tree *atual = raiz;
	while(!isEmpty(p) || atual != NULL)
	{
		while(atual != NULL)
		{
			push(&p,atual);
			atual = atual->esq;
		}
		
		atual = pop(&p);
		printf("%d\t",atual->info);
		
		atual = atual->dir;
	}
}

//travessia em pos ordem RECURSIVO
void pos_ordem(Tree *raiz)
{
	if(raiz != NULL)
	{
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("\n\t",raiz->info);
	}
}

//travessia em pos ordem INTERATIVO
void pos_ordemInt(Tree *raiz)
{
	Pilha *p1, *p2;
	init(&p1);
	init(&p2);
	push(&p1,raiz);
	
	Tree *atual = NULL;
	while(!isEmpty(p1))
	{
		atual = pop(&p1);
		push(&p2,atual);
		
		if(atual->esq != NULL)
			push(&p1,atual->esq);
		if(atual->dir != NULL)
			push(&p1,atual->dir);
	}
	while(!isEmpty(p2))
	{
		atual = pop(&p2);
		printf("%d\t",atual->info);
	}
}

//função que faz busca de um nodo INTERATIVO
Tree *buscaABB(Tree *raiz, int info)
{
	Tree *atual = raiz;
	
	while(atual != NULL)
	{
		if(info > atual->info)
			atual = atual->dir;
		else
		if(info < atual->info)
			atual = atual->esq;
		else
		if(atual->info == info)
			return atual;
	}
	return NULL;
}

//função que da free me todos os nodos de uma arvore RECURSIVO
void deletarABB(Tree **raiz)
{
	if(*raiz != NULL)
	{
		deletarABB(&(*raiz)->esq);
		deletarABB(&(*raiz)->dir);
		free(*raiz);
		*raiz = NULL;
	}
}

//função que da free em todos os nodos de uma arvore INTERATIVO
void deletarABBInt(Tree **raiz)
{
	Pilha *p1, *p2;
	init(&p1);
	init(&p2);
	push(&p1,*raiz);
	
	Tree *atual = NULL;
	
	while(!isEmpty(p1))
	{
		atual = pop(&p1);
		push(&p2,atual);
		if(atual->esq != NULL)
			push(&p1,atual->esq);
		if(atual->dir != NULL)
			push(&p1,atual->dir);
	}
	
	while(!isEmpty(p2))
	{
		atual = pop(&p2);
		free(atual);
	}
	*raiz = NULL;
}

//função que retorna o pai de um nodo da arvore INTERATIVO
Tree *paiNodo(Tree *raiz, int info)
{
	Tree *atual = raiz;
	
	if(raiz == NULL || atual->info == info)
		return NULL;
		
	while(atual != NULL)
	{
		if((atual->esq != NULL && atual->esq->info == info) || (atual->dir != NULL && atual->dir->info == info))
			return atual;
			
		if(info > atual->info)
			atual = atual->dir;	
		else
			atual = atual->esq;
	}
	return NULL;
}

//função que descobre a profundidade de um nodo na arvore INTERATIVO
int profundidade(Tree *raiz, int info)
{
	int cont=0;
	Tree *atual = raiz;
	
	while(atual != NULL)
	{
		if(info > atual->info)
			atual = atual->dir;
		else
		if(info < atual->info)
			atual = atual->esq;
		else
		if(atual->info == info)
			return cont;
		cont++;
	}
	return -1;
}

int main()
{
	Tree *raiz;
	initTree(&raiz);
}

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
		printf("\n%d",raiz->info);
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
		printf("\n%d",raiz->info);
		in_ordem(raiz->dir);
	}
}

//travessia em in ordem INTERATIVO
void in_ordemInt(Tree *raiz)
{
	
}

//travessia em pos ordem RECURSIVO
void pos_ordem(Tree *raiz)
{
	if(raiz != NULL)
	{
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("\n%d",raiz->info);
	}
}

//travessia em pos ordem INTERATIVO


int main()
{
	Tree *raiz;
	initTree(&raiz);
}

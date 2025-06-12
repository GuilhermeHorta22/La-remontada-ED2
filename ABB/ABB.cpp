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

#include<stdio.h>
#include<string.h>
#include<conio2.h>
#include<stdlib.h>

/* BALANCEAMENTO DE AVL 
	Para balancear uma AVL é feito na inserção do codigo, não tem como balancear uma AVL pos inserção.
	Na AVL balaceamos com base na altura de determinado nodo da arvore. Então vamos precisar implementar algumas
	funções para conseguir fazer uma inserção balanceada em uma AVL.
*/
struct tree
{
	int info;
	struct tree *esq, *dir;
};
typedef struct tree Tree;

//função que faz rotação a esquerda
void rotacao_esquerda(Tree **p)
{
	Tree *q, *temp;
	q = (*p)->dir;
	temp = q->esq;
	q->esq = *p;
	(*p)->dir = temp;
	*p = q;
}

//função que faz rotação a direita
void rotacao_direita(Tree **p)
{
	Tree *q, *temp;
	q = (*p)->esq;
	temp = q->dir;
	q->dir = *p;
	(*p)->esq = temp;
	*p = q;
}

//função que descobre a altura de um determinado nó da arvore (Modelo pre ordem)
int altura(Tree *raiz, int nivel, int maior)
{
	if(raiz != NULL)
	{
		if(nivel > maior)
			maior = nivel;
			
		altura(raiz->esq,nivel+1,maior);
		altura(raiz->dir,nivel+1,maior);
	}
	return maior;
}

int alturaAVL(Tree *raiz)
{
	int maior = 0;
	maior = altura(raiz,1,maior);
	return maior;	
}

//função que faz a inserção balanceada AVL
void insereAVL(Tree **raiz, int info, char *flag)
{
	int fb, fb_filho;
	
	if(*raiz == NULL)
	{
		*raiz = criaNo(info);
		*flag = 1; //indica que inseriu
	}
	else
	if(info < (*raiz)->info) //se caso tiver que inserir na esquerda
		insereAVL(&(*raiz)->esq,info);
	else //se caso tiver que inserir na direita
		insereAVL(&(*raiz)->dir,info)
		
	//calculo do fator de balanceamento do pai
	fb = alturaAVL((*raiz)->dir) - alturaAVL((*raiz)->esq);
	if(!*flag)
	{
		if(fb < -2 || fb > 2)
		{
			*flag = 0;
			if(fb == 2) //indica que é 
			{
				
			}
		}	
	}
	
}


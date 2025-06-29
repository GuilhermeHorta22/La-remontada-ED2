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

void insereABB(Tree **raiz, int info)
{
	Tree *aux, *ant;
	
	if(*raiz == NULL)
		*raiz = criaNo(info);
	else
	{
		aux = *raiz;
		
		while(aux != NULL)
		{
			ant = aux;
			if(info > aux->info)
				aux = aux->dir;
			if(info < aux->info)
				aux = aux->esq;
		}
		
		if(info > ant->info)
			ant->dir = criaNo(info);
		if(info < ant->info)
		else
			aux = aux->esq;
	}
	if(info > aux->info)
		ant->dir = criaNo(info);
	else
		ant->esq = criaNo(info);
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

//fun��o que faz busca de um nodo INTERATIVO
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

//fun��o para deletar um nodo informado na ABB INTERATIVO
int removerABB(Tree **raiz, int info)
{
    Tree *atual = *raiz;
    Tree *pai = NULL;

    //Localizar o nodo a ser removido
    while(atual != NULL && atual->info != info)
    {
        pai = atual;
        if(info < atual->info)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    //Caso n�o encontre
    if(atual == NULL)
    {
        printf("Nodo nao encontrado!\n");
        return -1;
    }

    //Continua apenas se encontrou
    if(atual != NULL)
    {
        //Caso 1: nodo folha
        if(atual->esq == NULL && atual->dir == NULL)
        {
            if(pai == NULL) // � raiz
                *raiz = NULL;
            else
            {
                if(pai->esq == atual)
                    pai->esq = NULL;
                else
                    pai->dir = NULL;
            }
            free(atual);
        }

        //Caso 2: nodo com 1 filho
        if((atual->esq == NULL && atual->dir != NULL) || (atual->esq != NULL && atual->dir == NULL))
        {
            Tree *filho;
            if(atual->esq != NULL)
                filho = atual->esq;
            else
                filho = atual->dir;

            if(pai == NULL) // � raiz
                *raiz = filho;
            else
            {
                if(pai->esq == atual)
                    pai->esq = filho;
                else
                    pai->dir = filho;
            }
            free(atual);
        }

        //Caso 3: nodo com 2 filhos
        if(atual->esq != NULL && atual->dir != NULL)
        {
            //Busca do sucessor (menor da sub�rvore direita)
            Tree *paiSucessor = atual;
            Tree *sucessor = atual->dir;

            while(sucessor->esq != NULL)
            {
                paiSucessor = sucessor;
                sucessor = sucessor->esq;
            }

            //Troca os dados
            atual->info = sucessor->info;

            //Ajusta os ponteiros para remover o sucessor
            if(paiSucessor->esq == sucessor)
            {
                if(sucessor->dir != NULL)
                    paiSucessor->esq = sucessor->dir;
                else
                    paiSucessor->esq = NULL;
            }
            else
            {
                if(sucessor->dir != NULL)
                    paiSucessor->dir = sucessor->dir;
                else
                    paiSucessor->dir = NULL;
            }
            free(sucessor);
            return 1;
        }
    }
}

//fun��o que da free me todos os nodos de uma arvore RECURSIVO
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

//fun��o que da free em todos os nodos de uma arvore INTERATIVO
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

//fun��o que retorna o pai de um nodo da arvore INTERATIVO
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

//fun��o que descobre a profundidade de um nodo na arvore INTERATIVO
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

//fun��o que conta a quantidade de no que tem em uma arvore (Estilo pr� ordem)
void quantNo(Tree *raiz, int *cont)
{
	Pilha *p;
	init(&p);
	push(&p,raiz);
	Tree *atual = NULL;
	
	while(!isEmpty(p))
	{
		atual = pop(&p);
		(*cont)++;
		
		if(atual->esq != NULL)
			push(&p,atual->esq);
		if(atual->dir != NULL)
			push(&p,atual->dir);
	}
}

//fun��o que descobre quem � o pai de um nodo e retorna por referencia
void buscaNo(Tree *raiz, int info, Tree **e, Tree **pai)
{
	*e = raiz;
	while(*e != NULL && (*e)->info != info)
	{
		*pai = *e;
		if(info < (*e)->info)
			*e = (*e)->esq;
		else
			*e = (*e)->dir;
		
	}
}

//fun��o que exclui um nodo para inserir novamente no balanceiamento
void exclusaoLado(Tree **raiz, Tree *e, Tree *pai, char lado)
{
	Tree *sub = NULL;
	Tree *subPai = NULL;
	int aux;
	
	if(e->esq == NULL && e->dir == NULL) // n�o tem filhos
	{
		if(e != pai) //caso se n�o for a raiz da arvore
		{
			if(e->info > pai->info)
				pai->dir = NULL;
			else
				pai->esq = NULL;
		}
		else //� a raiz da arvore
			*raiz = NULL;
		free(e);
	}
	else
	if(e->esq != NULL || e->dir != NULL) //apenas um filho
	{
		if(e != pai)
		{
			if(e->info > pai->info)
			{
				if(e->esq != NULL)
					pai->dir = e->esq;
				else
					pai->dir = e->dir;
			}
			else
			{
				if(e->esq != NULL)
					pai->esq = e->esq;
				else
					pai->esq = e->dir;
			}
		}
		else
		{
			if(e->esq != NULL)
				*raiz = e->esq;
			else
				*raiz = e->dir;
		}
		free(e);
	}
	else
	{
		if(lado == 'e')
		{
			sub = e->esq;
			subPai = e;
			while(sub->dir != NULL)
			{
				subPai = sub;
				sub = sub->dir;
			}
			aux = sub->info;
			exclusaoLado(&*raiz, sub, subPai, lado);
			e->info = aux;
		}
		else
		if(lado == 'd')
		{
			sub = e->dir;
			subPai = e;
			while(sub->esq != NULL)
			{
				subPai = sub;
				sub = sub->esq;
			}
			aux = sub->info;
			exclusaoLado(&*raiz, sub, subPai, lado);
			e->info = aux;
		}
		else
			printf("\nNao tem esse lado!!!\n");
	}
}

//fun��o que faz balanceamento na arvore ABB -> balanceia de acordo com a quantidade de nodo de um lado
void balanceiamentoABB(Tree **raiz)
{
	Tree *p, *e, *pai;
	int aux, fb, qEsq, qDir;
	Fila *f; //vamos usar uma fila para andar em nivel dentro da ABB
	initFila(&f);
	enqueue(&f,*raiz);
	
	while(!isEmpty(f))
	{
		dequeue(&f,&p);
		do
		{
			//vamos contar a quantidade de n� de cada lado para fazer o calculo e ver se est� desbalanceada
			qEsq = qDir = 0;
			quantNo(p->esq,&qEsq);
			quantNo(p->dir,&qDir);
			fb = qDir - qEsq;
			
			if(fb < -1 || fb > 1) //desbalanceado
			{
				aux = p->info;
				buscaNo(*raiz,p->info,&e,&pai);
				if(p->esq == NULL)
					p = p->dir;
				else
					p = p->esq;
				
				if(fb > 0)
					exclusaoLado(&*raiz,e,pai,'d');
				else
					exclusaoLado(&*raiz,e,pai,'e');
			}
		}while(fb < -1 || fb > 1);
		
		if(p->esq != NULL)
			enqueue(&f,p->esq);
		if(p->dir != NULL)
			enqueue(&f,p->dir);
	}
}

int main()
{
	Tree *raiz;
	initTree(&raiz);
	
	
}

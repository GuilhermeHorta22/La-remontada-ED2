#include<stdio.h>
#include<string.h>
#include<conio2.h>
#include<stdlib.h>

struct reg_lista
{
	struct listagen *cabeca;
	struct listagen *cauda;
};

union info_lista
{
	char info[8];
	struct reg_lista no;
};

struct listagen
{
	char terminal;
	union info_lista lista;
};
typedef struct listagen ListaGen;

struct TpPilha
{
	ListaGen *info;
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

ListaGen *top(Pilha *p)
{
	if(!isEmpty(p))
		return p->info;
	else
		return NULL;
}

void push(Pilha **p, ListaGen *info)
{
	Pilha *nova = (Pilha*)malloc(sizeof(Pilha));;
	nova->info = info;
	
	nova->prox = *p;
	*p = nova;
}

ListaGen *pop(Pilha **p)
{
	if(!isEmpty(*p))
	{
		Pilha *aux = *p;
		ListaGen *ret = aux->info;
		*p = aux->prox;
		free(aux);
		return ret;
	}
	return NULL;
}

//fun��o que cria uma caixinha de atomo
ListaGen *criaT(char *info)
{
	ListaGen *l = (ListaGen*)malloc(sizeof(ListaGen));
	l->terminal = 1; //indicando que � um atomo
	strcpy(l->lista.info,info);
	return l;
}

//fun��o que verifica se a caixinha atual n�o aponta para null
char nula(ListaGen *l)
{
	return l == NULL;
}

//fun��o que verifica se a caixinha atual � um atomo
char atomo(ListaGen *l)
{
	return !nula(l) && l->terminal == 1;
}

//fun��o que cria uma caixinha de lista
ListaGen *cons(ListaGen *H, ListaGen *T)
{
	if(atomo(T))
	{
		printf("\nA cauda nao pode ser um Atomo!\n");
		return NULL;
	}
	else
	{
		ListaGen *l = (ListaGen*)malloc(sizeof(ListaGen));
		l->terminal = 0;
		l->lista.no.cabeca = H;
		l->lista.no.cauda = T;
		return l;
	}
}

//fun��o que retorna quem � o proximo do cabe�a da lista
ListaGen *head(ListaGen *l)
{
	if(atomo(l) || nula(l))
	{
		printf("\nHEAD: Deve ser um argumento valido!");
		return NULL;
	}
	else
		return l->lista.no.cabeca;
}

//fun��o que retorna quem � o proximo da cauda da lista
ListaGen *tail(ListaGen *l)
{
	if(atomo(l) || nula(l))
	{
		printf("\nTAIL: Dever ser um argumento valido!");
		return NULL;
	}
	else
		return l->lista.no.cauda;
}

//fun��o que exibe a lista
void exibe(ListaGen *l)
{
	if(atomo(l))
		printf("%s",l->lista.info);
	else
	{
		printf("[");
		while(!nula(l))
		{
			exibe(head(l));
			l = tail(l);
			if(!nula(l))
				printf(",");
		}
		printf("]");
	}
}

//fun��o que destroi uma lista generalizada
void destruir(ListaGen **l)
{
	if(!nula(*l))
	{
		if(atomo(*l))
			free(*l);
		else
		{
			destruir(&(*l)->lista.no.cabeca);
			destruir(&(*l)->lista.no.cauda);
			free(*l);
			*l = NULL;
		}
	}
}

//fun��o que busca um atomo dentro de uma lista generealizada (INTERATIVO)
char buscaTeste(ListaGen *L, char *alvo)
{
	Pilha *p;
	init(&p);         // inicia a pilha
	push(&p, L);      // come�a empilhando a lista principal

	while(!isEmpty(p))
	{
		ListaGen *atual = top(p);
		atual = pop(&p);  // retira da pilha

		if(!nula(atual))
		{
			if(atomo(atual)) // � �tomo
			{
				if(strcmp(atual->lista.info, alvo) == 0)
					return 1;  // encontrado!
			}
			else // � lista: empilha cauda e cabe�a
			{
				push(&p, atual->lista.no.cauda);
				push(&p, atual->lista.no.cabeca);
			}
		}
	}

	return 0; // n�o achou
}

//fun��o que busca um atomo de maneira recursiva
ListaGen *buscaRecur(ListaGen *l, char *info)
{
	if(!nula(l))
	{
		if(atomo(l))
		{
			if(strcmp(l->lista.info,info) == 0)
				return l;
		}
		else
		{
			ListaGen *aux = buscaRecur(head(l),info);
			if(!nula(aux))
				return aux;
			
			aux = buscaRecur(tail(l),info);
			return aux;
		}
	}
	return NULL;
}

//fun��o que busca um atomo de maneira interativa
ListaGen *buscaInt(ListaGen *l, char *info)
{
	ListaGen *atual = NULL;
	Pilha *p;
	init(&p);
	push(&p,l);
	
	while(!isEmpty(p))
	{
		atual = pop(&p);
		if(!nula(atual))
		{
			if(atomo(atual)) //� um atomo
			{
				if(strcmp(atual->lista.info,info) == 0)
					return atual;
			}
			else
			{ //empilha a cauda antes para ficar na ordem dentro da pilha
				push(&p,atual->lista.no.cauda);
				push(&p,atual->lista.no.cabeca);
			}
		}
	}
	return NULL; //n�o achou
}

//fun��o para deletar um atomo desejado da lista generalizada
void excluirAtomo(ListaGen *l, char *info)
{
	Pilha *p;
	init(&p);
	push(&p, l);

	int flag = 0;
	ListaGen *atual = NULL;

	while(!isEmpty(p) && flag == 0)
	{
		atual = pop(&p);

		// Verifica cabe�a
		if(!nula(head(atual)) && atomo(head(atual)))
		{
			if(strcmp(head(atual)->lista.info, info) == 0)
			{
				free(head(atual));
				atual->lista.no.cabeca = NULL;
				flag = 1;
			}
		}

		// Continua a busca
		if(!nula(tail(atual)))
			push(&p,tail(atual));
		if(!nula(head(atual)))
			push(&p,head(atual));
	}
	if(flag == 1)
		printf("\nAtomo excluido com sucesso!");
	else
		printf("\nAtomo nao foi encontrado!");
}


/*
	1- Percorre a lista generalizada de forma iterativa com o aux�lio de uma pilha, explorando cada sublista.

	2- Para cada n� da lista que n�o for �tomo (ou seja, � uma sublista), a fun��o tenta medir a profundidade seguindo os n�s da cabe�a (head) at� chegar na profundidade desejada.
	
	3- Quando encontra uma sublista na profundidade desejada, ela:
	
		- Entra nessa sublista,
		
		- Vai caminhando pela cauda (tail) at� encontrar o final da lista (ou seja, um ponteiro NULL),
		
		- E ent�o insere o novo �tomo (colocando uma nova caixinha que aponta para o �tomo desejado).
*/

void inserirAtomoProfundidade(ListaGen *L, char *novo, int profundidade) 
{
    Pilha *p;
    init(&p);
    push(&p, L);

	int profAtual = 1;
    int inseriu = 0; // flag para controlar inser��o
    
    ListaGen *tmp = NULL;
    ListaGen *atual = NULL;
    ListaGen *sublista = NULL;

    while(!isEmpty(p) && inseriu != 1)
	{
        atual = pop(&p);

        if(!nula(atual) && !atomo(atual)) 
		{
            profAtual = 1;
            tmp = atual;

            // Contar profundidade
            while(!nula(tmp) && !atomo(tmp) && profAtual < profundidade) 
			{
                tmp = head(tmp);
                profAtual++;
            }

            // Se chegou na profundidade desejada
            if(profAtual == profundidade) 
			{
                sublista = atual;

                // Ir at� o fim da cauda
                while(!nula(sublista->lista.no.cauda))
                    sublista = sublista->lista.no.cauda;

                // Adiciona o novo �tomo
                sublista->lista.no.cauda = cons(criaT(novo), NULL);
                inseriu = 1; // Marca como inserido
            }

            // Continua percorrendo se n�o inseriu ainda
            if(inseriu == 0)
			{
                push(&p, atual->lista.no.cauda);
                push(&p, atual->lista.no.cabeca);
            }
        }
    }
}

//fun��o que duplica uma lista generealizada recursivamente
ListaGen *dup(ListaGen *l)
{
	if(nula(l))
		return NULL;
	if(atomo(l))
		return criaT(l->lista.info);
	return cons(dup(head(l)),dup(tail(l)));
}

int main()
{
	int achou; //[a,[b,[c]]]
	ListaGen *l = cons(criaT("a"),cons(cons(criaT("b"),cons(cons(criaT("c"),NULL),NULL)),NULL));
	exibe(l);
	
	printf("\n### BUSCA TESTE RETORNANDO INT ###\n");
	achou = buscaTeste(l,"c");
	if(achou == 1) //achou
		printf("\nAchou o elemento!!!\n");
	else
		printf("\nNao achou o elemento!!!\n");
	
	getch();
	
	printf("\n### EXCLUSAO DO ATOMO DESEJADO ###\n");
	excluirAtomo(l,"c");
	getch();
	
	printf("\n### BUSCA INTERATIVA RETORNANDO LISTAGEN ###\n");
	ListaGen *aux = NULL;
	aux = buscaInt(l,"c");
	if(aux != NULL) //achou
		printf("\nAchou o elemento!!!\n");
	else
		printf("\nNao achou o elemento!!!\n");
	
	getch();
	
	printf("\n### BUSCA RECURSIVA RETORNANDO LISTAGEN ###\n");
	aux = buscaRecur(l,"d");
	if(aux != NULL)
		printf("\nAchou o elemento!!!\n");
	else
		printf("\nNao achou o elemento!!!\n");
	
	printf("\n\n");
	l = cons(cons(criaT("a"),cons(criaT("b"),NULL)),cons(criaT("c"),NULL));
	exibe(l);
	
	destruir(&l);
	
	if(nula(l)) //se deu certo a fun��o de destruir a lista
		printf("\nA lista e nula!!!\n");
	else
		printf("\nA lista nao e nula!!!\n");
}

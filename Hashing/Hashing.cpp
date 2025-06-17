#include<stdio.h>
#include<conio2.h>
#include<string.h>
#include<stdlib.h>

#define TF 100
#define N 5

/*
	Hashing:
	Arvore de espalhamento, onde fazemos partição para diminuir o espaço de busca
	assim tornando as busca mais eficiente
*/

struct caixa
{
	int chave,  pos;
	struct caixa *prox;
};
typedef struct caixa Caixa;

struct tpreg
{
	int codigo;
	char nome[30];
	int idade;
	char status;
};
typedef struct tpreg TpReg;

//função que faz o calculo da onde vai inserir o registro
int hash(int chave)
{
	return chave % N;
}

//função que busca um registro dentro dos registros
void buscaLista(Caixa *inicio, int chave, Caixa **no)
{
	while(inicio != NULL && chave > inicio->chave)
		inicio = inicio->prox;
		
	if(inicio != NULL && chave == inicio->chave)
		*no = inicio;
	else
		*no = NULL;
}

void insere_lista(Caixa **inicio, int chave, int pos)
{
    //Criando a nova caixa
    Caixa *nc = (Caixa*)malloc(sizeof(Caixa));
    nc->chave = chave;
    nc->pos = pos;
    nc->prox = NULL;

    //Criando os ponteiros auxiliares
    Caixa *atual = NULL, *ant = NULL;

    // Se a lista está vazia, insere no início
    if(*inicio == NULL)
        *inicio = nc;
    else
    {
        atual = *inicio;
        ant = NULL;

        //Percorre enquanto a chave do novo for maior que a atual
        while(atual != NULL && nc->chave > atual->chave)
        {
            ant = atual;
            atual = atual->prox;
        }

        //Se ant for NULL, significa que deve inserir no início
        if(ant == NULL)
        {
            nc->prox = *inicio;
            *inicio = nc;
        }
        else
        {
            nc->prox = atual;
            ant->prox = nc;
        }
    }
}


// função que insere os dados dentro do arquivo
void insere(Caixa T[N], TpReg tabDados[TF], int *tl, TpReg reg)
{
	int ender;
	Caixa aux;
	
	ender = hash(reg.codigo);
	buscaLista(T[ender], reg.codigo, &aux);
	if(aux != NULL)
	{
		tabDados[*tl] = reg;
		insere_lista(&T[ender],reg.codigo,*tl);
		(*tl)++;
	}
	else
		printf("\nChave existente!");
}

//função que faz a exclusão logica de um registro
void exclusao_logica(Caixa T[N], TpReg tabDados[TF], int codigo)
{
	int ender;
	Caixa *aux;
	
	ender = hash(reg.codigo);
	busca_lista(T[ender],reg.codigo, &aux);
	if(aux != NULL)
	{
		if(tabDados[aux->pos].status == 1)
			tabDados[aux->pos].status = 0;
		else
			printf("\nJa esta excluido!!!");
	}
	else
		printf("\nA chave nao foi encontrada!");
}


//construindo arquivo para o espalhamento
void criarArquivoHash(char nomeArq[])
{
	FILE *arq = fopen(nomeArq,"rb");
	TpReg reg;
	int i;
	if(arq != NULL)
	{
		arq = fopen(nomeArq,"ab");
		reg.numero = 0;
		strcpy(reg.nome,"");
		reg.salario = 0.0;
		reg.status = 0;
		reg.elo = 0;
		for(i=0; i<N; i++)
			fwrite(&reg,sizeof(TpReg),1,arq);
	}
	fclose(arq);
}

void inserirHash(char nomeArq[], TpReg reg)
{
	int ender;
	TpReg regDad;
	FILE *arq = fopen(nomeArq,"rb+");
	
	ender = hash(reg.numero);
	fseek(arq,ender*sizeof(TpReg),0);
	fread(&regDad,sizeof(TpReg),1,arq);
	if(regDad.numero  == 0) //não existe colisão
	{
		fseek(arq,ender*sizeof(TpReg),0);
		fread(&reg,sizeof(TpReg),1,arq);
	}
	else //não existe colisão
	{
		
	}
	fclose(arq);
}

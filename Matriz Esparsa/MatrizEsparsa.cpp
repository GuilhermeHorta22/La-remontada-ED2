//resolução do exercicio 3 da prova de ED II
//fazer um separador de string e um codigo que a partir da string separada onde vai ser passado
//linha inicial e linha final para exclusão, assim como coluna inicial e coluna final


//para resolução vamos fazer a utilização de uma função que vai receber uma string inteira
//como no exemplo: "C2G3" ou "C20G33"
//e vai ser retornado linha inicial="C", linha final="G", coluna inicial=2, coluna final=3
//a partir disso procuramos as caixinhas dessa regiao e fazemos a exclusão no final
//o ideal é que vai guardando os endereços dela em uma pilha para no final da função excluir

void posicionaLinha(matEsp **lin, char *info)
{
	while(lin->linha != info)
		lin = lin->prox;
}

void posicionaColuna(matEsp **col, char info)
{
	while(col->coluna != info)
		col = col->prox;
}

//função que separa a string
//linha inteiro e coluna String
void separador(char *regiao, int *lini, int *linf, char *coli, char *colf)
{
	int i=0, j=0;
	char num1[10], num2[10];
	
	*coli = regiao[i++]; //guardando a letra da coluna inicial
	while(regiao[i] != '\0' && regiao[i] >= '0' && regiao[i] <= '9')
		num1[j++] = regiao[i++];
	num1[j] = '\0';
	*lini = atoi(num1); //guardando o numero da linha inicial
	
	j=0;
	*colf = regiao[i++]; //guardando a letra da coluna final
	while(regiao[i] != '\0' && regiao[i] >= '0' && regiao[i] <= '9')
		num2[j++] = regiao[i++];
	num2[j] = '\0';
	*linf = atoi(num2); //guardando o numero da linha final
}

//função que exclui determinada regiao de uma matriz esparsa
void excluirCampos(descritor desc, char *regiao)
{
	Pilha *p; //pilha que vai inserir os endereços para ser excluidos
	char *coli, *colf;
	int lini, linf;
	
	//não posso esquecer que é um descritor então vamos ter
	TpLinha *li, *lf;
	TpColuna *ci, *cf;
	
	separador(regiao,&lini,&linf,&coli,&colf);
	init(&p);
	
	//colocando as linhas inicial e final na coordenada passada
	li = desc.pLinha;
	posicionaLinha(&li,lini);
	lf = li;
	poscisionaLinha(&lf,linf);
		
	//colocando as colunas inicias e final na coordenada passada
	ci = desc.pColuna;
	posicionaColuna(&ci,coli);
	cf = ci;
	posicionaColuna(&cf,colf);
	
	while(li != lf->prox) //tem que ser o proximo de lf se nao não vai ir até lf
	{
		ant = aux =  li->primL;
		while(aux != NULL)
		{
			if(aux->coluna >= coli && aux->coluna <= colf)
			{
				push(&p,aux);
				if(ant == aux)
					li->primL = aux->pl;
				if(aux->coluna <= colf)
					ant = aux->pl;
			}
			ant = aux;
			aux = ant->pl;
		}
		li = li->prox;
	}
	
	while(ci != cf->prox)
	{
		ant = aux = ci->primC;
		while(aux != NULL)
		{
			if(aux->linha >= lini && aux->linha <= linf)
			{
				if(ant == aux)
					ci->primC = aux->pc;
				if(aux->linha <= linF)
					ant = aux->pc;
			}
			ant=aux;
			aux = aux->pc;
		}
		ci = ci->prox;
	}
	
	//exclusao dos endereços empilhados
	while(!isEmpty(p))
	{
		pop(&p,&aux);
		free(aux);
	}
}

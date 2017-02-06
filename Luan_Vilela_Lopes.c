/**************************************************
*
* Nome do(a) estudante: Luan Vilela Lopes
* Trabalho 1
* Professor(a): Diego
*
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NOME 50
#define MAX_CAPIVARAS 50
#define MAX_FAMILIA 50



/* Armazena informacoes de uma capivara */
typedef struct {
char nome[MAX_NOME+1];
int ultimo_peso; /* Ultimo peso registrado */
int var_total; /* Variacao total de peso */
int max_var_mensal; /* Maior variacao mensal encontrada */
char nascimento[11]; /* Data de nascimento */
} Capivara;
/* Armazena informacoes de uma familia de capivaras */
typedef struct {
char nome[MAX_NOME+1];
int num_capis; /* Quantidade de capivaras na familia */
int num_meses; /* Meses registrados */
Capivara capis[MAX_CAPIVARAS]; /* Armazena as capivaras */
} Familia;

// Criando a enumeração:
typedef enum {
    true = 1, false = 0
} bool;




void cadastraCapivara(int n, int i, Familia familia[MAX_FAMILIA]);
void cadastraPeso(int m, int id, int n, Familia familia[MAX_FAMILIA], int contMes);
void classificaCapivara(int id, int n, Familia familia[]);
void mes(int m);



int main(void){
	Familia familia[50]; 
	int f, i, k;


	//recebe o número de familias
	scanf("%d", &f);

	for(i = 0; i < f; i++){
		printf("\n");
		scanf("%s", familia[i].nome);
		setbuf(stdin, NULL);
		printf("\n");

		scanf("%d", &familia[i].num_capis);
		setbuf(stdin, NULL);

		familia[i].num_capis--;							// corrige entrada do usuário -1
		cadastraCapivara(familia[i].num_capis, i, familia);
		printf("\n");

		scanf("%d", &familia[i].num_meses);
		setbuf(stdin, NULL);
		printf("\n");
		familia[i].num_meses--;							//corrige entrada do usuário com -1
		cadastraPeso(familia[i].num_meses, i, familia[i].num_capis, familia, 1);

		classificaCapivara(i, familia[i].num_capis+1, familia);

		/* Imprime lista */
		//Familia Capitubbies - variacoes apos 2 meses
		printf("Familia %s - variacoes apos %d meses\n",familia[i].nome, familia[i].num_meses+1);
		for(k = 0; k < familia[i].num_capis+1; k++){
			if(familia[i].capis[k].max_var_mensal >= 0)
				printf("+%03d, %s\n", familia[i].capis[k].max_var_mensal, familia[i].capis[k].nome);
			else
				printf("%04d, %s\n", familia[i].capis[k].max_var_mensal, familia[i].capis[k].nome);

		}//fim for imprime

	}
}



void classificaCapivara(int id, int n, Familia familia[]){
	int i, j, min;
	Capivara aux;

  for (i = 0; i < (n-1); i++){
	min = i;
	for (j = (i+1); j < n; j++) {
		/* verifica qual variação total e maior*/
		if( abs(familia[id].capis[j].max_var_mensal) > abs(familia[id].capis[min].max_var_mensal) )
			min = j;
		/* se variaçao total for igual testa variacao  */
		if( abs(familia[id].capis[j].max_var_mensal) == abs(familia[id].capis[min].max_var_mensal) ){
			if( abs(familia[id].capis[j].var_total) > abs(familia[id].capis[min].var_total) )
				min = j;
			/* se variacao mesal for igual testa idade*/
			if( abs(familia[id].capis[j].var_total) == abs(familia[id].capis[min].var_total) ){
				int idade;
				bool gatilho = true;						//caso o ano, mês ou dia. seja maior fica false
				for(idade = 6; idade < 10; idade++)			//for ano
					if(familia[id].capis[j].nascimento[idade] > familia[id].capis[min].nascimento[idade]){
						min = j;
						gatilho = false;
					}
				//fim for ano
				for(idade = 3; idade < 5; idade++)			//for mês
					if(familia[id].capis[j].nascimento[idade] > familia[id].capis[min].nascimento[idade] && gatilho != false){
						min = j;
						gatilho = false;
					}
				//fim for mês
				for(idade = 0; idade < 2; idade++)			//for dia
					if(familia[id].capis[j].nascimento[idade] > familia[id].capis[min].nascimento[idade] && gatilho != false){
						min = j;
						gatilho = false;
					}
				//fim for dia
				/* Se a idade for igual gatinho = true */
				/* Então compara nome, em vez de usar a var idade que esta disponível. vou criar uma nova para facilitar leitura */
				int numChar = 0;
				while(numChar < MAX_NOME && gatilho == true){
					if(familia[id].capis[j].nome[numChar] < familia[id].capis[min].nome[numChar] && gatilho != false){
						min = j;
						gatilho = false;
					}
					numChar++;
				}
			}
		}

     }
     if (i != min) {
       aux = familia[id].capis[i];
       familia[id].capis[i] = familia[id].capis[min];
       familia[id].capis[min] = aux;
     }

  }

}




/* Função que recebe os dados das capivaras*/
//@m numero de meses registrados
//@id id da familia
//@n número de membros da família
//@familia struct
void cadastraPeso(int m, int id, int n,Familia familia[], int contMes){
	int k;
	bool chave = true;
	// imprime  meses
		mes(contMes++);
	/* Repete o mesmo mês até acabar os membros da família. */
	for(k = 0; k <= n; k++){
		char dados[MAX_NOME+12];
		char nome[MAX_NOME];
		memset(nome, 0, MAX_NOME);					// Zera valores da variável nome
		int i ,j, peso, multiplicador = 1;

		//recebe nome e data da capivara
		scanf("%[^\n]s", dados);
		setbuf(stdin, NULL);


		j = strlen(dados);
		//Escreve nome da capivara
		for(i = 0 ; i < strlen(dados); i++){
			if(dados[i] != ','){
				nome[i] = dados[i];
				peso = 0;
			}
			else
				break;				//sai do for quando achar a virgurla
		}//fim do for
		while(j--){
			if(dados[j] >= 48 && dados[j] <= 57){
				peso += multiplicador*((int)dados[j] - 48);
				multiplicador *=10;
			}
			else if(dados[j] == ',')	//sai do while caso ache uma virgula
				break;
		}

		printf("\n");
		/* gatilho, controla se foi encontrado o cadastro da capivara */
		chave = true;
		for(i = 0 ; i <= familia[id].num_capis; i++){
			if(strcmp(familia[id].capis[i].nome, nome) == 0 && chave){
				chave = false;
				int aux = peso - familia[id].capis[i].ultimo_peso;
				/* faz calculo da variacao do mes */
				if(familia[id].capis[i].ultimo_peso != 0)
					familia[id].capis[i].var_total = aux;
				/* Faz o calculo da variacao mensal total */
				if(familia[id].capis[i].var_total != 0)
					familia[id].capis[i].max_var_mensal += familia[id].capis[i].var_total;

				familia[id].capis[i].ultimo_peso = peso;		//salva ultimo peso digitado;
			}
		}
		/* Caso digite errado ou não exista o nome da capivara*/
		if(chave){
			printf("%s Nao existe nessa familia %s.\n", nome, familia[id].nome);
			cadastraPeso(m, id, n, familia, contMes);
		}

	}//fim do for k

	/* salta para o próximo mês */
	if(m > 0 && chave == false)
		cadastraPeso(m-1, id, n,familia, contMes);

}




/* Função que recebe os dados da família*/
//@n numero de capivaras que tem na família
//@id id da familia
//@familia struct
void cadastraCapivara(int n, int id, Familia familia[]){
	char dados[MAX_NOME+12];
	int i, j;
	//recebe nome e data da capivara
	scanf("%[^\n]s", dados);
	setbuf(stdin, NULL);
	//Escreve nome da capivara
	for(i = 0 ; i < strlen(dados); i++)
		if(dados[i] != ',')
			familia[id].capis[n].nome[i] = dados[i];
		else
			break;
	//fim for
	/* Escreve idade da Capivara*/
	i = strlen(dados)-1;
	j = 10;
	while(j--)
		familia[id].capis[n].nascimento[j] = dados[i--];

	//debug
	//printf("==========: %s, %s\n", familia[id].capis[n].nome, familia[id].capis[n].nascimento);
	//
	/* Recursão até acabar os membros da família */
	if(n > 0)
		cadastraCapivara(n-1, id, familia);
}



/* Função que informa mês*/
//retorna mes
void mes(int m){
	switch(m){
		case 1:
			printf("Fevereiro\n");
		break;
		case 2:
			printf("Marco\n");
		break;
		case 3:
			printf("Abril\n");
		break;
		case 4:
			printf("Maio\n");
		break;
		case 5:
			printf("Junho\n");
		break;
		case 6:
			printf("Julho\n");
		break;
		case 7:
			printf("Agosto\n");
		break;
		case 8:
			printf("Setembro\n");
		break;
		case 9:
			printf("Outubro\n");
		break;
		case 10:
			printf("Novembro\n");
		break;
		case 11:
			printf("Dezembro\n");
		break;
		default:
			printf("Janeiro\n");
	}
}
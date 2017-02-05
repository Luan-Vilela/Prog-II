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
void cadastraPeso(int m, int id, Familia familia[MAX_FAMILIA]);
void mes(int m);



int main(void){
	Familia familia[50];
	int f, i ;


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
		familia[i].num_meses--;							//corrige entrada do usuário com -1
		cadastraPeso(familia[i].num_meses, i, familia);
	}


	printf("%s\n", familia[f-1].nome);

}

/* Função que recebe os dados das capivaras*/
//@n numero de meses registrados
//@id id da familia
//@familia struct
void cadastraPeso(int m, int id, Familia familia[]){
	char dados[MAX_NOME+12];
	char nome[MAX_NOME];
	memset(nome, 0, MAX_NOME);					// Zera valores da variável nome
	int i, num, multiplicador = 1;
	mes(m);
	//recebe nome e data da capivara
	scanf("%[^\n]s", dados);
	setbuf(stdin, NULL);

	bool chave = true;
	//Escreve nome da capivara
	for(i = 0 ; i < strlen(dados); i++){
		if(dados[i] != ',' && chave){
			nome[i] = dados[i];
			num = 0;
		}
		else{
			chave = false;
			if(dados[i] >= 48 && dados[i] <= 57){
				num += (multiplicador * ((int)dados[i] - 48));
				multiplicador *= 10;
			}
		}
	}//fim do for
	printf("\n");
	chave = true;
	for(i = 0 ; i <= familia[id].num_capis; i++){
		if(strcmp(familia[id].capis[i].nome, nome) == 0 && chave){
			chave = false;
			printf("==========> Existe%s = %d\n", nome, num);

		}
	}
	if(chave){
		printf("%s Nao existe nessa na familia %s.\n", nome, familia[id].nome);
		cadastraPeso(m, id, familia);
	}

	if(m > 0 && chave == false)
		cadastraPeso(m-1, id, familia);
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
	printf("==========: %s, %s\n", familia[id].capis[n].nome, familia[id].capis[n].nascimento);

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
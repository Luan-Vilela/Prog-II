/**************************************************
*
* Luan Vilela Lopes
* Trabalho 2
* Professor(a): DIEGO PADILHA RUBERT
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes */
#define MAX_VEICULOS 5
#define NUM_PILHAS 3

/* Armazena informacoes de um veiculo estacionado em uma pilha */
typedef struct cel {
char placa[9];
struct cel *prox;
} veiculo;
/* Armazena informacoes de uma pilha */
typedef struct {
int veiculos; /* Quantidade de veiculos estacionados */
veiculo *topo; /* Topo da pilha */
} pilha;


int escolhePilha(pilha *estacionamento[NUM_PILHAS]);
void empilha(char placa[10], pilha *estacionamento[NUM_PILHAS]);
void mostraPilha(pilha *estacionamento, int n);


int main(){

	int n;
	char op[11];
	
	pilha *p[NUM_PILHAS];
	n = NUM_PILHAS;

	while(n--){
		p[n] = (pilha *) malloc(sizeof(pilha));
		p[n]->topo = NULL;
	}

	scanf("%d", &n);

	while(n--)
		do{
			scanf(" %[^\n]", op);

			 if (op[0] == 'E')
      			empilha(op, p);

      		if (op[0] == 'S')
      			printf("Funcao nao implementada ainda!\n");

      		if (op[0] == 'I')
      			mostraPilha(p[(op[3]-48)], op[3]-48 );
   
			
		}while(op[0] != 'F');
}




/*********************
	Mostra pilha individual 
	n é apenas um set pra printf P?
*/
void mostraPilha(pilha *estacionamento, int n){
	veiculo *p;
	printf("P%d:", n);
	for (p = estacionamento->topo; p != NULL; p = p->prox){
			printf("%s", p->placa);
			if(p->prox != NULL)
				printf(",");
	}
	printf("\n");

}

/* empilha em 1 das torres do estacionamento */
void empilha(char placa[10], pilha *estacionamento[NUM_PILHAS]){
	int i;
	char pl[9];
	// pilha *nova;
	 
	 veiculo *novoVeiculo;
	 novoVeiculo = (veiculo *) malloc(sizeof (veiculo));

	 /* separa a placa do veículo */
	 for(i = 2; i <= strlen(placa);i++)
	 	pl[i-2] = placa[i];
	
	/* Seleciona a pilha com menor carro. */
	int id_pilha = escolhePilha(estacionamento);

	/* Estaciona o carro caso tenha vaga. */
	if(estacionamento[id_pilha]->veiculos < 5){
		strcpy(novoVeiculo->placa,pl);
		novoVeiculo->prox = estacionamento[id_pilha]->topo;
		estacionamento[id_pilha]->topo = novoVeiculo;
		estacionamento[id_pilha]->veiculos++;
		printf("E %s\n", pl);
	}
	else
		printf("C %s\n", pl);
	//printf("pilha: %d - placa: %s / quant_Veic: %d\n", id_pilha, pl, estacionamento[id_pilha]->veiculos);

}


/* Escolho pilha com menor número de veículos */
int escolhePilha(pilha *estacionamento[NUM_PILHAS]){
	int i, k, j = 0;
	for(i = NUM_PILHAS-1; i >= 0;i--)
		for(k = i-1; k >= 0; k--){
			if(estacionamento[i]->veiculos < estacionamento[k]->veiculos)
				j = i;
			
		}

		//printf("%d\n", j);
		return j;
}
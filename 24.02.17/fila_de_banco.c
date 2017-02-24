#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct cel {
  int senha;
  time_t chegada;
  struct cel *prox;
} celula;


void enfileira_enc_C(celula *i, celula **f)
{
	static int senhaNum = 0; 
	celula *nova;
	nova = (celula *) malloc(sizeof (celula));
	nova->senha = senhaNum++;
	nova->chegada =  time(NULL);
	nova->prox = NULL;
	(*f)->prox = nova;
	*f = nova;
  
}


celula *desenfileira_enc_C(celula *i, celula **f)
{
	int x;
	celula *p;
	p = i->prox;
	if (p != NULL) {
	x = p->senha;
	i->prox = p->prox;

	if (i->prox == NULL)
		*f = i;
	}
	else
		printf("Fila vazia!\n");
/*
   diff_t = difftime(end_t, start_t);
*/
   	double temp = difftime(time(NULL), p->chegada); 
	//retorna senha e tempo
	printf("Tempo de espera de da senha %d: %lfs\n", x, temp);
	return p;
}



int main(void)
{
  celula *i, *f, *p;
  char op;
  
  i = f = (celula *) malloc(sizeof(celula));
  i->prox = NULL;

  do {
    scanf(" %c", &op);

    if (op == 'E')
      enfileira_enc_C(i, &f);
   
    if (op == 'S') {
      p = desenfileira_enc_C(i, &f);
      /*** Escrever a senha e calcular e escrever o tempo de espera ***/
      free(p);
    }
    
  } while(i->prox != NULL);

  return 0;
}

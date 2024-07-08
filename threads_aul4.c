#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

#define tam_t 5
pthread_t minhas_threads[tam_t];
int error = 1;
int sucesso = 0;


void Tarefa(char *nome)
{
	for(int ns=0;ns<10;ns++)
	{
		sleep(1);
		printf("Tarefa %s: passaram %d segundos do total de 10s\n", nome, ns+1);
	}

	if(isupper(nome[0]))
	{
		pthread_exit(&sucesso);
	}
	pthread_exit(&error);
	
}


int main(void)
{
	puts("Inicio\n");
	
	int *retorno[tam_t]; 
	char *param_t[tam_t] = {"Lucas", "maria", "Jose", "Gustavo", "anderson"};

	for(int i = 0; i < tam_t; i++)
	{
		pthread_create(&minhas_threads[i], NULL, (void *) Tarefa, (void *)param_t[i]);
	}
		
	for(int i = 0; i < tam_t; i++)
	{
		pthread_join(minhas_threads[i],	(void **)&retorno[i]);
		printf("Thread %s terminou com retorno %d\n", param_t[i], *retorno[i]);
	}

	puts("FIM\n");
return 0;
}

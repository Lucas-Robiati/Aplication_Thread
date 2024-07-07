#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t t1;
pthread_t t2;	
int ERRO_TH = 111;		// Codigo que indica erro na thread
int SUCESSO_TH = 222; 	// Codigo que indica sucesso na thread

void *codigo_tarefa_1(void){
	for( int ns=0; ns < 10; ++ns) {
		sleep(1);
		printf("Tarefa 1: passaram %d segundos\n", ns+1);
	}
	return( (void *) &SUCESSO_TH);
}

void codigo_tarefa_2(void){
	for( int ns=0; ns < 15; ++ns) {
		sleep(1);
		printf("Tarefa 2: passaram %d segundos\n", ns+1);
	}
	pthread_exit(&ERRO_TH); // nunca retornar variavel local
}


int main(void){
	int *retorno_t1;	// Codigo de termino da thread 1
	int *retorno_t2;	// Codigo de termino da thread 2
	
	printf("Inicio\n");

	pthread_create(&t1, NULL, (void *) codigo_tarefa_1, NULL);
	pthread_create(&t2, NULL, (void *) codigo_tarefa_2, NULL);

	pthread_join(t1, (void **) &retorno_t1);
	pthread_join(t2, (void **) &retorno_t2);

	printf("Fim: t1 retornou %d, t2 retornou %d\n", *retorno_t1, *retorno_t2);
	return(0);
}




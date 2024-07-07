#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define n_threads 10

pthread_t Minhas_threads[n_threads];

void Tarefa(int *nst)
{	
	for(int ns=0; ns < *nst; ns++)
	{
		sleep(1);
		printf("Passaram %d segundos do total de %d.\n", ns+1, *nst);
	}
}


int main(void)
{
	int param_thread[n_threads];
	
	printf("Inicio\n");
	
	for(int i = 0; i < n_threads; i++)
	{
		param_thread[i] = 5+i;
	}
	
	for(int i = 0; i < n_threads; i++)
	{
		pthread_create(&Minhas_threads[i], NULL, (void *) Tarefa, (void *) &param_thread[i]);
	}
	
	for(int i = 0; i < n_threads; i++)
	{
		pthread_join(Minhas_threads[i], NULL);
	}

puts("\nFim\n");
return 0;
}

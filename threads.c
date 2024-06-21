#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS 40 //quantas threads quero ter 
long compartilha = 0; //memoria compartilhada
pthread_mutex_t  mutex; // viabilizar os endereços das threads

void *threadfuc(void *arg)
{
  int a,b;
  for(long j=0;j < 100000; j++)
  {
    pthread_mutex_lock(&mutex);
    a = compartilha;
    b = 1;
    compartilha = a + b;
    pthread_mutex_unlock(&mutex);
  }
}

int main(int argc, char *argv[])
{
  pthread_t t[THREADS];
  int s;

  for(int i=0; i < THREADS; i++)
  {
    s = pthread_create(&t[i], NULL, &threadfuc, NULL); //criando todas as threads 
  }
  
  for(int i=0; i < THREADS; i++)
  {
    s = pthread_join(t[i], NULL); // esperando terminar
  }
  
  printf("compartilhada - %ld\n", compartilha);

return 0;
}


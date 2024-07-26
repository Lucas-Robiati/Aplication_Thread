#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

/*
 Quando se tem um problema onde duas threads alteram uma variavel goblal
 temos uma secao critica de codigo, compartilham uma variavel goblal compartilhada,
 sendo assim precisamos de uma exclusao mutua, desta forma usamos o mutex para proteger
 a variavel saldo.

 O mutex bloqueia a outra thread (obs: como se fosse um cadeado) de executar enquato o cadeado nao for aberto, sendo  assim
 as outras threads entram em uma lsita de espera o cadeado abrir para executar;

*/

pthread_t t1;
pthread_t t2; 
pthread_mutex_t mutex_saldo = PTHREAD_MUTEX_INITIALIZER;

double saldo = 10000.0;

void tarefa1(void)
{
  double saldo_velho, saldo_novo;
  sleep(1);
  
  for(int i=0; i < 100; i++)
  {
    pthread_mutex_lock(&mutex_saldo);
    
    saldo_velho = saldo;
    saldo_novo = saldo_velho - 10;

    printf("Saldo passou de %0.2f para o valor de %0.2f\n", saldo_velho, saldo_novo);
    saldo = saldo_novo;

    pthread_mutex_unlock(&mutex_saldo)  ;
  }
}

void tarefa2(void)
{
  double saldo_velho, saldo_novo;
  sleep(1);
  
  for(int i=0; i < 100; i++)
  {
    pthread_mutex_lock(&mutex_saldo);

    saldo_velho = saldo;
    saldo_novo = saldo_velho + 10;

    printf("Saldo passou de %0.2f para o valor de %0.2f\n", saldo_velho, saldo_novo);
    saldo = saldo_novo;
    
    pthread_mutex_unlock(&mutex_saldo);
  }
}

int main(int argc, char *argv[])
{
  printf("Saldo inicial %0.2f\n", saldo);
  

  pthread_create(&t1, NULL, (void *)tarefa1, NULL);
  pthread_create(&t2, NULL, (void *)tarefa2, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  
  printf("Saldo final %0.2f\n", saldo);

return 0;
}

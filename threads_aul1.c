#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

struct param_t
{
  int sec; // segundos totais
  char *nome; //nome da thread
};

pthread_t t1;
pthread_t t2;

void fuc_1(struct param_t *pparam)
{
  for(int ns=0; ns < pparam->sec; ++ns)
  {
    sleep(1);
    printf("%s: passaram %d segundos\n", pparam->nome, ns+1);
  }
}

void fuc_2(int *nst)
{
  for(int ns=0; ns < *nst; ns++)
  {
    sleep(1);
    printf("Tarefa 2: passaram %d segundos\n", ns+1);
  }
}

int main(void)
{
  struct param_t param1;
  int param2;

  param1.sec = 5;
  param1.nome = "TAREFA 1";

  param2 = 15;

  printf("Inicio\n");

  pthread_create(&t1,NULL, (void *) fuc_1, (void *)&param1);
  pthread_create(&t2,NULL, (void *) fuc_2, (void *)&param2);

  pthread_join(t1, NULL);
  pthread_join(t2,NULL);

return 0;
}

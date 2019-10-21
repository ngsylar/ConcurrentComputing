// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: L5111.c
// atividade: 1.1.1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static const int n_escritores = 3;
static const int n_leitores = 10;
static char banco_dados[10000];
static int index = 0;
static int contador = 0;

pthread_mutex_t escrita;
pthread_mutex_t leitura;

void* lendo (void* id) {
  long int tid = (long int)id;

  while (1) {
    pthread_mutex_lock(&leitura);
    contador++;                       // leitor entra na sala de leitura
    if (contador == 1)                // se for primeiro leitor na sala
      pthread_mutex_lock(&escrita);   // obtem acesso ao manuscrito
    pthread_mutex_unlock(&leitura);

    printf("(%d leitores) Leitor %ld leu:\n%s\n\n", contador, tid, banco_dados);

    pthread_mutex_lock(&leitura);
    if (contador == 1)                // se for ultimo leitor na sala
      pthread_mutex_unlock(&escrita); // libera manuscrito para os escritores
    contador--;                       // sai da sala de leitura
    pthread_mutex_unlock(&leitura);
    sleep(rand()%3);
  }
}

void* escrevendo (void* id) {
  long int tid = (long int)id;

  for (int i=0; i < 1000; i++) {
    pthread_mutex_lock(&escrita);
    printf("Escritor %ld escreveu na posicao %d \n\n", tid, index);
    banco_dados[index] = tid+'0';
    banco_dados[++index] = '\0';
    pthread_mutex_unlock(&escrita);
    sleep(rand()%2);
  }
}

int main () {
  pthread_t escritor[n_escritores];
  pthread_t leitor[n_leitores];

  banco_dados[index] = 'A';
  banco_dados[++index] = '\0';

  pthread_mutex_init(&escrita, 0);
  pthread_mutex_init(&leitura, 0);

  for (long int i=0; i < n_escritores; i++)
    pthread_create(&escritor[i], NULL, escrevendo, (void*)i+1);
  for (long int i=0; i < n_leitores; i++)
    pthread_create(&leitor[i], NULL, lendo, (void*)i+1);

  for (int i=0; i < n_escritores; i++)
    pthread_join(escritor[i], NULL);
  for (int i=0; i < n_leitores; i++)
    pthread_join(leitor[i], NULL);

  pthread_mutex_destroy(&escrita);
  pthread_mutex_destroy(&leitura);

  printf("%s\n", banco_dados);

  return 0;
}

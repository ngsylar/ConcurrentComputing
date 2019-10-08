// autor: Gabriel Sylar
// arquivo: 311.c
// atividade: 3.1.1

#include <stdio.h>
#include <pthread.h>

volatile int contador = 0;

void* incrementos () {
  for (int i = 0; i < 100; i++) {
    __sync_fetch_and_add (&contador, 1);
  }
  pthread_exit(NULL);
}

int main () {
  pthread_t thread[10];

  for (int i = 0; i < 10; i++)
    pthread_create(&thread[i], NULL, incrementos, NULL);
  for (int i = 0; i < 10; i++)
    pthread_join(thread[i], NULL);

  printf("%d\n", contador);
  return 0;
}
/* executar no terminal com o comando: for i in {1..1000}; do ./play; done */

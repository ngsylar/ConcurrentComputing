// autor: Gabriel Sylar
// arquivo: 111.c
// atividade: 1.1.1

#include <stdio.h>
#include <pthread.h>

int contador = 0;

void* incrementos () {
  for (int i = 0; i < 100; i++)
    contador++;
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

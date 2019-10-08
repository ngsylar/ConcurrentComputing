// autor: Gabriel Sylar
// arquivo: 211.c
// atividade: 2.1.1

#include <stdio.h>
#include <pthread.h>

static int contabancaria = 0;
static int turn = 0;

void* retirada () {
  while (1)
    if ((turn == 1) && (contabancaria >= 10)) {
      contabancaria = contabancaria - 10;
      printf("Retirada. Valor: %d\n", contabancaria);
      turn = 0;
    }
}

void* deposito () {
  while (1)
    if (turn == 0) {
      contabancaria = contabancaria + 20;
      printf("Deposito. Valor: %d\n", contabancaria);
      turn = 1;
    }
}

int main () {
  const int tam = 2;
  pthread_t thread[tam];

  pthread_create(&thread[0], NULL, deposito, NULL);
  pthread_create(&thread[1], NULL, retirada, NULL);
  for (int i = 0; i < tam; i++)
    pthread_join(thread[i], NULL);

  return 0;
}

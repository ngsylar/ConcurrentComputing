// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: L5211.c
// atividade: 2.1.1

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_mutexattr_t attr;

void bar() {
  printf("Tentando pegar o lock de novo.\n");
  pthread_mutex_lock(&mutex);
  printf("Estou com duplo acesso?\n");
  pthread_mutex_unlock(&mutex);
}

void *foo(void *empty) {
  pthread_mutex_lock(&mutex);
  printf("Acesso a região crı́tica.\n");
  bar();
  pthread_mutex_unlock(&mutex);
}

int main() {
  pthread_t t;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&mutex, &attr);
  pthread_create(&t, NULL, foo, NULL);
  pthread_join(t, NULL);
  pthread_mutex_destroy(&mutex);
  return 0;
}

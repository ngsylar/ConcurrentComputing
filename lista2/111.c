// autores: Nalu e Sylar
// arquivo: 111.c
// atividade: 1.1.1

#include <stdio.h>
#include <pthread.h>

void *rotina()
{
printf("Olá, sou uma thread\n");
}
int main()
{
pthread_t t, v;
pthread_create(&t, NULL, rotina, NULL);
pthread_create(&v, NULL, rotina, NULL);
printf("Olá, sou a main\n");
return 0;
}

// autores: Nalu e Sylar
// arquivo: 412.c
// atividade: 4.1.2

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int largada = 3;

void* carro (void* id) {

	while (largada);
	printf("Sou o carro %ld e terminei a corrida.\n", (long int)id);
	pthread_exit(NULL);
}

void* juizdelargada () {
	while (largada) {
		printf("%d\n", largada);
		// sleep(rand() % 10);
		sleep(1);
		largada--;
	}
	printf("GO!\n");
	pthread_exit(NULL);
}

int main () {
	pthread_t c[10], juiz;

	for (long int i = 0; i < 10; i++) {
		pthread_create(&c[i], NULL, carro, (void*)i);
	}

	pthread_create(&juiz, NULL, juizdelargada, NULL);
	pthread_join(juiz, NULL);

	for (int i = 0; i < 10; i++) {
		pthread_join(c[i], NULL);
	}

	return 0;
}

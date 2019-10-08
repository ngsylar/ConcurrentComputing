// autores: Nalu e Sylar
// arquivo: 311.c
// atividade: 3.1.1

#include <stdio.h>
#include <pthread.h>

void *contador(void *id){
	int i;
	long int tid = (long int )id;

	for (i=0; i<5;i++)
		printf("Sou a thread %ld e estou no número %d.\n", tid, i);
}

int main(){
  const int NUMTHREADS = 10;
	pthread_t threads[NUMTHREADS];

	for (long int i = 0; i < 10; i++) {
		pthread_create(&threads[i], NULL, contador, (void *) i);
	}
	for (long int i = 0; i < NUMTHREADS; i++)
    pthread_join(threads[i], NULL);

	return 0;
}

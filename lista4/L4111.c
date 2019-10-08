// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: L4111.c
// atividade: 1.1.1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t possedalista;
long int listadechamada[99];
int contador = 0;

void *aluno (void *id) {
    long int tid = (long int)id;

    pthread_mutex_lock(&possedalista);
    contador++;
    listadechamada[ contador-1 ] = tid;
    sleep(1);
    printf("Aluno %ld assinou a lista.\n", tid);
    pthread_mutex_unlock(&possedalista);
}

int main() {
    int n;
    do {
        printf("Numero de alunos: ");
        scanf("%d", &n);
    } while ((n<=1) || (n>=100));

    pthread_t t[n];
    pthread_mutex_init (&possedalista, 0);

    for (long int i=1; i<=n; i++) {
        pthread_create(&t[i-1], NULL, aluno, (void*)i);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(t[i], NULL);
    }
    pthread_mutex_destroy(&possedalista);

    printf("A ordem de assinatura da lista foi: ");
    for (int i=0; i<contador; i++) {
        printf("%ld ",listadechamada[i]);
    } printf("\n");

    return 0;
}

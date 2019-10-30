// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: L6211.c
// atividade: 2.1.1

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define ESQUERDO (id+4)%N   // pega garfo do lado esquerdo
#define DIREITO (id+1)%N    // pega garfo do lado direito

#define PENSANDO 0
#define COM_FOME 1
#define COMENDO 2
int estado[N];

pthread_mutex_t acessar_estado;
sem_t empanturrado[N];

void comer_ou_nao_comer_eis_a_questao (long int id) {
    if ((estado[id] == COM_FOME) && (estado[ESQUERDO] != COMENDO) && (estado[DIREITO] != COMENDO)) {
        printf("Filosofo %ld pegou os garfos %ld e %ld\n", id, ESQUERDO, DIREITO);
        estado[id] = COMENDO;
        printf("Filosofo %ld esta comendo\n\n", id);
        sleep(2);
        sem_post(&empanturrado[id]);    // se comeu solta os garfos
    }
}

void soltarGarfo (long int id) {
    pthread_mutex_lock(&acessar_estado);

    printf("Filosofo %ld soltou os garfos %ld e %ld\n", id, ESQUERDO, DIREITO);
    estado[id] = PENSANDO;
    printf("Filosofo %ld esta pensando\n\n", id);

    // se havia filosofos esperando com fome, entao libera garfos pra eles comerem
    comer_ou_nao_comer_eis_a_questao(ESQUERDO);
    comer_ou_nao_comer_eis_a_questao(DIREITO);

    pthread_mutex_unlock(&acessar_estado);
}

void pegarGarfo (long int id) {
    pthread_mutex_lock(&acessar_estado);

    estado[id] = COM_FOME;
    printf("Filosofo %ld esta com fome\n\n", id);
    comer_ou_nao_comer_eis_a_questao(id);

    pthread_mutex_unlock(&acessar_estado);
    sem_wait(&empanturrado[id]);    // se nao comeu, fica esperando
}

void* filosofo (void* n_filosofo) {
    long int id = (long int)n_filosofo;

    while (1) {
        sleep(1);
        pegarGarfo(id);
        sleep(1);
        soltarGarfo(id);
    }
}

int main () {
    pthread_t thread[N];

    pthread_mutex_init(&acessar_estado, NULL);
    for (long int i=0; i < N; i++)
        sem_init(&empanturrado[i], 0, 0);

    for (long int i=0; i < N; i++) {
        pthread_create(&thread[i], NULL, filosofo, (void*)i);
        printf("Filosofo %ld esta pensando\n\n", i);
    }
    for (long int i=0; i < N; i++)
        pthread_join(thread[i], NULL);

    pthread_mutex_destroy(&acessar_estado);
    for (long int i=0; i < N; i++)
        sem_destroy(&empanturrado[i]);

    return 0;
}

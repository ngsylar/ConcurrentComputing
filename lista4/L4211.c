// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: L4211.c
// atividade: 2.1.1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

static const int num_turistas = 90;         // numero de turistas visitanto o museu
static const int cap_sala[3] = {10,6,18};   // capacidade de pessoas que cada sala comporta
sem_t sala[3];    // semaforo da sala
sem_t guia;       // semaforo do guia

static int guia_cont[3] = {0,0,0};    // contador de pessoas que entraram em cada sala
// static int cont_geral = 90;           // contador geral de pessoas que sairam do museu (passando pela ultima sala)

void *turista (void* id) {
    long int tid = (long int)id;
    int val;

    // o turista tenta entrar em cada sala (na ordem 1, 2, 3)
    for (int i=0; i<3; i++) {
        sem_wait(&sala[i]);   // se sala nao estiver cheia, turista entra

        sem_wait(&guia);      // guia esta na entrada da sala atual recebendo um turista por vez
        guia_cont[i]++;       // este recurso eh acessado um turista por vez, incrementa uma pessoa a sala atual
        // printf("%ld entrou em %d\n", tid+1, i+1);

        // if (i==3)             // se a sala atual for a ultima, entao
        //     cont_geral--;     // numero de pessoas que estao esperando para visitar uma sala eh decrementado

        // se a sala atual estiver cheia, guia comeca a explicacao
        if (guia_cont[i] == cap_sala[i]) {
            printf("Sala %d completa, começando a explicação\n", i+1);
            guia_cont[i] = 0;   // apos explicacao, contador zera para receber novos turistas na sala atual
        } // este recurso so eh acessado apos a entrada do ultimo turista de um grupo de turistas do tamanho da capacidade da sala atual

        sem_post(&guia);    // guia libera a entrada / saida da sala atual
        sleep(2);           // turistas terminam de escutar a explicacao

        sem_post(&sala[i]); // turistas saem da sala
    }
}

int main () {
    pthread_t pessoa[ num_turistas ];

    // inicia o semaforo das tres salas mais o guia
    for (int i=0; i<3; i++)
        sem_init(&sala[i], 0, cap_sala[i]);
    sem_init(&guia, 0, 1);

    // cada turista entra no museu
    for (long int i = 0; i < num_turistas; i++)
        pthread_create(&pessoa[i], NULL, turista, (void*)i);

    // espera cada pessoa sair do museu
    for (int i = 0; i < num_turistas; i++)
        pthread_join(pessoa[i], NULL);

    // destroi todos os semaforos
    for (int i=0; i<3; i++)
        sem_destroy(&sala[i]);
    sem_destroy(&guia);

    // // mostra se todas as pessoas sairam do museu (passando pela ultima sala)
    // printf("%d\n", cont_geral);

    return 0;
}

// as instrucoes colocadas em comentario seriam para verificar ao final se houveram pessoas que sobraram e nao completaram o numero de capacidade da ultima sala, assim nao recebendo a explicacao do guia
// mas como 90 eh divisivel por 10, 6 e 18, todos recebem a explicacao ao final do programa, caso contrario seria necessario colocar um condicao do tipo (cont_geral < cap_sala[i]), quando i=2, na avaliacao do guia

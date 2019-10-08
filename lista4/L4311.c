// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: L4311.c
// atividade: 3.1.1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t caminhonete;
pthread_mutex_t pacote;

static const int max_pacotes = 30;    // numero de pacotes que serao solicitados por cada cliente
static const int capacidade = 10;     // numero de pacotes que a caminhonete leva por viagem
static int carregamento = 0;          // numero de pacotes que funcionario ja colocou na caminhonete
static int n_clientes;                // numero de clientes que solicitarao a entrega de pacotes (definido pelo usuario)
static int cliente_id = 0;            // id do cliente que esta na fila para solicitar uma entrega

// entrega de pacotes (so eh acionada pelo funcionario quando caminhonete estiver cheia, com 10 pacotes)
void* entrega () {
    int n_pacotes = n_clientes * max_pacotes;   // numero total de pacotes para serem entregues (inicialmente eh o numero de clientes multiplicado pelo numero de pacotes por cliente)

    // enquanto os pacotes, no total, nao acabaram
    while (n_pacotes != 0) {
        pthread_mutex_lock(&pacote);
        // se caminhonete estiver cheia, funcionario sai para a entrega
        if (carregamento == capacidade) {
            printf("Saindo para entregar %d pacotes\n", carregamento);
            carregamento = 0;                     // esvazia a caminhonete
            n_pacotes = n_pacotes - capacidade;   // o numero total de pacotes restantes eh diminuido pelo numero de pacotes que acabaram de ser entregues
            sleep(2);                             // tempo de duracao da viagem
            printf("Retornando das entregas e pronto para atender mais clientes\n");
            // sleep(1);
        }
        pthread_cond_signal(&caminhonete);    // sinaliza a caminhonete ja chegou ou ainda esta na agencia
        pthread_mutex_unlock(&pacote);
    }
    printf("Todos os pacotes foram entregues, nao ha mais clientes na fila\n");
}

// solicitacoes de entrega feita pelos clientes
void* solicitacao (void* id) {
    long int tid = (long int)id;    // id do cliente atual
    int n_pacotes = max_pacotes;    // numero de pacotes restantes do cliente atual (inicialmente eh igual ao numero maximo de pacotes por cliente)

    // enquanto os pacotes do cliente nao acabaram
    while (n_pacotes != 0) {
        pthread_mutex_lock(&pacote);
        // se cliente atual eh o primeiro da fila
        if (tid == cliente_id) {
            // se caminhonete ainda nao esta cheia
            if (carregamento < capacidade) {
                n_pacotes--;      // cliente solicita entrega de um pacote
                carregamento++;   // caminhonete recebe pacote solicitado pelo cliente
                printf("Cliente %ld solicitou a entrega de um pacote. Dele, restam %d\n", tid+1, n_pacotes);
                // sleep(1);
                pthread_cond_wait(&caminhonete, &pacote);   // cliente espera caminhonete sair para entrega
            }
            cliente_id++;   // cliente vai para o final da fila
        } // se fila deu uma volta, comeca a solicitacao de novos pacotes pelos clientes
        else if (cliente_id == n_clientes) {
            cliente_id = 0;
        }
        pthread_mutex_unlock(&pacote);
    }
}

int main () {
    // define numero inicial de clientes
    do {
        printf("Numero de clientes: ");
        scanf("%d", &n_clientes);
    } while ((n_clientes <= 1) || (n_clientes >= 100));

    // os clientes comecam a solicitar a entrega dos pacotes
    pthread_t funcionario;
    pthread_t cliente[ n_clientes ];
    pthread_cond_init(&caminhonete, NULL);
    pthread_mutex_init(&pacote, NULL);
    for (long int i=0; i < n_clientes; i++) {
        pthread_create(&cliente[i], NULL, solicitacao, (void*)i);
    } sleep(2);
    pthread_create(&funcionario, NULL, entrega, NULL);

    // espera a finalizacao das entregas
    for (long int i=0; i < n_clientes; i++) {
        pthread_join(cliente[i], NULL);
    } pthread_join(funcionario, NULL);

    // finaliza as entregas
    pthread_cond_destroy(&caminhonete);
    pthread_mutex_destroy(&pacote);
    return 0;
}

// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: 16.c
// atividade: 1.6

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NT 4

long long int somavalores (int *valores, int n) {
    long long int soma = 0;
    int mt;
    omp_set_num_threads (NT);

    #pragma omp parallel
    {
        long long int soma_parcial = 0;
        int i;
        #pragma omp for
        for (i = 0; i < n; i++) {
            soma_parcial = soma_parcial + valores[i];
        }
        #pragma omp atomic
        soma = soma + soma_parcial;
    }
    return soma;
}

int main() {
    long long int i, n, soma;
    int *valores;

    // scanf("%lld", &n);
    n = 1000000000;
    valores = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        valores[i] = 1;

    double inicio = omp_get_wtime();
    soma = somavalores(valores, n);
    double fim = omp_get_wtime();

    printf("Soma: %lld - %s\n", soma, soma == n ? "ok" : "falhou");
    printf ("Tempo de processamento: %lf\n", fim-inicio);

    return 0;
}

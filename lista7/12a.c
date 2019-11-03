// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: 12a.c
// atividade: 1.2.a

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long int somavalores(int *valores, int n) {
    long long int soma = 0;

    for (int i = 0; i < n; i++)
        soma = soma + valores[i];

    return soma;
}

int main() {
    long long int i, n, soma;
    int *valores;

    double inicio = omp_get_wtime();
    // scanf("%lld", &n);
    n = 1000000000;
    valores = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        valores[i] = 1;

    soma = somavalores(valores, n);
    printf("Soma: %lld - %s\n", soma, soma == n ? "ok" : "falhou");

    double fim = omp_get_wtime();
    printf ("Tempo total da execução: %lf\n", fim-inicio);

    return 0;
}

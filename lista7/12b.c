// autor: Ana Luisa
// autor: Gabriel Sylar
// arquivo: 12b.c
// atividade: 1.2.b

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

    // scanf("%lld", &n);
    n = 1000000000;
    valores = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        valores[i] = 1;

    double inicio = omp_get_wtime();
    soma = somavalores(valores, n);
    double fim = omp_get_wtime();

    printf("Soma: %lld - %s\n", soma, soma == n ? "ok" : "falhou");
    printf ("Tempo da soma somente: %lf\n", fim-inicio);

    return 0;
}

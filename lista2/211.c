// autores: Nalu e Sylar
// arquivo: 211.c
// atividade: 2.1.1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *conta1(void *x) {

    double *valor = malloc(sizeof(double));
    *valor = *(double *)x;

    *valor = (*valor) * (*valor) * 10;
    pthread_exit(valor);
}

void *conta2(void *x) {

    double *valor2 = malloc(sizeof(double));
    *valor2 = *(double *)x;

    *valor2 = (*valor2) * (*valor2) * (*valor2) * 42;
    pthread_exit(valor2);
}

int main(){

    double x, result;

    scanf("%lf", &x);

    pthread_t t1, t2;

    void *r1, *r2;

    pthread_create(&t1, NULL, conta1, (double *)&x);
    pthread_create(&t2, NULL, conta2, (double *)&x);

    pthread_join(t1, &r1);
    pthread_join(t2, &r2);

    result = (*(double *)r1) + (*(double *)r2);

    printf("%.4lf\n", result);
    free(r1);
    free(r2);
    return 0;
}

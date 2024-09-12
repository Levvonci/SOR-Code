#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

// Struttura per passare i parametri ai thread
typedef struct {
    int start;
    int end;
    unsigned long long result;
} ThreadParams;

// Funzione eseguita dai thread per calcolare il prodotto parziale
void *factorial_part(void *arg) {
    ThreadParams *params = (ThreadParams *)arg;
    params->result = 1;

    for (int i = params->start; i <= params->end; i++) {
        params->result *= i;
    }

    return NULL;
}

int main() {
    int n;
    printf("Inserisci un numero: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Il fattoriale non è definito per numeri negativi.\n");
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    ThreadParams params[NUM_THREADS];
    int range = n / NUM_THREADS;

    // Creazione dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        params[i].start = i * range + 1;
        params[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * range;
        pthread_create(&threads[i], NULL, factorial_part, &params[i]);
    }

    // Attende la terminazione dei thread e combina i risultati
    unsigned long long factorial = 1;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        factorial *= params[i].result;
    }

    printf("Il fattoriale di %d è: %llu\n", n, factorial);
    return 0;
}


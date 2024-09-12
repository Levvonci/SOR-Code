#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10

// Array condiviso
int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Variabile globale per la somma
int global_sum = 0;

// Mutex per proteggere l'accesso alla variabile globale
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Struttura per passare i parametri ai thread
typedef struct {
    int start_index;
    int end_index;
} ThreadParams;

// Funzione eseguita dai thread per calcolare la somma parziale
void *thread_sum(void *arg) {
    ThreadParams *params = (ThreadParams *)arg;
    int local_sum = 0;

    // Calcola la somma parziale dell'array
    for (int i = params->start_index; i < params->end_index; i++) {
        local_sum += array[i];
    }

    // Aggiorna la somma globale protetta dal mutex
    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    // Creazione dei thread
    pthread_t tid1, tid2;
    ThreadParams params1 = {0, ARRAY_SIZE / 2};
    ThreadParams params2 = {ARRAY_SIZE / 2, ARRAY_SIZE};

    // Crea i due thread
    pthread_create(&tid1, NULL, thread_sum, &params1);
    pthread_create(&tid2, NULL, thread_sum, &params2);

    // Attende la terminazione dei thread
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Stampa la somma totale calcolata dai due thread
    printf("La somma totale è: %d\n", global_sum);

    // Distrugge il mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}


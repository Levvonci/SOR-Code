/*
Scrivere un programma C che segue le seguenti specifiche.
Il processo eseguito, inizialmente crea un buffer come array di 11 numeri interi, inizializzati a zero. In seguito genera tre thread utilizzando le librerie POSIX secondo le seguenti specifiche:
•   Il primo thread in un ciclo infinito sceglie casualmente una cella del buffer e vi scrive il numero +1, qualsiasi sia il valore presente nella cella.
•   Il secondo thread in un ciclo infinito sceglie casualmente una cella del buffer e vi scrive il numero -1, qualsiasi sia il valore presente nella cella.
•   Il terzo thread in un ciclo infinito controlla se tutte le celle del buffer sono state inizializzate ad un valore diverso da 0. In caso positivo, determina se il numero di celle contenenti un valore pari a +1 è maggiore di quelle con -1 e termina tutti e tre i thread.
•   Mentre un thread ha accesso al buffer, nessun altro thread deve accedervi.
•   Una volta che un thread ha acceduto in lettura o scrittura al buffer, deve attendere un numero di secondi random tra 0 e 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 11


int buffer[BUFFER_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //Mutex


int random_index(int max) { //Genera numeri cas
    return rand() % max;
}

void *thread_increment(void *arg) { //Thread 1
    while (1) {
        int index = random_index(BUFFER_SIZE); //Cella casuale
        pthread_mutex_lock(&mutex); //Mutex lock
        buffer[index] = 1; // +1 cella
        pthread_mutex_unlock(&mutex); //Mutex unlock
        sleep(random_index(4)); //Sleep 0 3
    }
    return NULL;
}

void *thread_decrement(void *arg) { // Thread 2
    while (1) {
        int index = random_index(BUFFER_SIZE); //Cella casuale 
        pthread_mutex_lock(&mutex); //Mutex lock
        buffer[index] = -1; // -1 cella
        pthread_mutex_unlock(&mutex); //Mutex unlock
        sleep(random_index(4)); // Sleep 0 3
    }
    return NULL;
}

void *thread_checker(void *arg) { // Thread 3
    while (1) {
        pthread_mutex_lock(&mutex); // Mutex lock
        int all_non_zero = 1;
        int count_ones = 0;
        int count_neg_ones = 0;
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == 0) {
                all_non_zero = 0;
                break;
            }
            if (buffer[i] == 1) {
                count_ones++;
            } else if (buffer[i] == -1) {
                count_neg_ones++;
            }
        }
        
        if (all_non_zero) {
            if (count_ones > count_neg_ones) {
                pthread_mutex_unlock(&mutex); // Mutex unlock
                pthread_exit(NULL); // Termina tutti i thread
            }
        }
        pthread_mutex_unlock(&mutex);
        sleep(random_index(4));
    }
    return NULL;
}

int main() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 0;
    }
    
    srand(time(NULL));
    
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, thread_increment, NULL);
    pthread_create(&tid2, NULL, thread_decrement, NULL);
    pthread_create(&tid3, NULL, thread_checker, NULL);
    
    pthread_join(tid3, NULL);
    
    pthread_cancel(tid1);
    pthread_cancel(tid2);
    
    pthread_mutex_destroy(&mutex);
    
    printf("Fine\n");
    return 0;
}


/*
Scrivere un programma C che segue le seguenti specifiche.
Il processo eseguito, inizialmente crea un buffer come array di 11 numeri interi, inizializzati a zero. 
In seguito genera tre thread utilizzando le librerie POSIX secondo le seguenti specifiche:
Il primo thread in un ciclo infinito sceglie casualmente una cella del buffer e vi scrive il numero +1, 
qualsiasi sia il valore presente nella cella.
Il secondo thread in un ciclo infinito sceglie casualmente una cella del buffer e vi scrive il numero -1, 
qualsiasi sia il valore presente nella cella.
Il terzo thread in un ciclo infinito controlla se tutte le celle del buffer sono state inizializzate ad un valore diverso da 0. 
In caso positivo, determina se il numero di celle contenenti un valore pari a +1 è maggiore di quelle con -1 e termina tutti e tre i thread.
Mentre un thread ha accesso al buffer, nessun altro thread deve accedervi.
Una volta che un thread ha acceduto in lettura o scrittura al buffer, deve attendere un numero di secondi random tra 0 e 3
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 3
#define ARR_SIZE 11

int array[ARR_SIZE] = {0};
pthread_mutex_t mutex;
int array_init = 0;

void print_buffer() {
  printf("[ ");
  for (int i = 0; i < ARR_SIZE; i++) {
    printf("%d ", array[i]);
  }
  printf("]\n");
}

void *piu1(){
    srand(time(NULL));
    int indice;
    while (array_init == 0) {
        indice = rand() % (ARR_SIZE);
        pthread_mutex_lock(&mutex);
        array[indice] = +1;
        pthread_mutex_unlock(&mutex);

        int random_sleep = rand() % 4;
        sleep(random_sleep);
    }
    return NULL;
}

void *meno1(){
    srand(time(NULL));
    int indice;
    while (array_init == 0){
        indice = rand() % (ARR_SIZE);
        pthread_mutex_lock(&mutex);
        array[indice] = -1;
        pthread_mutex_unlock(&mutex);

        int random_sleep = rand() % 4;
        sleep(random_sleep);
    }
    return NULL;
}

void *check(){
    while (1){
        int num_pos = 0, num_neg = 0, count = 0, rand_sleep;
    
        pthread_mutex_lock(&mutex);
        for(int i = 0; i < ARR_SIZE; i++){
            if (array[i] != 0){
                count ++;
                if (array[i] == +1){
                    num_pos ++;
                } else {
                    num_neg ++;
                }
            }
        }
        if (count == ARR_SIZE) {
        array_init = 1;
        print_buffer();
        printf("Il numero di +1 nell'array è: %d\n", num_pos);
        printf("Il numero di -1 nell'array è: %d\n", num_neg
        );
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
        } else {
        pthread_mutex_unlock(&mutex);
        rand_sleep = rand() % 4;
        sleep(rand_sleep);
        }
    }
}

int main (int argc, char *argv[]) {
    pthread_t th[3];
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&th[0], NULL, &piu1, NULL);
    pthread_create(&th[1], NULL, &meno1, NULL);
    pthread_create(&th[2], NULL, &check, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(th[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
}


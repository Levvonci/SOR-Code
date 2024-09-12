/*
Si scriva un programma con tre thread che risolvono il seguente problema:
Un buffer di n elementi inizializzato con a -1 viene riempito nel seguente modo:
    - Il primo thread aggiunge nelle posizioni pari del buffer un numero casuale
da 0 a 100.
    - Il secondo thread aggiunge nelle posizioni dispari del buffer un casuale
da 100 a 200.
    - Il terzo thread somma gli elementi e modifica il buffer nel seguente modo:
        buff[0] = buff[0], buff[1] = buff[1] + buff[0], buff[2] = buff[1] +
buff[2] Si proponga una soluzione di mutua esclusione.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARR_SIZE 20

int buffer[ARR_SIZE] = {-1};
pthread_mutex_t mutex;

void print_buffer() {
  printf("[ ");
  for (int i = 0; i < ARR_SIZE; i++) {
    printf("%d ", buffer[i]);
  }
  printf("]\n");
}
void *pari() {
  srand(time(NULL));
  int num;
  for (int i = 0; i < ARR_SIZE; i += 2) {
    num = rand() % 101;
    pthread_mutex_lock(&mutex);
    buffer[i] = num;
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  pthread_exit(NULL);
}

void *dispari() {
  srand(time(NULL) + 444);
  int num;
  for (int i = 1; i < ARR_SIZE; i += 2) {
    num = rand() % 101 + 100;
    pthread_mutex_lock(&mutex);
    buffer[i] = num;
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  pthread_exit(NULL);
}

void *sum() {
  printf("[THREAD SOMMA]: Array prima del calcolo: \n");
  print_buffer();

  for (int i = 1; i < ARR_SIZE; i++) {
    buffer[i] = buffer[i] + buffer[i - 1];
  }
  printf("[THREAD SOMMA]: Array dopo il calcolo: \n");
  print_buffer();

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t th[3];
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&th[0], NULL, &pari, NULL);
  pthread_create(&th[1], NULL, &dispari, NULL);

  pthread_join(th[0], NULL);
  pthread_join(th[1], NULL);

  pthread_create(&th[2], NULL, &sum, NULL);
  pthread_join(th[2], NULL);

  pthread_mutex_destroy(&mutex);
}

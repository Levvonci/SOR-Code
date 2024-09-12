/* Scrivere un programma in C con tre thread che operano su un array di
   dimensione N.
    - Il primo thread riempie un array con numeri casuali tra 0 e 100.
    - Il secondo thread trova il valore massimo nell'array.
    - Il terzo trova il valore minimo. (senza utilizzare pthread_cond_t)
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARR_SIZE 20

int buff[ARR_SIZE] = {};
pthread_mutex_t mutex;

void print_array() {
  printf("[ ");
  for (int i = 0; i < ARR_SIZE; i++) {
    printf("%d ", buff[i]);
  }
  printf("]\n");
}

void *init() {
  srand(time(NULL));
  int num;
  for (int i = 0; i < ARR_SIZE; i++) {
    num = rand() % 100;
    buff[i] = num;
  }
  printf("[INIT THREAD]: ");
  print_array();
  pthread_exit(NULL);
}

void *max() {
  int max = buff[0];
  for (int i = 1; i < ARR_SIZE; i++) {
    if (max < buff[i]) {
      max = buff[i];
    }
  }
  printf("[MAX THREAD]: Il max dell'array è %d.\n", max);
  pthread_exit(NULL);
}

void *min() {
  int min = buff[0];
  for (int i = 1; i < ARR_SIZE; i++) {
    if (min > buff[i]) {
      min = buff[i];
    }
  }
  printf("[MIN THREAD]: Il max dell'array è %d.\n", min);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t th[3];
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&th[0], NULL, &init, NULL);
  pthread_join(th[0], NULL);

  pthread_create(&th[1], NULL, &max, NULL);
  pthread_create(&th[2], NULL, &min, NULL);

  pthread_join(th[1], NULL);
  pthread_join(th[2], NULL);

  pthread_mutex_destroy(&mutex);
}

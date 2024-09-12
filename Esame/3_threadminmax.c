/*
Scrivere un programma in C con tre thread che operano su due array di dimensione
N inizialmente a 0.
- Il primo thread scrive in un array A numeri casuali tra 1 e 150, scrivendo un
numero per volta in posizioni randomiche.
- Il secondo thread scrive in un array B numeri cassuali tra 150 e 300,
scrivendo un numero per volta in posizioni randomiche.
- Il terzo thread controlla se entrambi gli array sono stati inizializzati.
  In caso affermativo calcola il massimo in A e in B e calcola il minimo in A e
in B.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 3
#define ARR_SIZE 10

int arr_A[ARR_SIZE] = {0};
int arr_B[ARR_SIZE] = {0};
pthread_mutex_t mutex_t1, mutex_t2;
int arr_A_init = 0;
int arr_B_init = 0;

void *array_a_numbers() {
  srand(time(NULL));
  int index, number;
  while (arr_A_init == 0) {
    index = rand() % ARR_SIZE;
    number = rand() % 150 + 1;
    pthread_mutex_lock(&mutex_t1);
    printf("[THREAD A]: Ho generato il numero %d e lo inserisco in posizione %d.\n", number, index);
    arr_A[index] = number;
    pthread_mutex_unlock(&mutex_t1);

    int rand_sleep = rand() % 3;
    sleep(rand_sleep);
  }
  return NULL;
}

void *array_b_numbers() {
  srand(time(NULL) - 444);
  int index, number;
  while (arr_B_init == 0) {
    index = rand() % ARR_SIZE;
    number = rand() % 150 + 151;
    pthread_mutex_lock(&mutex_t1);
    printf("[THREAD B]: Ho generato il numero %d e lo inserisco in posizione %d.\n", number, index);
    arr_B[index] = number;
    pthread_mutex_unlock(&mutex_t1);

    int rand_sleep = rand() % 3;
    sleep(rand_sleep);
  }
  return NULL;
}

void *array_check() {
  while (1) {
    pthread_mutex_lock(&mutex_t1);
    // pthread_mutex_lock(&mutex_t2);
    printf("Checking...\n");
    int init_A = 0, init_B = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
      if (arr_A[i] != 0) {
        init_A++;
      }
      if (arr_B[i] != 0) {
        init_B++;
      }
    }
    if (init_A == ARR_SIZE) {
      arr_A_init = 1;
    }
    if (init_B == ARR_SIZE) {
      arr_B_init = 1;
    }
    if (init_A == ARR_SIZE && init_B == ARR_SIZE) {
      int min_A = arr_A[0], max_A = arr_A[0], min_B = arr_B[0], max_B = arr_B[0];
      for (int i = 1; i < ARR_SIZE; i++) {
        if (min_A > arr_A[i]) {
          min_A = arr_A[i];
        }
        if (max_A < arr_A[i]) {
          max_A = arr_A[i];
        }
        if (min_B > arr_B[i]) {
          min_B = arr_B[i];
        }
        if (max_B < arr_B[i]) {
          max_B = arr_B[i];
        }
      }
      printf("Array A: [ ");
      for (int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", arr_A[i]);
      }
      printf("]");
      printf("[THREAD CHECK]: Il min di A è: %d\n Il max di A è: %d\n", min_A,
             max_A);

      printf("Array B: [ ");
      for (int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", arr_B[i]);
      }
      printf("]");

      printf("[THREAD CHECK]: Il min di B è: %d\n Il max di B è: %d\n", min_B,
             max_B);
      pthread_mutex_unlock(&mutex_t1);
      // pthread_mutex_unlock(&mutex_t2);
      return NULL;
    }
    printf("Array ancora non inizializzati!\n");
    pthread_mutex_unlock(&mutex_t1);
    // pthread_mutex_unlock(&mutex_t2);

    int rand_sleep = rand() % 3;
    sleep(rand_sleep);
  }
}

int main(int argc, char *argv[]) {
  pthread_t th[NUM_THREADS];
  pthread_mutex_init(&mutex_t1, NULL);
  // pthread_mutex_init(&mutex_t2, NULL);

  pthread_create(&th[0], NULL, &array_a_numbers, NULL);
  pthread_create(&th[1], NULL, &array_b_numbers, NULL);
  pthread_create(&th[2], NULL, &array_check, NULL);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(th[i], NULL);
  }

  pthread_mutex_destroy(&mutex_t1);
  // pthread_mutex_destroy(&mutex_t2);
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREAD 4
pthread_mutex_t mutex;

int temp = 0;

void *gen_temp() {
  srand(time(NULL));
  int rand_temp, rand_sleep;
  while (1) {
    rand_temp = rand() % 51 - 10;
    // pthread_mutex_lock(&mutex);
    if (rand_temp >= -5 && rand_temp <= 35) {
      pthread_mutex_lock(&mutex);
      temp = rand_temp;
      pthread_mutex_unlock(&mutex);
      printf("Temperatura generata: %d\n", rand_temp);
      rand_sleep = rand() % 2;
      sleep(rand_sleep);
    } else {
      printf("THREAD GENERATORE TERMINATO. (%d)\n", rand_temp);
      // pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);
    }
  }
}

void *check_temp() {
  // srand(time(NULL));
  // int rand_sleep;
  while (1) {
    pthread_mutex_lock(&mutex);
    if (temp >= -5 && temp <= 35) {
      printf("[THREAD CHECK]: Temperatura ok: %d °C.\n", temp);
      pthread_mutex_unlock(&mutex);
      sleep(1);
    } else {
      printf("EMERGENZA!\n");
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);
    }
  }
}

int main(int argc, char *argv[]) {
  pthread_t th[NUM_THREAD];
  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < NUM_THREAD - 1; i++) {
    pthread_create(&th[i], NULL, &gen_temp, NULL);
  }
  pthread_create(&th[3], NULL, &check_temp, NULL);

  for (int i = 0; i < NUM_THREAD; i++) {
    pthread_join(th[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
}

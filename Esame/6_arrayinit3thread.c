#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARR_SIZE 11

pthread_mutex_t mutex;
int buffer[ARR_SIZE] = {0};
int done = 0;

void print_buffer() {
  printf("[ ");
  for (int i = 0; i < ARR_SIZE; i++) {
    printf("%d ", buffer[i]);
  }
  printf("]\n");
}

void *plus_one() {
  srand(time(NULL));
  int index, rand_sleep;
  while (done == 0) {
    index = rand() % (ARR_SIZE);
    pthread_mutex_lock(&mutex);
    buffer[index] = 1;
    pthread_mutex_unlock(&mutex);
    printf("[THREAD 1]: Ho inserito 1 in posizione %d.\n", index);
    rand_sleep = rand() % 4;
    sleep(rand_sleep);
  }
  pthread_exit(NULL);
}

void *minus_one() {
  srand(time(NULL) - 444);
  int index, rand_sleep;
  while (done == 0) {
    index = rand() % (ARR_SIZE);
    pthread_mutex_lock(&mutex);
    buffer[index] = -1;
    pthread_mutex_unlock(&mutex);
    printf("[THREAD -1]: Ho inserito -1 in posizione %d.\n", index);
    rand_sleep = rand() % 4;
    sleep(rand_sleep);
  }
  pthread_exit(NULL);
}

void *check() {
  srand(time(NULL) - 888);
  while (1) {
    int init_count = 0, rand_sleep, pos_count = 0, neg_count = 0;
    printf("[CHECK THREAD]: Checking...\n");
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < ARR_SIZE; i++) {
      if (buffer[i] != 0) {
        init_count++;
        if (buffer[i] == 1) {
          pos_count++;
        } else {
          neg_count++;
        }
      }
    }
    if (init_count == ARR_SIZE) {
      done = 1;
      print_buffer();
      printf("[CHECK THREAD]: Il numero di 1 nell'array è %d mentre quello di "
             "-1 è %d.\n",
             pos_count, neg_count);
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);
    } else {
      pthread_mutex_unlock(&mutex);
      rand_sleep = rand() % 4;
      sleep(rand_sleep);
    }
  }
}

int main(int argc, char *argv[]) {
  pthread_t th[3];
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&th[0], NULL, &plus_one, NULL);
  pthread_create(&th[1], NULL, &minus_one, NULL);
  pthread_create(&th[2], NULL, &check, NULL);

  for (int i = 0; i < 3; i++) {
    pthread_join(th[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
}

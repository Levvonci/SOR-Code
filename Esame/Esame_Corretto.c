#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int temp = 0;
int exit_threads = 0;

void* generate_temp(void* arg) {
    int thread_num = *(int*)arg;
    while(1) {
        pthread_mutex_lock(&mutex);
        if(exit_threads) {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        int random_temp = (rand() % 51) - 10;
        if(random_temp >= -5 && random_temp <= 35) {
            temp = random_temp;
            printf("Thread %d: Temp = %d\n", thread_num, temp);
        } else {
            exit_threads = 1;
            printf("Warning: Temp out of range! (%d)\n", random_temp);
            pthread_mutex_unlock(&mutex);
            pthread_cancel(pthread_self());
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* check_temp(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        if(temp < -5 || temp > 35) {
            printf("Emergenza: Temp fuori range! (%d)\n", temp);
            exit_threads = 1;
        }
        pthread_mutex_unlock(&mutex);
        if(exit_threads) {
            pthread_cancel(pthread_self());
        }
        sleep(1);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t threads[NUM_THREADS];
    int thread_nums[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i + 1;
        pthread_create(&threads[i], NULL, generate_temp, &thread_nums[i]);
    }

    pthread_t check_thread;
    pthread_create(&check_thread, NULL, check_temp, NULL);

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_join(check_thread, NULL);

    return 0;
}

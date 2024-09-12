#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Num_Thread 4
pthread_mutex_t mutex;
int temp = 0;

/*Funzione Genera Temperatura*/

void *gen_temp(){
    srand(time(NULL));
    int rand_temp, rand_sleep;
    while(1){
        rand_temp = rand() % 51 - 10;
        if(rand_temp >= -5 && rand_temp <= 35){
            pthread_mutex_lock(&mutex);
            temp = rand_temp;
            pthread_mutex_unlock(&mutex);
            rand_sleep = rand() % 2;
            sleep(rand_sleep);
        }else{
            printf("Temperatura fuori range: %d \n", rand_temp);
            pthread_exit(NULL);
        }
    }
}

/* Funzione Verifica Temperatura */

void *check_temp(){
    while(1){
        pthread_mutex_lock(&mutex);
        if(temp >= -5 && temp <= 35){
            printf("Temperatura ok: %d \n", temp);
            pthread_mutex_unlock(&mutex);
            sleep(1);
        }else{
            printf("EMERGENZA!! \n");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }
}


int main(int argc, char *argv[]){
    pthread_t th [Num_Thread];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < Num_Thread ; i++){
        pthread_create(&th[i], NULL, &gen_temp, NULL);
    }
    pthread_create(&th[Num_Thread], NULL, &check_temp, NULL);
    
    for(int i = 0 ; i < Num_Thread ; i++){
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

}

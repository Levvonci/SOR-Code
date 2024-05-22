#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int mails = 0;

void* routine(){
    for(int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]){
        
    int i;
    pthread_t th[8]; 
    pthread_mutex_init(&mutex, NULL);

    for(i = 0; i < 8; i++){
        if(pthread_create(th + i, NULL, &routine, NULL) != 0){
            perror("Errore nella creazione dei Thread\n");
            return 2;
        }
        printf("Il thread %d ha iniziato\n", i);   
    }
    for(i = 0; i < 8; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Errore nella join\n");
            return 3;
        }
        printf("Il thread %d ha terminato\n", i);
    }

    
    pthread_mutex_destroy(&mutex);
    printf("il numero di mail totale è: %d\n", mails);
    return 0;
}

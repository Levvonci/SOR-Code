/*
Crea 10 thread
Ogni thread prende un numero primo dall'array
Stampa quel numero a schermo
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int primi[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg){
    int indice = *(int*)arg;
    int sum = 0;
    for(int j = 0; j < 5; j++){
        sum += primi[indice + j];
    }
    printf("Somma locale = %d\n", sum);
    *(int*)arg = sum;
    return arg;
}

int main(int argc, char* argv[]){
    
    int i;
    pthread_t th[2];
    
    for(i = 0; i < 2; i++){
        int* a = malloc(sizeof(int));
        *a = i * 5;

        if(pthread_create(&th[i], NULL, &routine, a) != 0){
            perror("Errore nella creazione del thread\n");
        }
    }

    int sommaglobale = 0;

    for(i = 0; i < 2; i++){
        int* r;
        if(pthread_join(th[i], &r) != 0){
            perror("Errore nella join\n");
        }
        sommaglobale += *r;
        free(r);
    }
    printf("Somma globale = %d\n", sommaglobale);
    return 0; 
}

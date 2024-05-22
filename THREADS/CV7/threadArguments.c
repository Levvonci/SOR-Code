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
    printf("%d ", primi[indice]);
    free(arg);
}

int main(int argc, char* argv[]){
    
    int i;
    pthread_t th[10];
    
    for(i = 0; i < 10; i++){
        int* a = malloc(sizeof(int));
        *a = i;

        if(pthread_create(&th[i], NULL, &routine, a) != 0){
            perror("Errore nella creazione del thread\n");
        }
    }

    for(i = 0; i < 10; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Errore nella join\n");
        }
    }
    return 0; 
}


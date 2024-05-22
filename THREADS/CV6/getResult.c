#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void* roll_dice(){
    int valore = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = valore;
    //printf("Il valore del dato è: %d\n", valore);
    printf("Il risultato del thread è: %p\n", result);
    return (void*) result;
}

int main(int argc, char* argv[]){
    int* res;
    srand(time(NULL));
    pthread_t th;

    if(pthread_create(&th, NULL, &roll_dice, NULL) != 0){
        perror("Errore nella creazione del thread\n");
        return 1;
    }
    if(pthread_join(th,(void**) &res) != 0){
        perror("Errore nella wait\n");
        return 2;
    }
    
    printf("Main res: %p\n", res);
    printf("Il risultato è: %d\n", *res);
    free(res);
    return 0;
}

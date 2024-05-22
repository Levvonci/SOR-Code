
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int x = 2;

void* routine(){
    
    sleep(2);
    printf("Il valore di x é: %d\n", x);
}

void* routine2(){
    for(int i = 1; i<10; i++){
        x++;
    }

    sleep(2);
    printf("Il valore di x é: %d\n", x);
}

int main(int argc, char* argv[]){

  pthread_t t1, t2;
  pthread_create(&t1, NULL, &routine, NULL);
  pthread_create(&t2, NULL, &routine2, NULL); 
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}


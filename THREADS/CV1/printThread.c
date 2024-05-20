
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void* routine(){
  printf("Test dal thread\n");
  sleep(5);
  printf("Stoppando il thread\n");
}


int main(int argc, char* argv[]){

  pthread_t t1, t2;
  pthread_create(&t1, NULL, &routine, NULL);
  pthread_create(&t2, NULL, &routine, NULL); 
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
int main(int argc, char* argv[]){

  int id1 = fork();
  int id2 = fork();
  
  if(id1 == 0){
    if(id2 == 0){
      
      printf("Siamo i processi y\n");
    }else{
      
      printf("Siamo i processi x\n");
    }
  }else{
    
    if(id2 == 0 ){
      
      printf("Siamo i processi z\n");
    }else{
      
      printf("Siamo i genitori\n");
    }
  }

  while(wait(NULL) != -1 || errno != ECHILD){
    
    printf("Aspetto la fine di un figlio\n");
  }
  

  return 0;
}


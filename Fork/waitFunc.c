#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  
  int id = fork();                //creo processo figlio
  int n;

  if(id == 0){
                                  //sono nel figlio
    n = 1;
  }else{
                                  //sono nel padre
    n = 6;
  }
  if(id != 0){
                                  //aspetta il figlio
    wait();
  }
  
  int i;
  for(i = n; i < n + 5; i++){
                                  
    printf("%d", i);
    fflush(stdout);
  }
  
  if(id != 0){
    
    printf("\n");
  }
  return 0;
}

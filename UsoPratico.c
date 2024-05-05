#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]){
  
  int arr[] = {1,2,3,4,5,6};
  int fd[2];
  int inizio;
  int fine;
  int arrSize = sizeof(arr) / sizeof(int);

  if(pipe(fd) == -1){
    return 1;
  }
  
  int id = fork();

  if(id == -1){
    return 2;
  }
  if(id == 0){
    inizio = 0;
    fine = arrSize / 2; 
  }else{
    wait(id);
    inizio = arrSize / 2;
    fine = arrSize;
  }
  

  int sum = 0;
  int i;

  for(i = inizio; i < fine; i++){
    sum += arr[i];
  }

  if(id == 0){
    if(write(fd[1], &sum, sizeof(sum)) == -1){
      return 3;
    }
    close(fd[1]);
  }else{
    
    int sumFiglio;
    close(fd[1]);
    if(read(fd[0], &sumFiglio, sizeof(sumFiglio)) == -1){
      return 4;
    }
    close(fd[0]);
    
    int SommaTotale = sum + sumFiglio;
    printf("Somma totale = %d\n", SommaTotale);
  }
  
  printf("Somme parziali: %d\n", sum);
  
  return 0;
}

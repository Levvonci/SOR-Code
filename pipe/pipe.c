/*
Scrivi un programma che crei un processo figlio, il figlio deve ricevere in input un valore e tramite le pipe deve far leggere quel valore al padre
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]){
  
  int fd[2];

  //fd[0] - legge
  //fd[1] - scrive

  if (pipe(fd) == -1){                                //Creo la pipe, se pipe(fd) == -1 allora errore nella creazione della pipe
    printf("Errore nella creazione della pipe\n");
    return 1;
  }
  
  int id = fork();                                    //Eseguo la fork
  if(id == -1){                                       //Se pid == -1 errore nella fork
    printf("Errore nella fork\n");
    return 4;
  }
  if(id == 0){                                        //Sono nel figlio
    close(fd[0]);                                     //Chiudo il fd in lettura
    int x;
    printf("Inserisci un numero: ");                  //Inserisco input
    scanf("%d", &x);
    
    if(write(fd[1], &x, sizeof(int)) == -1){          //Scrivo nel fd, se fd[1] == -1 allora errore nella scrittura della pipe
      printf("Errore scrivendo nella pipe\n");
      return 2;
    }
    
    close(fd[1]);                                     //Chiudo fd in scrittura

  }else{                                              //Sono nel padre
    close(fd[1]);                                     //Chiudo fd in scrittura
    int y;
    if(read(fd[0], &y, sizeof(int)) == -1){           //Apro fd in lettura, se fd[0] == -1 allora errore nella luttura della pipe
      printf("Errore leggendo nella pipe\n");
      return 3;
    }
    close(fd[0]);                                     //Chiudo fd in lettura
    printf("il processo figlio mi ha mandato: %d", y);
  }
  
  
  return 0;
}

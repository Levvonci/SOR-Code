#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]){
  
  int pid;
  if((pid = fork()) == -1){
    perror("Errore nella fork()\n");
    return 1;
  }
  if(pid == 0){
    //figlio
    int file = open("RisultatoPing.txt", O_WRONLY | O_CREAT, 0777);
    
    if(file == -1){
      perror("Errore nella creazione del file\n");
      return 2;
    }
    printf("Il fd di RisultatoPing.txt è: %d", file);
    //Ridireziona lo stdout sul file RisultatoPing.txt, quindi il risultato del comando "ping" sarà scritto sul file
    //E duplica il file generato
    int file2 = dup2(file, STDOUT_FILENO);
    //Chiudi lo stdout del file originale, non del file duplicato
    close(file);

    //execlp per non passare il path del /bin/ping ma solo comando ping
    int err = execlp(
      "ping",
      "ping",
      "-c",
      "4",
      "google.com",
      NULL
    );
    
    if(err == -1){
      perror("Errore nel ping\n");
    }

  }else{
    //padre
    
  }
  
  return 0; 
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
  int pid;
  pid = fork();

  if(pid == -1){
    perror("Errore nella fork()\n");
    return 1;
  }
  if(pid == 0){
    printf("Sono il figlio di %d, con pid %d\n", getppid(), getpid());
    int pid2;
    pid2 = fork();
    if(pid2 == -1){
      perror("Errore nella fork()\n");
    }
    if(pid2 == 0){
      printf("Sono il figlio di %d, con pid %d\n", getppid(), getpid());
    }else{
      wait(NULL);
      printf("Sono il padre di %d, con pid %d\n", pid2, getpid());
    }

  }else{
    wait(NULL);
    printf("Sono il padre di %d, con pid %d\n", pid, getpid());
  }


  return 0;
}

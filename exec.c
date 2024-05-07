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
  
  execlp
  ("ping",
   "ping",
   "google.com",
   NULL
  );
  
  //Non avviene la print dato che il dopo il ping il processo termina

  printf("Qualcosa");
  return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    int fd = open("/home/lvnc/Documents/Uni/Code/RWsys/writeProva.txt", O_WRONLY | O_CREAT, S_IWRITE | S_IRUSR | S_IXUSR);
    
    if(fd == -1){
        perror("Errore nella creazione del file\n");
        return 1;
    }
    
    if(fd > -1){
        write(fd, "TestDiScrittura\n", 17); 
    }



    return 0;
}

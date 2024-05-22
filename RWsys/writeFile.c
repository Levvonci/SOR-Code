#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    int fd = open("/Users/lvnc/repo/SOR-Code/RWsys/writeProva.txt", O_WRONLY | O_CREAT, S_IWRITE | S_IRUSR | S_IXUSR);
    
    if(fd == -1){
        perror("Errore nella creazione del file\n");
        return 1;
    }
    
    if(fd > -1){
        write(fd, "TestDiScrittura\n", 19); 
    }

    close(fd);
    
    return 0;
}

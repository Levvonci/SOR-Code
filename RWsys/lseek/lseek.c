#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>


#define BUF_SIZE 5

int main(int argc, char* argv[]){
    int fd = open("/Users/lvnc/repo/SOR-Code/RWsys/lseek/fileprova.txt", O_RDONLY);
    char buf[BUF_SIZE]; //5

    if(fd == -1){
        perror("Errore nella lettura\n");
        return 1;
    }else{
        int seek = lseek(fd, (BUF_SIZE - 1)*2, SEEK_SET); // off set 8 bytes da sopra
        if(seek == -1){
            perror("Errore nella seek\n");
            return 2;
        }else{
            ssize_t numRead = read(fd, buf, BUF_SIZE - 2); //3 bytes buffer 4 su fd
            printf("%s\n", buf);
        }
        close(fd);
    }    


    return 0;
}
/*
FileProva = 
001
002
003
004
005
006
------------------------------------------
Ogni lettera/numero corrisponde ad un byte
Con lseek riposiziono l'offset di partenza per leggere su un file
Con SEEK_SET riposiziono l'offset di partenza dal primo byte leggibile del file
Successivamente la read mi prende in input il fd, il buffer che conterrá la mia parola/numero letto e il numero di bytes da leggere
In questo caso il numero di bytes da leggere era (BUF_SIZE = 5) - 2, dato che volevo leggere tutta la riga numero 3.
In questo caso ancora l'offset era posizionato a (BUF_SIZE - 1)*2 = 8, quindi su 001002|.
||Ricorda|| il carattere di fine stringa conta 1 byte, quindi per ogni riga in questo caso ho contato 4 bytes invece che 3
*/

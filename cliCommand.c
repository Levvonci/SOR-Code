#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int pid;
    if ((pid = fork()) == 0) {

        execlp("ping", "ping", "-c", "3", "google.it", NULL);

    } else {
        wait(NULL);
        printf("Successo!!");
    }

    return 0;
}

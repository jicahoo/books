#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
    pid_t pid;

    if ( (pid = fork()) < 0 ) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) {
        //First child
        if( (pid = fork()) < 0) {
            perror("fork error in first child\n");
        }

        if (pid == 0) {
            //second child
            sleep(5);
            printf("Second child, parent pid:%d\n", getppid());
            exit(0);
        } else {
            exit(0);
        }
    }

    if (waitpid(pid, NULL, 0) != pid) {
        perror("wait failed\n");
    }
    printf("Parent continue\n");
    //wait for the second child
    sleep(6);

    exit(0);

}

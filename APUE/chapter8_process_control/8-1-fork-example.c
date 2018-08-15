#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define x u.std

int glob = 6;
char buf[] = "a write to stdout\n";
int main() {
    printf("Hello World\n");
    int var;
    pid_t pid;
    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1)  != sizeof(buf) -1 ) {
        //err_sys("write error");
        perror("write error\n");
    }
    if ((pid = fork()) < 0 ) {
        //err_sys("fork error");
        perror("fork error!\n");
    } else if( pid == 0 ) {
        glob++;
        var++;
    } else {
        printf("parent process\n");
        sleep(2);
    }
    printf("pid = %d, glob = %d, var = %d \n", getpid(), glob, var);
    exit(0);
}

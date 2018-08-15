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
    printf("before fork \n");
    if ((pid = fork()) < 0 ) {
        //err_sys("fork error");
        perror("fork error!\n");
    } else if( pid == 0 ) {
        glob++;
        var++;
        printf("Child pid = %d, glob = %d, var = %d \n", getpid(), glob, var);
    } else {
        sleep(2);
        printf("Parent pid = %d, glob = %d, var = %d \n", getpid(), glob, var);
    }
    exit(0);
}

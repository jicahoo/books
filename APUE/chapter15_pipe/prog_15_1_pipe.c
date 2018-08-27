#include <unistd.h>
#include <stdio.h>
#define MAXLINE 100


int main(void) {
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0) {
        perror("Failed to create pipe\n");
    } else if ( (pid=fork()) < 0 ) {
        perror("Fork error\n");
    } else if (pid > 0) {
        //parent
        close(fd[0]);
        write(fd[1], "Hello world\n",12);
    } else {
        //child
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        printf("Got line: %s", line);
        //write(STDOUT_FILENO, line, n);
    }
}

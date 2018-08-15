#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


void pr_exit(int status) {
    if (WIFEXITED(status)) {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else {
        printf("Others\n");
    }
}

int main(void) {
    pid_t pid;
    int status;
    if ((pid = fork()) < 0) {
        perror("fork error\n");
    } if (pid == 0) {
        exit(7);
    }
    if (wait(&status) != pid) {
        perror("wait error\n");
    }
    pr_exit(status);

}

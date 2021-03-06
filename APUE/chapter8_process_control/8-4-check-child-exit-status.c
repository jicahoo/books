#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


void pr_exit(int status) {
    if (WIFEXITED(status)) {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? "(core file generated)":"");
#else
                "");
#endif
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
        //child process exit here
    }
    if (wait(&status) != pid) {
        perror("wait error\n");
    }
    pr_exit(status);

    if ((pid = fork()) < 0) {
        perror("fork error\n");
    } if (pid == 0) {
        abort();
        //child process exit here
    }
    if (wait(&status) != pid) {
        perror("wait error\n");
    }
    pr_exit(status);

    if ((pid = fork()) < 0) {
        perror("fork error\n");
    } if (pid == 0) {
        status /= 0; 
    }
    if (wait(&status) != pid) {
        perror("wait error\n");
    }
    pr_exit(status);

    exit(0);

}

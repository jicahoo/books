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
        printf("child pid: %d\n", getpid());
        int i = 0; 
        for(i = 0; i < 12; i++) {
            //After kill -9 <ppid>, it will print 'my parent pid: 1' to stdout
            printf("my parent pid: %d\n", getppid());
            sleep(5);
        }
        exit(7);
        //child process exit here
    }

    printf("parent pid: %d\n", getpid());


    if (wait(&status) != pid) {
        perror("wait error\n");
    }
    pr_exit(status);

    sleep(60);

    exit(0);

}

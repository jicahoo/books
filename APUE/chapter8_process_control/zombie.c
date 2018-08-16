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
        exit(7);
        //child process exit here
    }

    //If not call wait, the child process will be in zombie
    //Zombie process cann't be killed. It is a bug in your program that the parent process forgot to take care of the child processes.
    //https://stackoverflow.com/questions/16944886/how-to-kill-zombie-process
    //http://www.linuxandubuntu.com/home/what-are-zombie-processes-and-how-to-find-kill-zombie-processes
    if (wait(&status) != pid) {
        perror("wait error\n");
    }
    pr_exit(status);

    sleep(60);

    exit(0);

}

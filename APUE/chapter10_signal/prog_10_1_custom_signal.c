#include <stdio.h>
#include <signal.h>

/*
 *
 * Test method: 
 * kill -USR1 <PID>
 * kill -USR2 <PID> 
 * kill <PID> 
 * */

static void sig_usr(int);
int main() {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("Can't register sigusr1 handler!");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("Can't register sigusr2 handler!");
    }

    printf("before pause\n");
    for ( ; ; ) {
        pause();
    }
    printf("after pause\n");
}

static void sig_usr(int signo) {
    printf("enter sig_usr\n");
    if (signo == SIGUSR1) {
        printf("Recv SIGUSR1\n");
    } else if (signo == SIGUSR2) {
        printf("Recv SIGUSR2\n");
    } else {
        printf("Recv signal: %d\n", signo);
    }
    printf("leave sig_usr\n");
}

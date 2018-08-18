#include <fcntl.h>
#include <stdio.h>
//#include <unistd.h>

#define BUFFSIZE 5


void write_to_file(pid_t pid, char* buf) {
    int i = 100;
    int fd = open("./test.txt", O_RDWR);
    for(i =0 ;i < 1000; i++) {
        if (lseek(fd, 0L, SEEK_END) < 0 ) {
            perror("seek error");
        }

        ssize_t size = write(fd, buf,5);
        //printf("%d Char written: %d\n", pid, size);
        if (size != 5) {
            perror("Write failure\n");
        }
    }
    close(fd);
}

/**
 * Two processes are writing the same file at the same time without any sync mechanism.
 * User expect there should be 2000 lines in test.txt. However, the actual result surprise the user.
 */
int main(void) {
    printf("Hello World!\n");

    pid_t pid;
    if ( (pid = fork()) < 0 ) {
        perror("fork failed.\n");
    }

    if (pid == 0) {
        char buf[BUFFSIZE] = "ABCD\n";
        write_to_file(getpid(), buf);
    } else {
        char buf[BUFFSIZE] = "EFGH\n";
        write_to_file(getpid(), buf);
        wait(NULL);
    }
    
    return 0;
}



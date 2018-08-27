#include <fcntl.h>
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void) {
    int fd;
    if ( (fd = creat("file.hole", FILE_MODE)) < 0 ) {
        perror("Failed to create file.hole\n");
    }

    if ( write(fd, buf1, 10) != 10) {
        perror("Failed to write buf1\n");
    }

    if ( lseek(fd, 16384, SEEK_SET) == -1) {
        perror("Failed to seek 16384\n");
    }

    if ( write(fd, buf2, 10) != 10) {
        perror("Failed to write buf2\n");
    }

}

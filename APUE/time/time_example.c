#include <time.h>
#include <unistd.h>
#include <stdio.h>


void main(void) {
    time_t start = time(0);
    sleep(3);
    time_t dur = time(0) - start;

    printf("Duration: %d\n", dur);

}



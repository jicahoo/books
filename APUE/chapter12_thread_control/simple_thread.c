#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>

//gcc -pthread simple_thread.c  -o simple.exe

// At beginning, I didn't add *.
void *inc_x(void *x_void_ptr)
{
#ifdef SYS_gettid
        pid_t tid = syscall(SYS_gettid);
#else
#error "SYS_gettid unavailable on this system"
#endif
    printf("tid: %d\n", tid);
    printf("inc_x pid: %d\n", getpid());
    int *x_ptr = (int *)x_void_ptr;
    while(++(*x_ptr) < 100);
    printf("x increment finished\n");
}
int main() 
{
    printf("main pid: %d\n", getpid());
    int x=0, y=0;
    printf("x: %d, y: %d\n", x, y);
    pthread_t inc_x_thread;
    if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    while(++y < 100);
    printf("y increment finished\n");
    if(pthread_join(inc_x_thread, NULL)){
        fprintf(stderr, "Error joining\n");
        return 2;
    }
    printf("x: %d, y: %d\n", x, y);
    return 0;
}

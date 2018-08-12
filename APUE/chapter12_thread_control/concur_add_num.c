#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int shared_i;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void incr_num(void);
int main() {
    printf("Hello World\n");
    int ret;
    pthread_t thread_1, thread_2, thread_3;

    ret = pthread_create(&thread_1, NULL, (void*)incr_num, NULL);
    ret = pthread_create(&thread_2, NULL, (void*)incr_num, NULL);
    ret = pthread_create(&thread_3, NULL, (void*)incr_num, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);

    printf("shared_i: %d\n", shared_i);
    
    return 0;
}

void incr_num(void) {
    printf("Enter thread\n");
    int i = 0;
    for(i = 0; i < 100000; i++) {
        if (pthread_mutex_lock(&mutex) != 0) {
            printf("Lock failed.\n");
            exit(EXIT_FAILURE);
        }
        shared_i++;
        if (pthread_mutex_unlock(&mutex) != 0) {
            printf("Unlock failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("Leave thread\n");
}

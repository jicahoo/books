#include <stdio.h>
#include <stdlib.h>

int global_int=10;
main() {
    int i;
    int a[1000];
    printf("The stack top is near %p\n", &i);
    int j;
    printf("The stack top is near %p\n", &j);
    printf("The data segment is near: %p\n", &global_int);
    int *p1 = malloc(10000*sizeof(int));
    printf("The heap is near: %p\n", &p1);
    //TODO: the address of text segement.

    return 0;
}

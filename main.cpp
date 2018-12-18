#include <stdlib.h>
#include "mbed.h"
#include "mbed_mem_trace.h"

#define PLENGTH 100

char **p;

void alloc_task_main() {
    int i = 0, size;
    while (i < PLENGTH) {
        size = rand() % 10000;
        p[i] = (char *)malloc(size);
        for (int j = 0; j < size; j++)
            p[i][j] = i % 256;
        i++;
        wait_ms(rand() % 1000);
    }
}

void free_task_main() {
    int i = 0;
    while (i < PLENGTH) {
        if (p[i] != 0)
            free(p[i++]);
        wait_ms(rand() % 1000);
    }
}

int main() {
    mbed_mem_trace_set_callback(mbed_mem_trace_default_callback);

    srand(10);

    p = (char **)calloc(sizeof(char *), PLENGTH);

    Thread task_alloc, task_free;

    task_alloc.start(alloc_task_main);
    task_free.start(free_task_main);

    task_alloc.join();
    task_free.join();
}


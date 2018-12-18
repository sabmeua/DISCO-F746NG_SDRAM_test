#include <stdlib.h>
#include "mbed.h"
#include "mbed_mem_trace.h"

int main() {
    mbed_mem_trace_set_callback(mbed_mem_trace_default_callback);

    char *p[10];
    for (int i = 0; i < 10; i++) {
        p[i] = (char *)malloc(1 * 1024 * 1024);
    }

    for (int i = 0; i < 7; i++) {
        free(p[i]);
    }
}


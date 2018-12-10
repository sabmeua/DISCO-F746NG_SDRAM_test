#include <stdlib.h>
#include "mbed.h"
#include "mbed_mem_trace.h"

int main() {
    mbed_mem_trace_set_callback(mbed_mem_trace_default_callback);
    while (true) {
        void *p = malloc(50);
        wait(0.5);
        free(p);
    }
}


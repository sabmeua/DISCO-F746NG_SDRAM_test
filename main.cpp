#include <stdlib.h>
#include "mbed.h"
#include "mbed_mem_trace.h"
#include "stm32746g_discovery_sdram.h"

#define SDRAM_BASE 0xC0000000
#define SDRAM_SIZE 8 * 1024 * 1024

#if defined(TARGET_DISCO_F746NG) && defined(TOOLCHAIN_GCC_ARM)
extern "C" caddr_t _sbrk(int incr) {
    static unsigned char isSdramInitialized = 0;

    static unsigned char* heap = (unsigned char*)SDRAM_BASE;
    unsigned char* prev_heap = heap;
    unsigned char* new_heap = heap + incr;

    if (isSdramInitialized == 0) {
        BSP_SDRAM_Init();
        isSdramInitialized = 1;
    }

    if (new_heap >= (unsigned char*)(SDRAM_BASE + SDRAM_SIZE)) {
        return (caddr_t)-1;
    }

    heap = new_heap;
    return (caddr_t) prev_heap;
}
#endif

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


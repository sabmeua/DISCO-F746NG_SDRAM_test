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

        /**
         * Allow unaligned access in SDRAM by configure MPU
         * -- http://www.keil.com/support/docs/3777.htm
         */
        MPU_Region_InitTypeDef MPU_InitStruct;

        /* Disable the MPU */
        HAL_MPU_Disable();

        /* Configure the MPU attributes for SDRAM */
        MPU_InitStruct.Enable = MPU_REGION_ENABLE;
        MPU_InitStruct.BaseAddress = 0xC0000000;
        MPU_InitStruct.Size = MPU_REGION_SIZE_8MB;
        MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
        MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
        MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
        MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
        MPU_InitStruct.Number = MPU_REGION_NUMBER0;
        MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
        MPU_InitStruct.SubRegionDisable = 0x00;
        MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

        HAL_MPU_ConfigRegion(&MPU_InitStruct);

        /* Enable the MPU */
        HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

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


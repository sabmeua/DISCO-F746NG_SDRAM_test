#!/bin/bash

mbed export -i GCC_ARM
LINKER_SCRIPT=./STM32F746xG_ext_sdram.ld make


# DISCO-F746NG_SDRAM_test

This is a sample of [heap_ext_DISCO_F746NG](https://github.com/sabmeua/heap_ext_DISCO_F746NG) library.

# How to run

```
mbed import https://github.com/sabmeua/DISCO-F746NG_SDRAM_test.git
mbed target DISCO_F746NG
mbed toolchain GCC_ARM
mbed compile
```

And write the bin file to DISCO_F746NG board and run.
Then, the heap allocation log will be output like below.

```
#c:0xc0000008;0x800067f-4;100
#m:0xc00005a8;0x800505f-4096
#m:0xc00015b0;0x800505f-4096
#m:0xc00025b8;0x80005a1-7444
#m:0xc00042d0;0x80005a1-8937
#f:0x0;0x80005f5-0xc00025b8
#f:0x0;0x80005f5-0xc00042d0
#m:0xc00025b8;0x80005a1-193
#m:0xc0002680;0x80005a1-7642
#f:0x0;0x80005f5-0xc00025b8
#f:0x0;0x80005f5-0xc0002680
#m:0xc00025b8;0x80005a1-855
#m:0xc0002918;0x80005a1-6581
#f:0x0;0x80005f5-0xc00025b8
#f:0x0;0x80005f5-0xc0002918
#m:0xc00025b8;0x80005a1-3197
.
.
.
```

You can see that the address 0xc0000000 area is allocated.

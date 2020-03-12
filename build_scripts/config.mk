# Make sure to adjust those to your paths
#GCC_TOOLCHAIN=/opt/gcc-arm-none-eabi-7-2018-q2-update/bin
#LIB_GCC=/opt/gcc-arm-none-eabi-7-2018-q2-update/lib/gcc/arm-none-eabi/7.3.1/libgcc.a
GCC_TOOLCHAIN=/opt/gcc-arm-none-eabi-9-2019-q4-major/bin
LIB_GCC=/opt/gcc-arm-none-eabi-9-2019-q4-major/lib/gcc/arm-none-eabi/9.2.1/libgcc.a
LIB_SUPCPP=/opt/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/lib/libsupc++_nano.a
UPLOAD_DEV=/dev/ttyUSB0
DEP_DIR = .deps
OUTPUT_PATH= bin
INC_PATHS += -I inc

CC=$(GCC_TOOLCHAIN)/arm-none-eabi-gcc
CXX=$(GCC_TOOLCHAIN)/arm-none-eabi-g++
LINK=$(GCC_TOOLCHAIN)/arm-none-eabi-ld
OBJCOPY=$(GCC_TOOLCHAIN)/arm-none-eabi-objcopy
SIZE=$(GCC_TOOLCHAIN)/arm-none-eabi-size
AR=$(GCC_TOOLCHAIN)/arm-none-eabi-ar
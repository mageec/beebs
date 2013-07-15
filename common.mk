PLATFORMCODE=../../lowpower-framework/platformcode

VERIFY ?= 0
ifeq ($(VERIFY), 1)
	FLAGS += -g -DVERIFY
endif

FLAGS += -m32

x86_CC=gcc
x86_FLAGS += $(FLAGS) -DX86
x86_SRC += $(PLATFORMCODE)/jrand.c

arm_CC=arm-none-eabi-gcc
arm_FLAGS += $(FLAGS) -DARM
arm_FLAGS += -T$(PLATFORMCODE)/stm32vl_flash.ld
arm_FLAGS += -mcpu=cortex-m3 -mthumb
arm_FLAGS += -I$(PLATFORMCODE)
arm_SRC += $(PLATFORMCODE)/{stm32f100,sbrk,exit}.c

all: x86_ arm_

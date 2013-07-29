PLATFORMCODE=../platformcode

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	FLAGS += -g
endif

FLAGS += -std=c99 -I$(PLATFORMCODE)

x86_CC=gcc
x86_FLAGS += $(FLAGS) -DX86 -m32
x86_SRC += $(PLATFORMCODE)/{jrand,platformcode}.c

arm_CC=arm-none-eabi-gcc
arm_FLAGS += $(FLAGS) -DARM
arm_FLAGS += -T$(PLATFORMCODE)/stm32vl_flash.ld
arm_FLAGS += -mcpu=cortex-m3 -mthumb
arm_SRC += $(PLATFORMCODE)/{exit,jrand,platformcode,sbrk}.c

all: x86_ arm_

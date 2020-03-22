#
# Makefile
#
CC = arm-fsl-linux-gnueabi-gcc
LVGL_DIR ?= ${shell pwd}
CFLAGS ?=   -Wshadow -Wundef  -O3 -g0 -I$(LVGL_DIR)/
LDFLAGS ?= -lpthread
BIN = aui
OBJ_DIR = obj

#Collect the files to compile
MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
#include $(LVGL_DIR)/lv_examples/lv_examples.mk
include $(LVGL_DIR)/lv_lib_lodepng/lodepng.mk
include $(LVGL_DIR)/component/component.mk

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

#$(warning $(CFLAGS))
## MAINOBJ -> OBJFILES

all: default

%.o: %.c
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $@"
    
default: $(AOBJS) $(COBJS) $(MAINOBJ)
	@$(CC) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)
	
## @if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;\
## mv *.o $(OBJ_DIR)


clean: 
	rm -f $(BIN) $(AOBJS) $(COBJS) $(MAINOBJ)

mv:
	rm -rf $(BIN) $(OBJ_DIR)

## @if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;\
## mv *.o $(OBJ_DIR)
	

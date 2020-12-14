#==========================================================
#   File:   Makefile for STM8
#   Date:   2011-01-22
#==========================================================

MCU = STM8S103
SRC_C += main.c
SRC_C += ../pts.c

#----------------------------------------------------------
STPROG = "C:/Program Files (x86)/STMicroelectronics/st_toolset/stvp/STVP_CmdLine.exe"

CC_PATH = "C:/Tools/SDCC/bin/"
#CC_PATH = "D:/Tools/SDCC/bin/"
CC = $(CC_PATH)sdcc.exe
CL = $(CC_PATH)sdcc.exe
IHX = $(CC_PATH)packihx

#LIB_PATH = $(CC_PATH)../lib/stm8
#LIBS = $(LIB_PATH)/stm8.lib

INCLUDES += -I.
INCLUDES += -I..
#INCLUDES += -Istdlib.stm8/inc
INCLUDES += -Istm8.lib/Include

VPATH  = .
VPATH += stdlib.stm8/src
VPATH += ../
VPATH += build/

#----------------------------------------------------------
FLAGS_C  = -mstm8
FLAGS_C += -D$(MCU)
#FLAGS_C += -obuild/
FLAGS_C += --std-c99
FLAGS_C += --opt-code-size
FLAGS_C += --model-medium
#FLAGS_C += --debug

FLAGS_L += -obuild/
FLAGS_L += -mstm8 
FLAGS_L += -pstm8s003
FLAGS_L += -Wl-m -Wl-j


#----------------------------------------------------------


all:
	@make build
	@echo =======================================
	@echo = Use \"make flash\" to write firmware. =
	@echo =======================================

build: main.hex size

mcu_all: all mcu_program mcu_restart

%.ihx: $(SRC_C:%.c=%.rel)
	@echo '- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -'
	@echo .linking: $@ 
	@ $(CL) $(FLAGS_L) $(addprefix build/, $(notdir $(SRC_C:%.c=%.rel)))
	@ $(CL) $(FLAGS_L) --out-fmt-elf $(addprefix build/, $(notdir $(SRC_C:%.c=%.rel)))
	
$(SRC_C:%.c=%.rel): %.rel: %.c
	@$(CC) $(FLAGS_C) $(INCLUDES) -obuild/ -c $(@:%.rel=%.c)

size: build/main.elf
	@echo '-----------------------------------------------------------'
	#@ size -B $^
	@readelf -S $^

main.hex:  build/main.ihx
	$(IHX) $< > build/main.hex

	
clean:
	@echo '-----------------------------------------------------------'
	@rm -f build/*.*

flash: main.hex
	@$(STPROG) -BoardName=ST-LINK -Port=USB -ProgMode=SWIM -Device=STM8S103F3 -no_loop -no_log -FileProg=build/main.hex


mcu_restart:
	@C:\Program Files\STMicroelectronics\st_toolset\stvd/gdb7.exe --quiet --command=mcu/stm8s003k3.ini
	
.PHONY : all clean program size
TARGET = TETRIS
OBJS = main.o common.o graphics.o framebuffer.o block.o hanzi.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspgu -lpsppower -lpng -lpsprtc -lz -lm 
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = TETRIS
PSP_EBOOT_ICON  = icon.png
//PSP_EBOOT_PIC1  = pic.png

PSP_FW_VERSION = 371
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak 



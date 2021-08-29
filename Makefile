LIBHEADERS = -I./Firmware/CMSIS -I./Firmware/CMSIS/GD/GD32F10x/Include -I./Firmware/GD32F10x_standard_peripheral/Include \
-I./Firmware/
LIBSRC = -I./Firmware/GD32F10x_standard_peripheral/Source
DEFINES = -DGD32F10X_XD
CFLAGS = -Og -mcpu=cortex-m3 -mthumb -Wall -g -Wa,-a,-ad $(LIBHEADERS) $(LIBSRC) $(DEFINES)
LINKERFLAGS = -fdata-sections -ffunction-sections -lc -lm -lnosys -specs=nano.specs -Wl,--gc-sections
PREF = arm-none-eabi-
COMPILER = gcc
BUILDDIR = output
SRCDIR = src
INCLDIR = include

$(BUILDDIR)/output.elf : $(BUILDDIR)/main.o linker.ld $(BUILDDIR)/startup.o $(BUILDDIR)/utime.o $(BUILDDIR)/ubutton.o
	$(PREF)$(COMPILER) $(CFLAGS) $(LINKERFLAGS) $(BUILDDIR)/main.o $(BUILDDIR)/ubutton.o $(BUILDDIR)/utime.o $(BUILDDIR)/startup.o -T linker.ld -o output/output.elf

$(BUILDDIR)/main.o : main.c
	$(PREF)$(COMPILER) -c $(CFLAGS) $(LINKERFLAGS) main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/startup.o : startup.s
	$(PREF)$(COMPILER) -c $(CFLAGS) $(LINKERFLAGS) startup.s -o $(BUILDDIR)/startup.o

$(BUILDDIR)/utime.o : $(SRCDIR)/utime.c $(INCLDIR)/utime.h
	$(PREF)$(COMPILER) -c $(CFLAGS) $(LINKERFLAGS) $(SRCDIR)/utime.c -o $(BUILDDIR)/utime.o

$(BUILDDIR)/ubutton.o : $(SRCDIR)/ubutton.c $(INCLDIR)/ubutton.h $(BUILDDIR)/utime.o
	$(PREF)$(COMPILER) -c $(CFLAGS) $(LINKERFLAGS) $(SRCDIR)/ubutton.c -o $(BUILDDIR)/ubutton.o


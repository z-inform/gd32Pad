LIBHEADERS = -I./Firmware/CMSIS -I./Firmware/CMSIS/GD/GD32F10x/Include -I./Firmware/GD32F10x_standard_peripheral/Include \
-I./Firmware/
LIB = ./Firmware/GD32F10x_standard_peripheral
DEFINES = -DGD32F10X_XD
CFLAGS = -Og -mcpu=cortex-m3 -mthumb -Wall -g -Wa,-a,-ad $(LIBHEADERS) -I$(LIB) $(DEFINES)
LINKERFLAGS = -fdata-sections -ffunction-sections -lc -lm -lnosys -specs=nano.specs -Wl,--gc-sections
PREF = arm-none-eabi-
COMPILER = gcc
BUILDDIR = output
SRCDIR = src
INCLDIR = include
LIBTARGETS = gd32f10x_rcu.o gd32f10x_gpio.o gd32f10x_misc.o gd32f10x_timer.o

FINALOBJ := main.o startup.o utime.o ubutton.o $(LIBTARGETS)
FINALOBJ := $(addprefix $(BUILDDIR)/, $(FINALOBJ))


$(BUILDDIR)/output.elf : $(FINALOBJ) linker.ld
	$(PREF)$(COMPILER) $(CFLAGS) $(LINKERFLAGS) $(FINALOBJ) -T linker.ld -o output/output.elf

$(BUILDDIR)/main.o : main.c
	$(PREF)$(COMPILER) -c $(CFLAGS) main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/startup.o : startup.s
	$(PREF)$(COMPILER) -c $(CFLAGS) startup.s -o $(BUILDDIR)/startup.o

$(BUILDDIR)/utime.o : $(SRCDIR)/utime.c $(INCLDIR)/utime.h
	$(PREF)$(COMPILER) -c $(CFLAGS) $(SRCDIR)/utime.c -o $(BUILDDIR)/utime.o

$(BUILDDIR)/ubutton.o : $(SRCDIR)/ubutton.c $(INCLDIR)/ubutton.h $(BUILDDIR)/utime.o
	$(PREF)$(COMPILER) -c $(CFLAGS) $(SRCDIR)/ubutton.c -o $(BUILDDIR)/ubutton.o

$(addprefix $(BUILDDIR)/, $(LIBTARGETS)) : $(BUILDDIR)/%.o : $(LIB)/Source/%.c $(LIB)/Include/%.h
	$(PREF)$(COMPILER) -c $(CFLAGS) $< -o $@

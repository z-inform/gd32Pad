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

LIBTARGETS = gd32f10x_rcu.o gd32f10x_gpio.o gd32f10x_misc.o gd32f10x_timer.o gd32f10x_adc.o gd32f10x_dma.o

ULIBTARGETS = utime.o ubutton.o uadc.o

FINALOBJ := main.o startup.o $(ULIBTARGETS) $(LIBTARGETS)
FINALOBJ := $(addprefix $(BUILDDIR)/, $(FINALOBJ))


$(BUILDDIR)/output.elf : $(FINALOBJ) linker.ld
	$(PREF)$(COMPILER) $(CFLAGS) $(LINKERFLAGS) $(FINALOBJ) -T linker.ld -o output/output.elf

$(BUILDDIR)/main.o : main.c $(INCLDIR)/$(addsuffix .h, $(basename $(ULIBATRGETS)))
	$(PREF)$(COMPILER) -c $(CFLAGS) main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/startup.o : startup.s
	$(PREF)$(COMPILER) -c $(CFLAGS) startup.s -o $(BUILDDIR)/startup.o

$(addprefix $(BUILDDIR)/, $(ULIBTARGETS)) : $(BUILDDIR)/%.o : $(SRCDIR)/%.c $(INCLDIR)/%.h
	$(PREF)$(COMPILER) -c $(CFLAGS) $< -o $@

$(addprefix $(BUILDDIR)/, $(LIBTARGETS)) : $(BUILDDIR)/%.o : $(LIB)/Source/%.c $(LIB)/Include/%.h
	$(PREF)$(COMPILER) -c $(CFLAGS) $< -o $@

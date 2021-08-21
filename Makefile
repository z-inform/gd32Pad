LIBHEADERS = -I./Firmware/CMSIS -I./Firmware/CMSIS/GD/GD32F10x/Include -I./Firmware/GD32F10x_standard_peripheral/Include \
-I./Firmware/
LIBSRC = -I./Firmware/GD32F10x_standard_peripheral/Source
DEFINES = -DGD32F10X_XD
CFLAGS = -Og -mcpu=cortex-m3 -mthumb -Wall -g -Wa,-a,-ad $(LIBHEADERS) $(LIBSRC) $(DEFINES)
LINKERFLAGS = -fdata-sections -ffunction-sections -lc -lm -lnosys -specs=nano.specs -Wl,-Map=$(BUILDDIR)/output.map,--cref \
-Wl,--gc-sections
PREF = arm-none-eabi-
BUILDDIR = output


$(BUILDDIR)/output.elf : $(BUILDDIR)/main.o linker.ld $(BUILDDIR)/startup.o
	$(PREF)gcc $(CFLAGS) $(LINKERFLAGS) $(BUILDDIR)/main.o $(BUILDDIR)/startup.o -T linker.ld -o output/output.elf


$(BUILDDIR)/main.o : main.c
	$(PREF)gcc -c $(CFLAGS) $(LINKERFLAGS) main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/startup.o : startup.s
	$(PREF)gcc -c $(CFLAGS) $(LINKERFLAGS) startup.s -o $(BUILDDIR)/startup.o


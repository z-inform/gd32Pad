CFLAGS = -Og -mcpu=cortex-m3 -mthumb -Wall 
LINKERFLAGS = -fdata-sections -ffunction-sections -lc -lm -lnosys -specs=nano.specs
PREF = arm-none-eabi-
BUILDDIR = output


$(BUILDDIR)/output.elf : $(BUILDDIR)/main.o linker.ld $(BUILDDIR)/startup.o
	$(PREF)gcc $(LINKERFLAGS) $(BUILDDIR)/main.o $(BUILDDIR)/startup.o -T linker.ld -o output/output.elf


$(BUILDDIR)/main.o : main.c
	$(PREF)gcc -c $(CFLAGS) main.c -o $(BUILDDIR)/main.o


$(BUILDDIR)/startup.o : startup.s
	$(PREF)gcc -c $(CFLAGS) startup.s -o $(BUILDDIR)/startup.o


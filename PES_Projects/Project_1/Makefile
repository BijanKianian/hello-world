# From MCUXpresso
# FRDM Environment Makefile section.

# Syntax $: make test FRDM=1 //Default FRDM =0;
ifdef FRDM

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS_driver/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: PES_memtest.axf

# Tool invocations
PES_memtest.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="PES_memtest.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -mcpu=cortex-m0plus -mthumb -T PES_memtest_Debug.ld -o "PES_memtest.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) PES_memtest.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "PES_memtest.axf"; # arm-none-eabi-objcopy -v -O binary "PES_memtest.axf" "PES_memtest.bin" ; # checksum -p MKL25Z128xxx4 -d "PES_memtest.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets

# Linux Environment Makefile section.
else

CC=gcc
CFLAGS=-c -Wall -Werror

memtest: memtest.o help.o allocate.o free.o display.o write.o invert.o pattern.o verify.o
	$(CC) -o  memtest memtest.o help.o allocate.o free.o display.o write.o invert.o pattern.o verify.o
	$(CC) $(CFLAGS) memtest.c
help.o: help.c help.h
	$(CC) $(CFLAGS) help.c
allocate.o: allocate.c allocate.h
	$(CC) $(CFLAGS) allocate.c
free.o: free.c free.h
	$(CC) $(CFLAGS) free.c
display.o: display.c display.h
	$(CC) $(CFLAGS) display.c
write.o: write.c write.h
	$(CC) $(CFLAGS) write.c
invert.o: invert.c invert.h
	$(CC) $(CFLAGS) invert.c
pattern.o: pattern.c pattern.h
	$(CC) $(CFLAGS) pattern.c
verify.o: verify.c verify.h
	$(CC) $(CFLAGS) verify.c
test: memtest test.txt 
		./memtest<test.txt>outputFile.txt
clean:
	rm -rf *o memtest
	rm -rf outputFile.txt

endif
# Finish If Else statments. 

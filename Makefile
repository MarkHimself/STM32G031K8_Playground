
$(info $(SHELL))

CC = arm-none-eabi-gcc
ACC = arm-none-eabi-as

IDIR = include
ODIR = obj
OUT_LOC = Debug

INCDIR1 = -I"CMSIS/Include"
INCDIR2 = -I"Device/ST/STM32G0xx/Include/"
INCDIR = $(INCDIR1) $(INCDIR2)

DEBUG = -g
PROJECT_NAME = STM32G031K8_Playground
OUTPUT_EXT = elf
EXECUTABLE_WPATH = $(OUT_LOC)/$(PROJECT_NAME).$(OUTPUT_EXT)

MACH = cortex-m0plus
FPU = -mfloat-abi=soft

# COMPILER FLAGS
#C_TO_ASM = -save-temps
CFLAGS = -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0 $(DEBUG) $(INCDIR) -DSTM32G031xx -DSTM32G031K8Tx $(FPU) $(C_TO_ASM)

ASMFLAGS = -mthumb $(DEBUG) $(INCDIR) $(FPU) -mcpu=$(MACH)

# LINKING FLAGS
# LIBGCC Library for division
# $(CC) -print-libgcc-file-name		use this option to print the filepath of the LIBGCC library on your machine. Note: type into terminal. do not include in makefile.
LIBGCC = -lgcc
# MATH Library
LIBMATH = -lm

# Generate a map file
MAP = -Wl,-Map=final.map
LDFLAGS = -mcpu=$(MACH) -mthumb $(FPU) -T linker_script.ld $(MAP) -nostdlib -Wl,--start-group $(LIBMATH) $(LIBGCC) -lc -lnosys -Wl,--end-group
########################################################################################################################

all: $(EXECUTABLE_WPATH)

########################################################################################################################

# _OBJ: all the object files that need to be generated to build the binary file.
_OBJ = main.o startup.o proc_exceptions.o GPIO_Output.o GPIO_Input.o general_timers_pwm.o
OBJ_PATH = obj
OBJ = $(patsubst %,$(OBJ_PATH)/%,$(_OBJ))

# The system object (source file provided by vendor)
OBJ_SYSTEM = $(ODIR)/system_stm32g0xx.o

_ASMOBJ = exclusive_access_asm.o
ASMOBJ_PATH = obj
ASMOBJ = $(patsubst %,$(ASMOBJ_PATH)/%,$(_ASMOBJ))

# _DEPS: all the header files included inside of the "include" directory.
# DEPS: include/filename1.h include/filename2.h  etc...
_DEPS = main.h startup.h proc_exceptions.h GPIO_Output.h GPIO_Input.h general_timers_pwm.h
DEPS_PATH = include
DEPS = $(patsubst %,$(DEPS_PATH)/%,$(_DEPS))

##################### COMPILE THE EXECUTABLE #############################

$(EXECUTABLE_WPATH): $(OBJ) $(OBJ_SYSTEM)
	$(CC)  -o $@ $^ $(LDFLAGS)

##################### COMPILE THE SYSTEM SETUP #############################

_DEPS_SI = system_stm32g0xx.h stm32g031xx.h stm32g0xx.h
DEPS_PATH_SI = Device\ST\STM32G0xx\Include
DEPS_SI = $(patsubst %,$(DEPS_PATH_SI)/%,$(_DEPS_SI))

$(OBJ_SYSTEM): Device/ST/STM32G0xx/Source/Templates/system_stm32g0xx.c $(DEPS_SI)
	$(CC) $(CFLAGS) -o $@ $< -I. $(DEBUG)

#################### START OF: COMPILE EACH INDIVIDUAL SOURCE FILE ##########################

$(ODIR)/main.o: src/main.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I. $(DEBUG)

$(ODIR)/startup.o: src/startup.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I. $(DEBUG)

$(ODIR)/proc_exceptions.o: src/proc_exceptions.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I. $(DEBUG)

$(ODIR)/GPIO_Output.o: src/GPIO_Output.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I. $(DEBUG)

$(ODIR)/GPIO_Input.o: src/GPIO_Input.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I. $(DEBUG)

$(ODIR)/general_timers_pwm.o: src/general_timers_pwm.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< -I. $(DEBUG)

#################### END OF: COMPILE EACH INDIVIDUAL SOURCE FILE ##########################

clean:
	rm -f *.map *.o $(ODIR)/*.o *.i *.s $(EXECUTABLE_WPATH)


cleanw:
	del *.map *.o $(ODIR)\*.o *.i *.s $(OUT_LOC)\$(PROJECT_NAME).$(OUTPUT_EXT)

dump:
	arm-none-eabi-objdump -d Debug/$(PROJECT_NAME).elf

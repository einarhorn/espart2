# Specify directories where the various tools and libraries can be found
FS_PREFIX=/group/teaching/espractical/Freescale/

FST_PREFIX=$(FS_PREFIX)/ARM_Tools/Command_Line_Tools/

CC=$(FST_PREFIX)mwccarm
AS=$(FST_PREFIX)mwasmarm
LD=$(FST_PREFIX)mwccarm

# Set up CFLAGS to build an MQX project
INCDIRS=-i $(FS_PREFIX)/ARM_EABI_Support/ewl/EWL_C/include/ 
CFLAGS=-gccinc -proc=cortex-m4 -cwd include -enc ascii $(INCDIRS) -g -thumb -interworking -little -fp vfpv4 -O3 

# Set up the linker to build an MQX project
LDSCRIPT=bareboard_flash.lcf
LDFLAGS=-proc=cortex-m4 -thumb -nostdlib $(LDSCRIPT) -g -L$(FS_PREFIX)/ARM_EABI_Support/ewl/lib -lavender model=ewl ,print=none ,scan=none ,io=none 

# Specify the source files to be compiled here
MAIN_SOURCES=main.c vectors.c led.c button.c uart.c 
MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)

.PHONY: clean

all :
	make clean
	make main 

# Recipe to build the binary
main :  $(MAIN_OBJECTS)
	$(LD) $(LDFLAGS) $^ $(LDFLAGS) -o $@

# Recipe to make each individual object file
%.o : %.c
	$(CC) $(CFLAGS) -o "$@" -c "$<"

# Recipe to tidy up the build folder
clean:
	rm -f main
	rm -f $(MAIN_OBJECTS) 


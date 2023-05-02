# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include
LDFLAGS		= -L/opt/ti/msp430_gcc/inlcude

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf buzzer.elf 

#additional rules for files
button.elf: ${COMMON_OBJECTS} ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

buzzer.elf: ${COMMON_OBJECTS} buzzer.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: buzzer.elf
	msp430loader.sh  $^

clean: $^
	rm -f *.o *.elf

buzzer.c: buzzer.h
main.c: buzzer.h



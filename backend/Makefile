LIBRARY=libbackend.so
BUILD=release

ifeq ($(BUILD),debug)
	CFLAGS+= \
		-g \
		-fsanitize=address \
		-fsanitize=pointer-compare \
		-fsanitize=pointer-subtract \
		-fsanitize=undefined \
		-fsanitize-address-use-after-scope
endif

ifeq ($(BUILD),release)
	CFLAGS+= \
		-O3
endif

INCLUDE+= \
	-Iinclude \
	-I../colc/include \
	-I../middleend/include \
	-I../frontend/include \

SRC+= \
	src/asm/riscv/machine.c \
	src/asm/riscv/asm_generator.c \
	src/asm/riscv/asm_instruction.c \
	src/asm/riscv/asm_line.c \
	src/asm/riscv/register.c \

OBJECTS := $(SRC:.c=.o)

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar crs $@ $^

%.o:%.c
	gcc -c $(CFLAGS) $(INCLUDE) -o $@ $<

clean: 
	rm -f $(LIBRARY) $(OBJECTS)

.PHONY: all clean

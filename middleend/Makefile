LIBRARY=libmiddleend.so
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
	-I../frontend/include \
	-I../colc/include

SRC+= \
	src/cfg.c \
	src/cfg_node.c \
	src/optree.c \

OBJECTS := $(SRC:.c=.o)

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar crs $@ $^

%.o:%.c
	gcc -c $(CFLAGS) $(INCLUDE) -o $@ $<

clean: 
	rm -f $(LIBRARY) $(OBJECTS)

.PHONY: all clean
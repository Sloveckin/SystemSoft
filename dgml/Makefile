LIBRARY=libdgml.a
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

INCLUDE+=\
	-I../colc/include\
	-I../frontend/include\
	-Iinclude

LPATH+=\
  -L../front-end\

LIBS+=\
  -lfrontend

OBJECTS+=\
	src/from_ast.o

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

%.o:%.c
	gcc -c $(CFLAGS) $(INCLUDE) $(LPATH) -o $@ $^

clean:
	rm -f $(LIBRARY) $(OBJECTS)
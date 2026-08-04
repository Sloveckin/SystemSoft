LIBRARY=libuser_input.a
BUILD=release

ifeq ($(BUILD),debug)
	CFLAGS+=\
		-g\
		-fsanitize=address \
		-fsanitize=pointer-compare \
		-fsanitize=pointer-subtract \
		-fsanitize=undefined \
		-fsanitize-address-use-after-scope
endif

ifeq ($(BUILD),release)
	CFLAGS+=\
		-O3
endif

INCLUDE+=\
	-Iinclude\
	-I../colc/include

LDPATH+=\
	-L../colc/

LIBS+=\
	-lcolc

OBJECTS+=\
	src/user_input.o


all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

%.o:%.c
	gcc $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean:
	rm -f $(OBJECTS) $(LIBRARY)




#build:
#	gcc $(CFLAGS) $(INCLUDE) $(LDPATH) $(LIBS) src/user_input.c
#	ar rcs libuser_input.a user_input.o
#	rm *.o

#clean:
#	rm -f *.o *.a

#rebuild: clean build

#.PHONY:	rebuild

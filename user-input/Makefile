CFLAGS+=\
  -g\
	-c

INCLUDE+=\
	-Iinclude\
	-I../colc/include

LDPATH+=\
	-L../colc/

LIBS+=\
	-lcolc

build:
	gcc $(CFLAGS) $(INCLUDE) $(LDPATH) $(LIBS) src/user_input.c
	ar rcs libuser_input.a user_input.o
	rm *.o

clean:
	rm -f *.o *.a

rebuild: clean build

.PHONY:	rebuild

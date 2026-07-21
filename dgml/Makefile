INCLUDE+=\
	-I../colc/include\
	-I../front-end/include\
	-Iinclude

SRC+=\
	src/ast.c

OBJ+=\
	ast.o

build:
	gcc $(INCLUDE) $(SRC) -c
	ar rcs libdgml.a $(OBJ)
	rm -f *.o

clean:
	rm -rf *.o libdgml.a

rebulid: clean build

.PHONY:	clean build

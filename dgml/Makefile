CFLAGS+=\
  -g

INCLUDE+=\
	-I../colc/include\
	-I../frontend/include\
	-Iinclude

LPATH+=\
  -L../front-end\

LIBS+=\
  -lfrontend

SRC+=\
	src/from_ast.c

OBJ+=\
	from_ast.o

build:
	gcc $(CFLAGS) $(INCLUDE) $(LPATH) $(SRC) $(LIBS) -c
	ar rcs libdgml.a $(OBJ)
	rm -f *.o

clean:
	rm -rf *.o libdgml.a

rebulid: clean build

.PHONY:	clean build

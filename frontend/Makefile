CFLAGS+=\
	-g \

INCLUDE+=\
	-Igenerated\
	-Iinclude\
	-I../colc/include

SRC+=\
	src/ast/ast_node_type.c\
	src/ast/ast_node.c\
	src/parser/parser.c

LIBS_PATH+=\
	-L../colc/

LIBS+=\
	-lcolc\

build: flex bison
	gcc $(CFLAGS) $(INCLUDE) generated/parser.tab.c generated/lexer.yy.c $(SRC) -c
	ar rcs libfrontend.a lexer.yy.o parser.tab.o ast_node.o parser.o ast_node_type.o
	rm -f *.o 

flex:
	mkdir -p generated
	flex -o generated/lexer.yy.c lexer.lx

bison:
	mkdir -p generated
	bison -d -o generated/parser.tab.c parser.y

clean:
	rm -rf generated *.o *.a

.PHONY: clean build

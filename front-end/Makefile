CFLAGS+=\
	-g \
	-fsanitize=leak \
	-fsanitize=address \
	-fsanitize=pointer-compare \
	-fsanitize=pointer-subtract \
	-fsanitize=undefined \
	-fsanitize-address-use-after-scope \
	-Wextra \
	-Wall \

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
	gcc -fPIC $(CFLAGS) $(INCLUDE) generated/parser.tab.c generated/lexer.yy.c $(SRC) -c
	gcc --shared lexer.yy.o parser.tab.o ast_node.o parser.o ast_node_type.o $(LIBS_PATH) $(LIBS) -o libparser.so
	rm -f *.o

flex:
	mkdir -p generated
	flex -o generated/lexer.yy.c lexer.lx

bison:
	mkdir -p generated
	bison -d -o generated/parser.tab.c parser.y

clean:
	rm -rf generated libparser.so

.PHONY: clean build

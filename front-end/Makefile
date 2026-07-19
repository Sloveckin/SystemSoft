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
    src/ast/ast_node.c\
    src/parser/parser.c

LIBS_PATH+=\
    -L../colc/

LIBS+=\
    -lcolc\

build:
	gcc -fPIC $(CFLAGS) $(INCLUDE)  generated/parser.tab.c generated/lexer.yy.c $(SRC) -c
	gcc --shared  lexer.yy.o parser.tab.o ast_node.o parser.o $(LIBS_PATH) $(LIBS) -o libparser.so
	rm -f *.o

clean:
	rm -f libparser.so

.PHONY: clean build

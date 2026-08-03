LIBRARY=libfrontend.a
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

INCLUDE+= \
	-Igenerated \
	-Iinclude \
	-I../colc/include

SRC+= \
	src/ast/ast_node_type.c \
	src/ast/ast_node.c \
	src/parser/parser.c \
	generated/parser.tab.c \
	generated/lexer.yy.c \

OBJECTS+= \
	src/ast/ast_node_type.o \
	src/ast/ast_node.o \
	src/parser/parser.o \
	generated/parser.tab.o \
	generated/lexer.yy.o


all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

%.o:%.c
	gcc -c $(CFLAGS) $(INCLUDE) -o $@ $<

src/parser/parser.o: generated/parser.tab.h

generated/parser.tab.c generated/parser.tab.h: parser.y
	mkdir -p generated
	bison -d -o generated/parser.tab.c parser.y

generated/lexer.yy.c generated/lexer.h: lexer.lx generated/parser.tab.h
	mkdir -p generated
	flex -o generated/lexer.yy.c --header-file=generated/lexer.h lexer.lx

clean:
	rm -rf $(LIBRARY) $(OBJECTS) generated parser.tab.c parser.tab.h lexer.yy.c lexer.h

.PHONY:	all clean
build: pre_generate_parser
	flex -o lexer.yy.c lexer.lx
	rm -f *.o

pre_generate_parser:
	bison -H parser.y

clean:
	rm -f lexer parser.tab.c parser.tab.h lexer.yy.c *.o *.so

.PHONY: clean lexer

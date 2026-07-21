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
    -Werror

INCLUDE+=\
    -Ifront-end/include\
    -Icolc/include\
    -Iuser-input/include\
    -Idgml/include

LDPATH+=\
    -Lfront-end\
    -Luser-input\
    -Lcolc\
    -Ldgml

LIBS+=\
    -lparser\
    -luser_input\
    -lcolc\
    -ldgml

build:
	gcc $(CFLAGS) $(INCLUDE) $(LDPATH) main.c $(LIBS) -o main

clean:
	rm -f main

rebuild: clean build

.PHONY: rebuild

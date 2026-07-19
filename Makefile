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

build:
	gcc $(CFLAGS) -Ifront-end/include -Icolc/include -Lfront-end main.c -lparser -o main

clean:
	rm -f main

rebuild: clean build

.PHONY: rebuild

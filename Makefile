CFLAGS+=\
	-g \
    #-fsanitize=leak \
    #-fsanitize=address \
    #-fsanitize=pointer-compare \
    #-fsanitize=pointer-subtract \
    #-fsanitize=undefined \
    #-fsanitize-address-use-after-scope \
    #-Wextra \
    #-Wall \
    #-Werror

INCLUDE+=\
    -Ifront-end/include\
    -Icolc/include\
    -Iuser-input/include\
    -Idgml/include\
    -Ibackend/include

LDPATH+=\
    -Lfront-end\
    -Luser-input\
    -Lcolc\
    -Ldgml\
    -Lbackend

LIBS+=\
    -lparser\
    -luser_input\
    -lcolc\
    -ldgml\
    -lbackend

build:
	gcc $(CFLAGS) $(INCLUDE) $(LDPATH) main.c $(LIBS) -o main

clean:
	rm -f main

rebuild: clean build

.PHONY: rebuild

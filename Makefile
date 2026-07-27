CFLAGS+=\
	-g

INCLUDE+=\
    -Ifrontend/include\
    -Icolc/include\
    -Iuser-input/include\
    -Idgml/include\
    -Ibackend/include

LDPATH+=\
    -Ldgml\
    -Lfrontend\
    -Luser-input\
    -Lcolc\
    -Lbackend

LIBS+=\
    -ldgml\
    -lfrontend\
    -luser_input\
    -lcolc\
    -lbackend

build:
	gcc $(CFLAGS) $(INCLUDE) $(LDPATH) main.c $(LIBS) -o main

clean:
	rm -f main

rebuild: clean build

.PHONY: rebuild

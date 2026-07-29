APP_NAME=clake

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
	gcc $(CFLAGS) $(INCLUDE) $(LDPATH) main.c $(LIBS) -o $(APP_NAME)

clean:
	rm -f $(APP_NAME)

rebuild: clean build

.PHONY: rebuild

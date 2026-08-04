BINARY=clake
BUILD=release

ifeq ($(BUILD),debug)
	CFLAGS+= \
		-g \
		-fsanitize=address \
		-fsanitize=pointer-compare \
		-fsanitize=pointer-subtract \
		-fsanitize=undefined \
		-fsanitize-address-use-after-scope
endif

ifeq ($(BUILD),release)
	CFLAGS+= \
		-O3
endif

INCLUDE+= \
	-Ifrontend/include \
	-Icolc/include \
	-Iuser-input/include \
	-Idgml/include \

LDPATH+= \
	-Ldgml \
	-Lfrontend \
	-Luser-input \
	-Lcolc \

LIBS+= \
	-ldgml \
	-lfrontend \
	-luser_input \
	-lcolc \

OBJECTS+=\
	main.o\

all: library $(BINARY)

library:
	$(MAKE) -C frontend BUILD=$(BUILD)
	$(MAKE) -C user-input BUILD=$(BUILD)
	$(MAKE) -C dgml BUILD=$(BUILD)

$(BINARY): $(OBJECTS)
	gcc $(CFLAGS) -o $@ $^ $(LDPATH) $(LIBS)

%.o:%.c
	gcc -c $(INCLUDE) $(CFLAGS) -o $@ $^

clean:
	$(MAKE) -C frontend clean
	$(MAKE) -C user-input clean
	$(MAKE) -C dgml clean
	rm -f $(BINARY) $(OBJECTS)

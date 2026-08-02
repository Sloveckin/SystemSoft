LIBRARY=libbackend.a
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

INCLUDE+=\
	-Iinclude/\
	-I../colc/include\
	-I../frontend/include

LDPATH+=\
	-L../frontend\
	-L../colc

LIBS+=\
	-lfrontend

SRC+=\
	src/cfg/control_flow_graph_node.c\
	src/optree/operation_tree_node.c\
	src/semantic_analysis/semantic_analysis.c\
	src/semantic_analysis/semantic_anlysis_context.c\
	src/error/error.c\
	src/type/type.c\
	src/common/function.c\
	src/common/signature.c\
	src/common/variable.c\
	src/program.c

OBJECTS+=\
  	src/cfg/control_flow_graph_node.o\
	src/optree/operation_tree_node.o\
	src/semantic_analysis/semantic_analysis.o\
	src/semantic_analysis/semantic_anlysis_context.o\
	src/error/error.o\
	src/type/type.o\
	src/common/function.o\
	src/common/signature.o\
	src/common/variable.o\
	src/program.o

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

%.o:%.c
	gcc $(INCLUDE) -c $^ -o $@

clean:
	rm -f $(OBJECTS) $(LIBRARY)

#build:
#	gcc $(CFLAGS) $(INCLUDE) $(SRC) $(LDPATH) $(LIBS) -c
#	ar rcs libbackend.a $(OBJ)
#	rm -rf *.o

#clean:
#	rm -f *.o *.a

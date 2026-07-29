CFLAGS+=\
  	-c\
	-g

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

OBJ+=\
  program.o\
	semantic_analysis.o\
	type.o\
	semantic_anlysis_context.o\
	function.o\
	control_flow_graph_node.o\
	operation_tree_node.o\
	error.o\
	signature.o\
	variable.o\

build:
	gcc $(CFLAGS) $(INCLUDE) $(SRC) $(LDPATH) $(LIBS) -c
	ar rcs libbackend.a $(OBJ)
	rm -rf *.o

clean:
	rm -f *.o *.a

.PHONY: clean build

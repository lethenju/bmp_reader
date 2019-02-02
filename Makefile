all: output

OBJECTS_DIR=objects
SRC_DIR=src
EXE_NAME=output

output: main.o
	gcc -o $(EXE_NAME) $(OBJECTS_DIR)/* -lm

main.o: $(SRC_DIR)/main.c 
	gcc -ggdb -c $(SRC_DIR)/main.c -o  $(OBJECTS_DIR)/main.o

make clean:
	rm  $(OBJECTS_DIR)/* learn

make rebuild: clean all

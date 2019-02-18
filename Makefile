all: output

OBJECTS_DIR=objects
SRC_DIR=src
EXE_NAME=output


all: $(SRC_DIR)/main.c  $(SRC_DIR)/bmp_reader.c 
	gcc -g $(SRC_DIR)/*.c -lm -o $(EXE_NAME)

make clean:
	rm  $(OBJECTS_DIR)/* learn

make rebuild: clean all

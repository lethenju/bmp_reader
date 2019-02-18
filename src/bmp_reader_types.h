#ifndef BMP_READER_TYPES_H
#define BMP_READER_TYPES_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 100
#define HEIGHT 50
#define MAXBUF 10000000



typedef struct {
    int r; //RED
    int g; //GREEN
    int b; //BLUE
} pixel;

typedef struct {
    unsigned long size;
    unsigned long width;
    unsigned long height;
    int offset;
    pixel** image_ptr;
    char* buf;
    char* ptr; 
    FILE* fd;
} bmp_reader_context;

#endif
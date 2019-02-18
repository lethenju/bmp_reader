#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define WIDTH 100
#define HEIGHT 50
#define MAXBUF 10000000

typedef struct pixel_t {
    int r; //RED
    int g; //GREEN
    int b; //BLUE
} pixel;

typedef struct bmp_reader_context_t {
    unsigned long size;
    unsigned long width;
    unsigned long height;
    pixel** image_ptr;
    char* buf;
    char* ptr; 
    FILE* fd;
} bmp_reader_context;


char ascii_tran[10] = {' ','.',
                        ':','-',
                        '+','=',
                        '*','o',
                        'O','M'};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage : exe FILE\n");
        return -1;
    }
    bmp_reader_context *ctx = (bmp_reader_context*) malloc(sizeof(bmp_reader_context));

    ctx->fd = fopen(argv[1],"rb");
    
    ctx->buf =  (char*) malloc(MAXBUF*sizeof(char));
    ctx->ptr = ctx->buf;

    char* buf = ctx->buf; // Simply put them locally in the function
    char* ptr = ctx->ptr;

    fread(buf,MAXBUF,1,ctx->fd);    
    int i;  
    ptr+=2; // Skipping magic number
    memcpy(&(ctx->size),ptr,4);
    ptr+=4;
    printf("Size : %lu\n",ctx->size);
    ptr+=4;
    printf("Offset : %d\n", *ptr);
    int offset = *ptr;
    ptr+=4;


    // DIB HEADER PARSING
    unsigned long sizeDIB = 0;
    
    memcpy(&sizeDIB,ptr,4);
    ptr+=4;
    memcpy(&(ctx->width),ptr,4);
    ptr+=4;    
    memcpy(&(ctx->height),ptr,4);
    ptr+=4;
    
    printf("Size DIB header : %lu\n",sizeDIB);
    printf("width : %lu\n",ctx->width);
    printf("height : %lu\n",ctx->height);

    ptr = buf+offset;
    float x,y;
    int k = 0;
    ctx->image_ptr = malloc(ctx->height);
    for(y=0; y < HEIGHT; y++){
        pixel *line = malloc(ctx->width*sizeof(pixel));
        pixel *p =  *(ctx->image_ptr)+(int)y;
        p = line;
    }
    printf("lol");
    for (y= 0 ; y<HEIGHT; y++){
        pixel *line = *(ctx->image_ptr) + (int)y;
        for (x=0; x<WIDTH ; x++){
            pixel *p = malloc(sizeof(pixel));
            p = line + (int)x;
            p->r = *ptr;
            p->g = *(ptr+1);
            p->b = *(ptr+2);
            ptr+=3;
        }
    }
    k=0;
    for (y= 0 ; y<HEIGHT; y++){
        pixel **line = ctx->image_ptr + (int)y;
        for (x=0; x<WIDTH; x++){
            pixel *p = *line+(int)x;
            int average = abs((p->b+p->g+p->r)/(3*20));

            if (average >= 0 && average < 10) {
                printf("%c",ascii_tran[average]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
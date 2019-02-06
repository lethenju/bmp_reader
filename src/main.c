#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define WIDTH 100
#define HEIGHT 50
#define MAXBUF 10000000

typedef struct pixel_t {
    unsigned int r; //RED
    unsigned int g; //GREEN
    unsigned int b; //BLUE
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
    
    int screen[ctx->width][ctx->height]; 
    ptr = buf+offset;
    float x,y;
    ctx->image_ptr = (pixel**) malloc(ctx->width*ctx->height*sizeof(pixel));

    for (y= ctx->height-1 ; y>=0; y-=1){
        for (x=0; x<ctx->width; x+=1){
            pixel **image = ctx->image_ptr;
            int num = x*y+x;
            pixel *p = (pixel*) malloc(sizeof(pixel));
            p->r = *ptr;
            p->g = *(ptr+1);
            p->b = *(ptr+2);
            memcpy((void*) (image+num), (void*) p, sizeof(pixel));
            screen[(int)floor(x*WIDTH/ctx->width)][(int)floor(y*HEIGHT/ctx->height)] = 
                abs((*ptr+*(ptr+1)+*(ptr+2))/(3*20));
            ptr+=3;
        }
    }
    for (y= 0 ; y<HEIGHT; y++){
        for (x=0; x<WIDTH; x++){
            int num = x*y+x;
            pixel **image = ctx->image_ptr;
            pixel *p = *(image+num);
            int average = abs((p->b+p->g+p->r)/(3*20));

            if (average >= 0 && average < 10) {
                printf("%c",ascii_tran[screen[(int)x][(int)y]]);
            } else {
                printf(" ");
            }
          /*  if (screen[(int)x][(int)y] >= 0 && screen[(int)x][(int)y]<10) {
                printf("%c",ascii_tran[screen[(int)x][(int)y]]);
            } else {
                printf(" ");
            }
            */
        }
        printf("\n");
    }

    return 0;
}

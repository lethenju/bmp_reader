#include "bmp_reader.h"

bmp_reader_context* bmp_reader_init(FILE *fd) {
    bmp_reader_context *ctx = (bmp_reader_context*) malloc(sizeof(bmp_reader_context));
    ctx->fd = fd;
    ctx->buf =  (char*) malloc(MAXBUF*sizeof(char));
    ctx->ptr = ctx->buf;
    return ctx;
}

void bmp_reader_parse_header(bmp_reader_context *ctx) {
    char* ptr = ctx->ptr;
    fread(ctx->buf,MAXBUF,1,ctx->fd);   
    int i;  
    ptr+=2; // Skipping magic number
    memcpy(&(ctx->size),ptr,4);
    ptr+=4;
    printf("Size : %lu\n",ctx->size);
    ptr+=4;
    printf("Offset : %d\n", *ptr);
    ctx->offset = *ptr;
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
}

void bmp_reader_parse_image(bmp_reader_context *ctx) {
    bmp_reader_parse_header(ctx);
    
    char* ptr = ctx->buf+ctx->offset;
    float x,y;
    ctx->image_ptr = malloc(ctx->height);
    for (y= 0 ; y< ctx->height; y++){
        *(ctx->image_ptr+(int)(y*(HEIGHT)/ctx->height)) = malloc(ctx->width*sizeof(pixel));
        pixel *line = *(ctx->image_ptr + (int)(y*(HEIGHT)/ctx->height));
        for (x=0; x<ctx->width ; x++){
            pixel *p = malloc(sizeof(pixel));
            p = line + (int)(x*(WIDTH)/ctx->width);
            p->r = *ptr;
            p->g = *(ptr+1);
            p->b = *(ptr+2);
            ptr+=3;
        }
    }
}


void bmp_reader_render_image(bmp_reader_context *ctx) {
    int x, y;
    char ascii_tran[10] = {' ','.',
                        ':','-',
                        '+','=',
                        '*','o',
                        'O','M'};

    for (y= 0 ; y<HEIGHT; y++){
        pixel **line = ctx->image_ptr + HEIGHT - 1 - (int)y;
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
}


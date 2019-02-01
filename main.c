#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define WIDTH 100
#define HEIGHT 50
#define MAXBUF 10000000

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

    FILE *fd = fopen(argv[1],"rb");
    
    unsigned char* buf =  (unsigned char*) malloc(MAXBUF*sizeof(char));

    unsigned char* ptr = buf;
    fread(buf,MAXBUF,1,fd);    
    int i;  
    printf("\n");    
    printf("magic number: %c%c",*ptr,*(ptr+1));
    printf("\n");
    ptr+=2;
    unsigned long size = 0;
    memcpy(&size,ptr,4);
    ptr+=4;
    printf("Size : %lu",size);
    printf("\n");    

    ptr+=4;

    printf("Offset : %d", *ptr);
    int offset = *ptr;
    printf("\n");    
    ptr+=4;


    // DIB HEADER PARSING
    unsigned long sizeDIB = 0;
    unsigned long width = 0;
    unsigned long height = 0;
    
    memcpy(&sizeDIB,ptr,4);
    ptr+=4;
    memcpy(&width,ptr,4);
    ptr+=4;    
    memcpy(&height,ptr,4);
    ptr+=4;
    
    printf("Size DIB header : %lu\n",sizeDIB);
    printf("width : %lu\n",width);
    printf("height : %lu\n",height);
    
    int screen[width][height]; 
    ptr = buf+offset;
    float x,y;

    for (y= height-1 ; y>=0; y-=1){
        for (x=0; x<width; x+=1){
            screen[(int)floor(x*WIDTH/width)][(int)floor(y*HEIGHT/height)] = 
                (*ptr+*(ptr+1)+*(ptr+2))/(3*25);
            ptr+=3;
        }
    }

    for (y= 0 ; y<HEIGHT; y++){
        for (x=0; x<WIDTH; x++){
            if (screen[(int)x][(int)y] >= 0 && screen[(int)x][(int)y]<10) {
                printf("%c",ascii_tran[screen[(int)x][(int)y]]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
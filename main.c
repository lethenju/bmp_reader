#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define WIDTH 100
#define HEIGHT 50
#define MAXBUF 10000000



int main(int argc, char* argv[]) {
    srand(time(NULL));

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

    //On avance de 4 octets 
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

        char ascii_tran[10] = {' ','.',
                            ':','-',
                            '+','=',
                            '*','o',
                            'O','M'};
    while (1){
        system("clear");
        int r = rand();

        for (y= height-1 ; y>=0; y-=1){
            for (x=0; x<width; x+=1){
                screen[(int)floor(x*WIDTH/width)][(int)floor(y*HEIGHT/height)] = 
                    abs(((*ptr+*(ptr+1)+*(ptr+2))/3+r*256)%250);
                ptr+=3;
            }
        }
        int old_color= 0;
        for (y= 0 ; y<HEIGHT; y++){
            for (x=0; x<WIDTH; x++){
                if (old_color != screen[(int)x][(int)y]){
                    printf("\e[48;5;%dm ",screen[(int)x][(int)y]);
                } else {
                    printf(" ");
                }
                old_color = screen[(int)x][(int)y];
            }
            printf("\n");
        }
        usleep(100000);
        ptr = buf+offset;
    }
    return 0;
}
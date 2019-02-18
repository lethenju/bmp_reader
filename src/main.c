#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_reader.h"



int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage : exe FILE\n");
        return -1;
    }

    bmp_reader_context *ctx = bmp_reader_init(fopen(argv[1],"rb"));
    bmp_reader_parse_image(ctx);
    bmp_reader_render_image(ctx);

    return 0;
}
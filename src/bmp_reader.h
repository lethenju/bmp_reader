#ifndef BMP_READER_H
#define BMP_READER_H
#include "bmp_reader_types.h"

bmp_reader_context* bmp_reader_init(FILE *fd);


void bmp_reader_parse_image(bmp_reader_context *ctx);

void bmp_reader_render_image(bmp_reader_context *ctx);

#endif

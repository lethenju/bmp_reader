# bmp_reader

Welcome to the bmp_reader repository.
This very small program allows you to display bmp images straight to your terminal, by ascii.

Just type `make` to compile the sources.

Launch the output executable with a BMP source file to make it display the picture.

For now, it doesnt work for all types of images : just the simplest type of BMP is compatible.

## Example

Here is a small example of how to use the application

```c
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
```

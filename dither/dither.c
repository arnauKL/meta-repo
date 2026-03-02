#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://github.com/nothings/stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAXVAL          255
#define OUTPUT_FILENAME "output.png"

struct Image
{
    int width;
    int height;
    int channels;
    unsigned char data[];
};

void process_pixel(int i, int j, struct Image *im);
struct Image *read_image(const char *filename);

int
main(void)
{
    struct Image *input_im = read_image("IMG_8601.JPEG");

    free(input_im);

    return EXIT_SUCCESS;
}

struct Image *
read_image(const char *filename)
{
    int w, h, components, n_channels = 3;

    unsigned char *pixels = stbi_load(filename, &w, &h, &components, n_channels);
    assert(pixels != NULL);

    struct Image *im = malloc(sizeof(struct Image) + (w * h * n_channels));

    memcpy(im->data, pixels, w * h * n_channels);
    stbi_image_free(pixels);

    im->channels = n_channels;
    im->height = h;
    im->width = w;

    return im;
}

void
save_to_png(struct Image *im)
{
    int stride = im->channels * im->width; // bytes x row
    int result =
        stbi_write_png(OUTPUT_FILENAME, im->width, im->height, im->channels, im->data, stride);
    assert(result != 0);
}

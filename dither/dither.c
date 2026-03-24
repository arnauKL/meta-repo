#include <assert.h>
#include <stdlib.h>
#include <string.h>

// https://github.com/nothings/stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define MINVAL          28
#define MAXVAL          255
#define OUTPUT_FILENAME "output.png"

struct Image
{
    int width;
    int height;
    int channels;
    unsigned char data[];
};

void to_gray(const struct Image *input_im, struct Image *output_im);
void save_to_png(const struct Image *im);
struct Image *read_image(const char *filename);
struct Image *create_grayscale_image(const int w, const int h);
void apply_error(unsigned char *value, int error);

int
main(void)
{
    struct Image *input_im = read_image("400");
    struct Image *output_im = create_grayscale_image(input_im->width, input_im->height);

    // convert initial image to grayscale
    to_gray(input_im, output_im);

    const int threshold = 120;

    for (int y = 0; y < output_im->height; y++) {
        for (int x = 0; x < output_im->width; x++) {

            int idx = (y * output_im->width + x);

            int orig_value = output_im->data[idx];
            output_im->data[idx] = output_im->data[idx] < threshold ? MINVAL : MAXVAL;

            if (idx < (output_im->height - 1) * output_im->width) {
                int error = orig_value - output_im->data[idx];
                //
                //          X   7/16
                //  3/16  5/16  1/16
                //

                apply_error(&(output_im->data[idx + 1]), (7 * error) >> 4); // the next
                apply_error(&(output_im->data[idx + (input_im->width) - 1]),
                            (3 * error) >> 4); // below left
                apply_error(&(output_im->data[idx + (input_im->width) + 0]),
                            (5 * error) >> 4); // the next
                apply_error(&(output_im->data[idx + (input_im->width) + 1]),
                            (1 * error) >> 4); // the next
            }
        }
    }

    save_to_png(output_im);

    free(input_im);
    free(output_im);

    return EXIT_SUCCESS;
}

void
apply_error(unsigned char *value, int error)
{
    int new_value = *value - error;
    if (new_value > MAXVAL) {
        *value = MAXVAL;
    } else if (new_value < MINVAL) {
        *value = MINVAL;
    } else {
        *value = new_value;
    }
}

void
to_gray(const struct Image *input_im, struct Image *output_im)
{
    for (int y = 0; y < input_im->height; y++) {
        for (int x = 0; x < input_im->width; x++) {

            int idx = (y * input_im->width + x) * input_im->channels;

            int gray_idx = (y * input_im->width + x);

            output_im->data[gray_idx] =
                (int)(input_im->data[idx + 1] + input_im->data[idx + 2] + input_im->data[idx]) / 3;
        }
    }
}

struct Image *
create_grayscale_image(const int w, const int h)
{
    int n_channels = 1; // grayscale
                        //
    struct Image *im = malloc(sizeof(struct Image) + (w * h * n_channels));

    im->channels = n_channels;
    im->height = h;
    im->width = w;

    return im;
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
save_to_png(const struct Image *im)
{
    int stride = im->channels * im->width; // bytes x row
    int result =
        stbi_write_png(OUTPUT_FILENAME, im->width, im->height, im->channels, im->data, stride);
    assert(result != 0);
}

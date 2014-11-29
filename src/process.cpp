#include "process.hpp"

//////////////
// Includes //
#include <vector>
#include <tuple>

#include "image.hpp"

//////////
// Code //

using std::make_tuple;
using std::vector;
using std::tuple;
using std::get;

// Verifying the validity of a set of images.
bool validateImages(int count, Image** imgs) {
    for (int i = 1; i < count; i++) {
        if (imgs[i - 1]->width    != imgs[i]->width  ||
            imgs[i - 1]->height   != imgs[i]->height ||
            imgs[i - 1]->maxValue != imgs[i]->maxValue)
            return false;
    }
    return true;
}

// Getting a single pixel at a given index of every image.
Pixel* getPixelsAt(int count, Image** imgs, int index) {
    Pixel* pixels = new Pixel[count];
    for (int i = 0; i < count; i++)
        pixels[i] = imgs[i]->pixels[index];
    return pixels;
}

// Choosing a pixel from a vector of pixels.
Pixel choosePixel(int count, Pixel* pixels) {
    int n = 0;

    Pixel ips[] = {
        Pixel(0, 0, 0),
        Pixel(0, 0, 0)
    };

    for (int i = 0; i < count; i++) {
        if (n == 0)
            ips[1] = pixels[i];

        if (pixels[i] == ips[1])
            n++;
        else
            n--;
    }

    n = 0;
    for (int i = 0; i < count; i++)
        if (pixels[i] == ips[1])
            n++;

    if (n > count / 2)
        return ips[1];
    return ips[0];
}

// Processing a set of images.
Image* processImages(int count, Image** imgs) {
    if (!validateImages(count, imgs))
        return nullptr;

    int length = imgs[0]->width * imgs[0]->height;
    Pixel* finalPixels = new Pixel[length];
    Pixel* pixels;

    for (int i = 0; i < length; i++) {
        pixels = getPixelsAt(count, imgs, i);
        finalPixels[i] = choosePixel(count, pixels);
        delete[] pixels;
    }

    return new Image(finalPixels,
                     imgs[0]->width,
                     imgs[0]->height,
                     imgs[0]->maxValue);
}

// Greyscaling an image.
Image* grayscaleImage(Image* img) {
    int l = img->width * img->height;
    Pixel* grayPixels = new Pixel[l];

    int avg;
    for (int i = 0; i < l; i++) {
        avg = img->pixels[i].sum() / 3;
        grayPixels[i] = Pixel(avg, avg, avg);
    }

    return new Image(grayPixels, img->width, img->height, img->maxValue);
}

// Converting 2D coordinates to a 1D ordinate.
int convertCoords(Image* img, int row, int col) {
    return (row * img->width) + col;
}

// Creating a new image based on some vertex transformation.
template <class Function>
Image* vertexTransform(Image* img, Function transform) {
    Pixel* pixels = new Pixel[img->width * img->height];

    for (int row = 0; row < img->height; row++) {
        for (int col = 0; col < img->width; col++) {
            tuple<int, int> tpos = transform(make_tuple(row, col));

            pixels[convertCoords(img, row, col)] =
                img->pixels[convertCoords(img,
                                          get<0>(tpos),
                                          get<1>(tpos))];
        }
    }

    return new Image(pixels, img->width, img->height, img->maxValue);
}

// Flipping an image in the X coordinate.
Image* flipxImage(Image* img) {
    return vertexTransform(img, [=](tuple<int, int> pair) -> tuple<int, int> {
            return make_tuple(get<0>(pair), img->width - (get<1>(pair) + 1));
    });
}

// Flipping an image in the Y coordinate.
Image* flipyImage(Image* img) {
    return vertexTransform(img, [=](tuple<int, int> pair) -> tuple<int, int> {
        return make_tuple(img->height - (get<0>(pair) + 1), get<1>(pair));
    });
}

// Bounding a number by a minimum and a maximum.
int boundNum(int n, int min, int max) {
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

// Performing a radial blur on an image.
Image* radialBlurImage(Image* img, int radius) {
    Pixel* pixels = new Pixel[img->width * img->height];

    int r, g, b, count;
    Pixel p;
    for (int row = 0; row < img->height; row++) {
        for (int col = 0; col < img->width; col++) {
            r = 0; g = 0; b = 0, count = 0;

            for (int i = -radius; i < radius; i++) {
                for (int j = -radius; j < radius; j++) {
                    Pixel p = img->pixels[convertCoords(img,
                                                        boundNum(row + i, 0, img->height - 1),
                                                        boundNum(col + j, 0, img->width - 1))];

                    r += p.r;
                    g += p.g;
                    b += p.b;
                    count++;
                }
            }

            pixels[convertCoords(img, row, col)] =
                Pixel(r / count,
                      g / count,
                      b / count);
        }
    }

    return new Image(pixels, img->width, img->height, img->maxValue);
}

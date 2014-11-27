#include "process.hpp"

//////////////
// Includes //
#include "image.hpp"

//////////
// Code //

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

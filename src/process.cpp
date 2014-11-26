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

Pixel choosePixel(int count, Pixel* pixels) {
    // TODO: Develop a consensus.
    Pixel p;
    return p;
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

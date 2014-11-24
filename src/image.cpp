#include "image.hpp"

/////////////
// Include //
#include <iostream>
#include <fstream>
#include <string>

#include "pixel.hpp"
#include "load.hpp"

//////////
// Code //

// Loading an image from a file.
Image::Image(std::string path) {
    Pixel* pixels = loadPPM(path);

    this->pixels = pixels;
    this->width = 0;
    this->height = 0;
    this->maxValue = 0;
    this->error = pixels == nullptr;
}

// Creating a new image from a set of Pixels.
Image::Image(Pixel* pixels, int width, int height, int maxValue) {
    this->pixels = pixels;
    this->width = width;
    this->height = height;
    this->maxValue = maxValue;
    this->error = false;
}

// Creating a new (empty) image.
Image::Image() {
    this->pixels = new Pixel[0];
    this->width = 0;
    this->height = 0;
    this->maxValue = 0;
    this->error = false;
}

// Deconstructing an image.
Image::~Image() {
    delete[] this->pixels;
}

// Saving an image to a file.
int Image::save(std::string path) {
    return 1;
}

// Processing a set of images to sort out unwanted pixels.
Image* processImages(Image* i1, Image* i2, Image* i3) {
    Pixel* pixels;

    return new Image(pixels,
                     i1->width,
                     i1->height,
                     i1->maxValue);
}

// Writing an image out to the disk.
void writeImage(Image* img, std::string path) {
    // TODO: Write image.
}

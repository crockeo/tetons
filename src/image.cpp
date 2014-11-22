#include "image.hpp"

/////////////
// Include //
#include <string>

#include "pixel.hpp"

//////////
// Code //

// Loading an image from a file.
Image::Image(std::string path) {
    // TODO: load shit.
    this->pixels = new Pixel[0];
}

// Creating a new (empty) image.
Image::Image() {
    this->pixels = new Pixel[0];
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
Image processImages(Image, Image, Image);

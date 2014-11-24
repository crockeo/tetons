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
    this->pixels = nullptr;
    this->width = 0;
    this->height = 0;
    this->maxValue = 0;
    this->error = false;

    std::ifstream* in = new std::ifstream(path);
    if (!in) {
        std::cerr << "Could not open file to read.\n";
        this->error = true;
        return;
    }

    // Verifying the file header.
    if (!verifyHeader(in)) {
        std::cerr << "Could not verify the file header.\n";
        in->close();
        delete in;
        this->error = true;
        return;
    }

    // Loading the size.
    int* size = loadSize(in);
    if (size == nullptr) {
        std::cerr << "Could not load the image size.\n";
        in->close();
        delete in;
        this->error = true;
        return;
    }

    this->width = size[0];
    this->height = size[1];
    delete[] size;

    // Loading the maximum value.
    int maxValue = loadMaxValue(in);
    if (maxValue == -1) {
        std::cerr << "Could not load the maximum value.\n";
        in->close();
        delete in;
        this->error = true;
        return;
    }

    this->maxValue = maxValue;

    // Loading every single pixel.
    Pixel* pixels = loadPixels(in);
    if (pixels == nullptr) {
        std::cerr << "Could not load the image pixels.\n";
        in->close();
        delete in;
        this->error = true;
        return;
    }

    this->pixels = pixels;
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
    if (this->pixels != nullptr)
        delete[] this->pixels;
}

// Saving an image to a file.
int Image::save(std::string path) {
    return 1;
}

// Processing a set of images to sort out unwanted pixels.
Image* processImages(Image* i1, Image* i2, Image* i3) {
    return nullptr;
}

// Writing an image out to the disk.
void writeImage(Image* img, std::string path) {
    // TODO: Write image.
}

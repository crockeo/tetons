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
    delete in;
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
    std::ofstream* out = new std::ofstream(path);
    if (!out->good()) {
        delete out;
        return 1;
    }

    *out << "P3\n";
    *out << this->width << " " << this->height << "\n";
    *out << this->maxValue << "\n";

    for (int i = 0; i < this->width * this->height; i++) {
        if (i != 0 && i % 7 == 0)
            *out << "\n";

        *out << (int)this->pixels[i].r << "   "
             << (int)this->pixels[i].g << "   "
             << (int)this->pixels[i].b << "   ";
    }

    out->close();
    delete out;

    return 1;
}

// Processing a set of images to sort out unwanted pixels.
Image* processImages(Image* i1, Image* i2, Image* i3) {
    if (!(i1->width    == i2->width    && i2->width    == i3->width  &&
          i1->height   == i2->height   && i2->height   == i3->height &&
          i1->maxValue == i2->maxValue && i2->maxValue == i3->maxValue))
        return nullptr;

    Pixel* pixels = new Pixel[i1->width * i1->height];

    for (int i = 0; i < i1->width * i1->height; i++)
        pixels[i] = choosePixel(i1->pixels[i], i2->pixels[i], i3->pixels[i]);

    return new Image(pixels, i1->width, i1->height, i1->maxValue);
}

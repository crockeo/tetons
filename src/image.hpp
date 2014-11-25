#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

/////////////
// Include //
#include <string>

#include "pixel.hpp"

//////////
// Code //

// A type to represent an image.
struct Image {
    Pixel* pixels;
    int width, height;
    int maxValue;
    bool error;

    // Loading an image from a file.
    Image(std::string);

    // Creating a new image from a set of Pixels.
    Image(Pixel*, int, int, int);

    // Creating a new (empty) image.
    Image();

    // Deconstructing an image.
    ~Image();

    // Saving an image to a file.
    int save(std::string);
};

#endif

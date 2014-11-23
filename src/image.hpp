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

    // Loading an image from a file.
    Image(std::string);

    // Creating a new image from a set of Pixels.
    Image(Pixel*);

    // Creating a new (empty) image.
    Image();

    // Deconstructing an image.
    ~Image();

    // Saving an image to a file.
    int save(std::string);
};

// Processing a set of images to sort out unwanted pixels.
Image processImages(Image, Image, Image);

#endif

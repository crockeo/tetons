#ifndef _PIXEL_HPP_
#define _PIXEL_HPP_

//////////
// Code //

// A type to represent a pixel.
struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    // Constructing a Pixel.
    Pixel(unsigned char, unsigned char, unsigned char);

    // Summing the values in a Pixel.
    int sum();

    // Checking equality between pixels.
    bool equals(Pixel);

    // Getting the distance between two pixels.
    int distance(Pixel);

    // Getting the average between two pixels;
    Pixel average(Pixel);
};

// Out of three pixels, check for the two pixels that are closest and choose
// the average of those two as the result.
Pixel choosePixel(Pixel, Pixel, Pixel);

#endif

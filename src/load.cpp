#include "load.hpp"

//////////////
// Includes //
#include <iostream>
#include <fstream>
#include <string>

#include "pixel.hpp"

//////////
// Code //

// Verifying the hedaer on a PPM.
bool verifyHeader(std::ifstream* in) {
    char* header = new char[3];
    in->get(header, 3);

    bool good = false;
    if (header[0] == 'P' && header[1] == '3')
        good = true;

    delete[] header;
    return good;
}

// Loading the width and height from a file buffer.
int* loadSize(std::ifstream* in) {
    return nullptr;
}

// Loading the max value of an image buffer.
int loadMaxValue(std::ifstream* in) {
    return 0;
}

// Loading a single pixel from an ifstream.
Pixel loadPixel(std::ifstream* in) {
    return Pixel(0, 0, 0);
}

// Loading every single Pixel from an ifstream.
Pixel* loadPixels(std::ifstream* in) {
    return nullptr;
}

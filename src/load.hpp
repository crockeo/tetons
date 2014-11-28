#ifndef _LOAD_HPP_
#define _LOAD_HPP_

//////////////
// Includes //
#include <fstream>
#include <string>

#include "pixel.hpp"

//////////
// Code //

// Converting a set of characters to a number.
int toInts(char*, int);

// Verifying the hedaer on a PPM.
bool verifyHeader(std::ifstream*);

// Loading the width and height from a file buffer.
int* loadSize(std::ifstream*);

// Loading the max value of an image buffer.
int loadMaxValue(std::ifstream*);

// Loading a single pixel from an ifstream.
Pixel loadPixel(std::ifstream*);

// Loading every single Pixel from an ifstream.
Pixel* loadPixels(std::ifstream*);

#endif

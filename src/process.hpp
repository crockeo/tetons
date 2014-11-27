#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

//////////////
// Includes //
#include "image.hpp"

//////////
// Code //

// Processing a set of images.
Image* processImages(int, Image**);

// Greyscaling an image.
Image* grayscaleImage(Image*);

// Flipping an image in the X coordinate.
Image* flipxImage(Image*);

// Flipping an image in the Y coordinate.
Image* flipyImage(Image*);

#endif

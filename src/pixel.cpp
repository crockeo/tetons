#include "pixel.hpp"

//////////
// Code //

// Getting the absolute value of an int.
int absolute(int n) {
    if (n < 0)
        return -n;
    return n;
}

// Constructing a Pixel.
Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->error = false;
}

Pixel::Pixel() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->error = true;
}

// Summing the values in a Pixel.
int Pixel::sum() {
    return (int)(this->r) + (int)(this->g) + (int)(this->b);
}

// Checking equality between pixels.
bool Pixel::equals(Pixel p) {
    return this->r == p.r &&
           this->g == p.g &&
           this->b == p.b;
}

// Getting the distance between two pixels.
int Pixel::distance(Pixel p) {
    Pixel temp(absolute(this->r - p.r),
               absolute(this->g - p.g),
               absolute(this->b - p.b));
    return temp.sum();
}

// Getting the average between two pixels;
Pixel Pixel::average(Pixel p) {
    return Pixel((this->r + p.r) / 2,
                 (this->g + p.g) / 2,
                 (this->b + p.b) / 2);
}

// Out of three pixels, check for the two pixels that are closest and choose
// the average of those two as the result.
Pixel choosePixel(Pixel a, Pixel b, Pixel c) {
    int abd = a.distance(b),
        acd = a.distance(c),
        bcd = b.distance(c);

    if (abd <= acd && abd <= bcd)
        return a.average(b);
    else if (acd <= abd && acd <= bcd)
        return a.average(c);
    else if (bcd <= abd && bcd <= acd)
        return b.average(c);

    return Pixel(0, 0, 0);
}

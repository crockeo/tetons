#include "load.hpp"

//////////////
// Includes //
#include <iostream>
#include <fstream>
#include <string>

#include "pixel.hpp"

//////////
// Code //

// Converting a character of a number to a number.
int toInt(char c) {
    if ('0' <= c && c <= '9')
        return (int)c - 48;
    return -1;
}

// Converting a set of characters to a number.
int toInts(char* cs, int accum) {
    if (cs[0] == '\0')
        return accum;

    int n = toInt(cs[0]);
    if (n == -1)
        return -1;

    return toInts(cs + 1, (accum * 10) + n);
}

// Consuming spaces from an ifstream. It returns the first character that's
// matched as NOT a whitespace character.
void consumeWhitespace(std::ifstream* in) {
    while (in->peek() == ' ')
        in->get();
}

// Verifying the hedaer on a PPM.
bool verifyHeader(std::ifstream* in) {
    char* header = new char[8];
    in->getline(header, 3, '\n');

    bool good = false;
    if (header[0] == 'P' && header[1] == '3')
        good = true;

    delete[] header;

    return good;
}

// Loading the width and height from a file buffer.
int* loadSize(std::ifstream* in) {
    char* width = new char[16];
    char* height = new char[16];

    in->getline(width, 16, ' ');
    in->getline(height, 16, '\n');

    int* size = new int[2];

    size[0] = toInts(width, 0);
    size[1] = toInts(height, 0);

    delete[] width;
    delete[] height;

    return size;
}

// Loading the max value of an image buffer.
int loadMaxValue(std::ifstream* in) {
    char* mv = new char[16];
    in->getline(mv, 16, '\n');

    int n = toInts(mv, 0);
    delete[] mv;

    return n;
}

// Loading a single pixel from an ifstream.
Pixel loadPixel(std::ifstream* in) {
    if (in->eof()) {
        Pixel p;
        p.error = true;
        return p;
    }

    char* str = new char[16];
    int r, g, b;

    consumeWhitespace(in);
    in->get(str, 16, ' ');
    r = toInts(str, 0);

    consumeWhitespace(in);
    in->get(str, 16, ' ');
    g = toInts(str, 0);

    consumeWhitespace(in);
    in->get(str, 16, ' ');
    b = toInts(str, 0);

    delete[] str;

    Pixel p(r, g, b);
    return p;
}

// Loading every single Pixel from an ifstream.
Pixel* loadPixels(std::ifstream* in) {
    int size = 0;
    int length = 0;
    Pixel* pixels = new Pixel[size];

    for (Pixel p = loadPixel(in); !p.error; p = loadPixel(in)) {
        if (length >= size) {
            Pixel* tempPixels = new Pixel[size * 2];
            for (int i = 0; i < size; i++)
                tempPixels[i] = pixels[i];

            if (size == 0)
                size++;
            else
                size *= 2;

            delete[] pixels;
            pixels = tempPixels;
        }

        pixels[length++] = p;
    }

    if (size == 0) {
        delete[] pixels;
        return nullptr;
    } else {
        Pixel* tempPixels = new Pixel[length];
        for (int i = 0; i < length; i++)
            tempPixels[i] = pixels[i];
        delete[] pixels;
        pixels = tempPixels;
    }

    return pixels;
}

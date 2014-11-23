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

// Loading a PPM into a set of pixels
Pixel* loadPPM(std::string path) {
    std::ifstream* in = new std::ifstream(path.c_str());

    if (!in->good()) {
        std::cerr << "Could not open PPM.\n";
        return nullptr;
    }

    if (!verifyHeader(in))
        return nullptr;

    return nullptr;
}

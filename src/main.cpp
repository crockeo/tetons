/////////////
// Imports //
#include <iostream>

#include "process.hpp"
#include "image.hpp"
#include "pixel.hpp"

//////////
// Code //

// Loading an image from the filesystem.
Image* loadImage(char* path) {
    std::cout << "Loading image " << path << ".\n";
    Image* img = new Image(std::string(path));
    if (img->error) {
        std::cerr << "Failed to load image " << path << ".\n";
        delete img;
        return nullptr;
    }

    return img;
}

// Loading a set of images.
Image** loadImages(int argc, char** argv) {
    Image** imgs = new Image*[argc - 2];

    for (int i = 1; i < argc - 1; i++) {
        imgs[i - 1] = loadImage(argv[i]);
        if (imgs[i - 1] == nullptr) {
            std::cerr << "Could not load image " << argv[i] << "!\n";
            for (int j = 1; j < i; i++)
                delete imgs[j];
            delete[] imgs;

            return nullptr;
        }
    }

    return imgs;
}

// Placeholder main.
int main(int argc, char** argv) {
    // Checking for argument validity.
    if (argc == 1) {
        std::cout << "Proper usage: tentons <img 1> <img 2> ... "
                  << "<output image>\n";
        return 1;
    }

    // Loading each Image.
    Image** imgs = loadImages(argc, argv);
    if (imgs == nullptr)
        return 2;

    // Processing the output image.
    std::cout << "Processing output image...\n";
    Image* out = processImages(argc - 2, imgs);

    // Writing the output image.
    if (out != nullptr) {
        std::cout << "Writing output image...\n";
        out->save(std::string(argv[argc - 1]));
    } else {
        std::cout << "Cannot write out null output image!\n";
    }

    // Cleaning up memory.
    std::cout << "Cleaning up memory...\n";
    for (int i = 0; i < argc - 2; i++)
        if (imgs[i] != nullptr)
            delete imgs[i];

    delete[] imgs;

    if (out != nullptr)
        delete out;

    return 0;
}

/////////////
// Imports //
#include <iostream>

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
        return nullptr;
    }

    return img;
}

// Loading a set of images.
Image** loadImages(char** argv) {
    Image** imgs = new Image*[3];

    Image* img1 = loadImage(argv[1]);
    if (img1 == nullptr)
        return nullptr;

    Image* img2 = loadImage(argv[2]);
    if (img2 == nullptr)
        return nullptr;

    Image* img3 = loadImage(argv[3]);
    if (img3 == nullptr)
        return nullptr;

    imgs[0] = img1;
    imgs[1] = img2;
    imgs[2] = img3;

    return imgs;
}

// Placeholder main.
int main(int argc, char** argv) {
    // Checking for argument validity.
    if (argc != 5) {
        std::cout << "Proper usage: tentons <output image 1> <output image 2> "
                  << "<output image 3> <output image>\n";

        return 1;
    }

    // Loading each Image.
    Image** imgs = loadImages(argv);
    if (imgs == nullptr)
        return 2;

    // Processing the output image.
    std::cout << "Processing output image...\n";
    Image* out = processImages(imgs[0], imgs[1], imgs[2]);

    // Writing the output image.
    std::cout << "Writing output image...\n";
    writeImage(out, std::string(argv[4]));

    // Cleaning up memory.
    std::cout << "Cleaning up memory...";
    for (int i = 0; i < 3; i++)
        if (imgs[i] != nullptr)
            delete imgs[i];
    delete imgs;
    if (out != nullptr)
        delete out;

    return 0;
}

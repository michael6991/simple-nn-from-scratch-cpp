#ifndef __MNIST_LOADER_
#define __MNIST_LOADER_
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <stdint.h>

#define MNIST_ROWS 28
#define MNIST_COLS 28
#define MNIST_IMAGE_SIZE 748 // 28 x 28

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class MNSITLoader
{
    private:
        std::ifstream images_file; // Open file for reading
        std::ifstream labels_file;
        vector<uint8_t> img = vector<uint8_t>(MNIST_IMAGE_SIZE);

    public:
        MNSITLoader(const std::string& path_images, const std::string& path_labels);
        ~MNSITLoader();

        // Read an image "lazily"
        void read_mnist_cv();
        void read_img(char* out, uint32_t index);
        uint32_t swap_endian(uint32_t val);
};





#endif
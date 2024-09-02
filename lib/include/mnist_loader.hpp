#ifndef __MNIST_LOADER_
#define __MNIST_LOADER_
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <stdint.h>

#define MNIST_IMAGE_SIZE 748 // 28 x 28

class MNSITLoader
{
    private:
        std::ifstream images_file; // Open file for reading
        std::ifstream labels_file;
        std::vector<uint8_t> img = std::vector<uint8_t>(MNIST_IMAGE_SIZE);

    public:
        MNSITLoader(const std::string& path_images, const std::string& path_labels);
        ~MNSITLoader();

        // Read image "lazily"
        void read_mnist_cv();
        uint32_t swap_endian(uint32_t val);
};





#endif /* __MNIST_LOADER__ */
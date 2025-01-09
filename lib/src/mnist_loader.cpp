#include "../include/mnist_loader.hpp"
#include "opencv2/opencv.hpp"


MNSITLoader::MNSITLoader(const string& path_images, const string& path_labels)
{
    this->images_file.open(path_images, std::ios::in | std::ios::binary);
    this->labels_file.open(path_labels, std::ios::in | std::ios::binary);

    if (!images_file.is_open()) {
        throw std::runtime_error("File not open: " + path_images);
    }
    if (!labels_file.is_open()) {
        throw std::runtime_error("File not open: " + path_labels);
    }
}

uint32_t MNSITLoader::swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}


void MNSITLoader::read_mnist_cv()
{
    // Read the magic and the meta data
    uint32_t magic;
    uint32_t num_items;
    uint32_t num_labels;
    uint32_t rows;
    uint32_t cols;

    this->images_file.read(reinterpret_cast<char* >(&magic), 4);
    magic = swap_endian(magic);
    if(magic != 2051){
        throw std::runtime_error("Incorrect image file magic: " + std::to_string(magic));
    } else {
        cout << "Correct image magic: " << magic << endl;
    }

    this->labels_file.read(reinterpret_cast<char* >(&magic), 4);
    magic = swap_endian(magic);
    if(magic != 2049){
        throw std::runtime_error("Incorrect label file magic: " + std::to_string(magic));
    } else {
        cout << "Correct label magic: " << magic << endl;
    }

    this->images_file.read(reinterpret_cast<char* >(&num_items), 4);
    num_items = swap_endian(num_items);
    this->labels_file.read(reinterpret_cast<char* >(&num_labels), 4);
    num_labels = swap_endian(num_labels);
    if(num_items != num_labels){
        throw std::runtime_error("Number of images in images file should equal to number of labels in labels file");
    } else {
        cout << "Number of images equals to number of labels: " << num_items << endl;
    }

    this->images_file.read(reinterpret_cast<char* >(&rows), 4);
    rows = swap_endian(rows);
    this->images_file.read(reinterpret_cast<char* >(&cols), 4);
    cols = swap_endian(cols);
    cout << "Image rows:  "<< rows << ", cols: " << cols << endl;
    if (rows != cols) {
        throw std::runtime_error("Number of rows not equal to number of columns");
    }

    char label = 0;
    char* pixels = new char[rows * cols];

    for (int i = 0; i < num_items; ++i) 
    {
        // read image pixel
        this->images_file.read(pixels, rows * cols);
        // read label
        this->labels_file.read(&label, 1);

        string sLabel = std::to_string(int(label));
        cout << "lable is: " << sLabel << endl;

        // convert it to cv Mat, and show it
        cv::Mat image_tmp(rows, cols, CV_8UC1, pixels);
        // resize bigger for showing
        cv::resize(image_tmp, image_tmp, cv::Size(100, 100));
        cv::imshow(sLabel, image_tmp);
        cv::waitKey(0);
    }

    delete[] pixels;
}

/**
 * Seek to and read the i'th image in the sequence of images within images file.
 * The 28x28 image will be read into the given ouptut pointer.
 * Index should be >= 0
 */
void MNSITLoader::read_img(char* out, uint32_t index)
{
    char label = 0;
    char* pixels = new char[MNIST_IMAGE_SIZE];

    // Seek to the required image according to full 28 byte jumps
    this->images_file.seekg(index * MNIST_IMAGE_SIZE);

    this->images_file.read(pixels, MNIST_IMAGE_SIZE);
    out = pixels;
}



MNSITLoader::~MNSITLoader()
{
}



#include "../include/mnist_loader.hpp"
// #include <opencv2/opencv.hpp>
#include "/opt/homebrew/opt/opencv/include/opencv4/opencv2/opencv.hpp"

/**
 * The compilation line that worked:
*  clang++ a.c -o a.out -g -std=c++17 -I/opt/homebrew/opt/opencv/include/opencv4 -L/opt/homebrew/opt/opencv/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
 */


MNSITLoader::MNSITLoader(const string& path_images, const string& path_labels)
{
    this->images_file.open(path_images, ios::in | ios::binary);
    this->labels_file.open(path_labels, ios::in | ios::binary);

    if (!images_file.is_open()) {
        throw runtime_error("File not open: " + path_images);
    }
    if (!labels_file.is_open()) {
        throw runtime_error("File not open: " + path_labels);
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

    this->images_file.read(reinterpret_cast<char *>(&magic), 4);
    magic = swap_endian(magic);
    if(magic != 2051){
        cout << "Incorrect image file magic: " << magic << endl;
        return;
    } else {
        cout << "Correct image magic: " << magic << endl;
    }

    this->labels_file.read(reinterpret_cast<char *>(&magic), 4);
    magic = swap_endian(magic);
    if(magic != 2049){
        cout << "Incorrect label file magic: " << magic << endl;
        return;
    } else {
        cout << "Correct label magic: " << magic << endl;
        return;
    }

    this->images_file.read(reinterpret_cast<char *>(&num_items), 4);
    num_items = swap_endian(num_items);
    this->labels_file.read(reinterpret_cast<char *>(&num_labels), 4);
    num_labels = swap_endian(num_labels);
    if(num_items != num_labels){
        cout << "Number of images in images file should equal to number of labels in labels file" << endl;
        return;
    } else {
        cout << "Number of images equals to number of labels: " << num_items <<endl;
    }

    this->images_file.read(reinterpret_cast<char *>(&rows), 4);
    rows = swap_endian(rows);
    this->labels_file.read(reinterpret_cast<char *>(&cols), 4);
    cols = swap_endian(cols);
    cout << "Image rows:  "<< rows << ", cols: " << cols << endl;

    char label = 0;
    char* pixels = new char[rows * cols];

    for (int item_id = 0; item_id < num_items; ++item_id) 
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


MNSITLoader::~MNSITLoader()
{
}



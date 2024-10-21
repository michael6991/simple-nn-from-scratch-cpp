#include "../lib/include/mnist_loader.hpp"
#include <iostream>
#include <string>

using std::string;
using std::cout; using std::cin; using std::cerr; using std::endl;
using std::exception;


int main(int argc, char **argv)
{
    string base_dir = argv[1];  // /path/to/mnist-base-dir
    string images_path = base_dir + "/train-images-idx3-ubyte";
    string labels_path = base_dir + "/train-labels-idx1-ubyte";

    cout << "\nStarting mnist loader test...\n" << endl;
    cout << "base dir: " << base_dir << endl;
    cout << "images_path: " << images_path << endl;
    cout << "labels_path: " << labels_path << endl;

    try {
        MNSITLoader * mnist = new MNSITLoader(images_path, labels_path);
        mnist->read_mnist_cv();
    }
    catch (const exception& e) {
        // Catch any exception thrown during the execution of MNISTLoader
        cerr << "Exception caught: " << e.what() << endl;
    }
    return 0;
}
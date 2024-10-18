#include "../lib/include/mnist_loader.hpp"
#include <iostream>
#include <string>

using std::string;
using std::cout; using std::cin; using std::cerr; using std::endl;
using std::exception;


int main()
{
    // Put custom paths here
    string images_path = "../mnist/train-images-idx3-ubyte";
    string labels_path = "../mnist/train-labels-idx1-ubyte";

    try {
        MNSITLoader * mnist = new MNSITLoader(images_path, labels_path);
    }
    catch (const exception& e) {
        // Catch any exception thrown during the execution of MNISTLoader
        cerr << "Exception caught: " << e.what() << endl;
    }
    return 0;
}
#include <cstdio>
#include <vector>
#include <iostream>
#include "../main/layer.hpp"


using namespace std;


int main(int argc, char **argv)
{
    printf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);

    Layer *l = new Layer(4, true, 0, "layer 0");

    l->print_layer(l->get_name());

    delete l;

    return 0;
}

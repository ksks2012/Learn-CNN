#include "convolution_layer.h"
#include "read_mnist.h"

void train(void);

void test(void);

using namespace std;

int main(int argc, char *argv[]) {
    switch (atoi(argv[1])) {
        case 1:
            train();
            break;

        case 2:
            test();
            break;
    }
}

void train() {
    // TODO: net

    vector<label_t> train_labels, test_labels;
    vector<vec_t> train_images, test_images, feature_map;
    //::vector<vec_t> train_images, test_images;

    read_mnist_labels("./data/train-labels.idx1-ubyte", &train_labels);

    // cout << train_labels.size() << endl;

    // printf("%d\n", train_labels.at(0));

    read_mnist_images(
        "./data/train-images.idx3-ubyte", &train_images, -1.0, 1.0, 2, 2);

    conv(train_images[0],
         feature_map,
         32,
         32,
         5,
         1,
         6);  // C1, 1@32x32-in, 6@28x28-out

    // cout << train_images[0].size();
}

void test() {}
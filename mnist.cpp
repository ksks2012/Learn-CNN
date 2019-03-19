#include "activation.h"
#include "convolution_layer.h"
#include "pooling_layer.h"
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
    vector<vec_t> train_images, test_images, feature_map_C1, feature_map_C3;
    //::vector<vec_t> train_images, test_images;

    read_mnist_labels("./data/train-labels.idx1-ubyte", &train_labels);

    // cout << train_labels.size() << endl;

    // printf("%d\n", train_labels.at(0));

    read_mnist_images(
        "./data/train-images.idx3-ubyte", &train_images, -1.0, 1.0, 2, 2);

    // single image
    conv(train_images,
         feature_map_C1,
         32,
         32,
         5,
         1,
         6);  // C1, 1@32x32-in, 6@28x28-out

    for (size_t i = 0; i < feature_map_C1.size(); ++i)
        func_ReLU(feature_map_C1[i]);

    max_pool(feature_map_C1, 28, 28, 6, 2, 2);  // S2, 6@28x28-in, 6@14x14-out

    conv(feature_map_C1,
         feature_map_C3,
         14,
         14,
         5,
         6,
         16);  // C3, 6@14x14-in, 16@10x10-out

    cout << feature_map_C3.size() << endl;
}

void test() {}
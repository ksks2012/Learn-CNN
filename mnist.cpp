#include "activation.h"
#include "convolution_layer.h"
#include "pooling_layer.h"
#include "read_mnist.h"

void train(void);

void test(void);

void check_map(tensor_t);

using namespace std;

int main(int argc, char *argv[]) {
    srand(time(NULL));

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
    cout << "C1" << endl;
    conv(train_images,
         feature_map_C1,
         32,
         32,
         5,
         1,
         6);  // C1, 1@32x32-in, 6@28x28-out

    fstream fout;
    fout.open("0.dat", ios::out);

    for (size_t i = 0; i < feature_map_C1.size(); ++i) {
        for (size_t j = 0; j < feature_map_C1[i].size(); ++j) {
            fout << feature_map_C1[i][j] << " ";
        }
        fout << endl;
    }

    func_ReLU(feature_map_C1);
    check_map(feature_map_C1);

    cout << "S2" << endl;
    max_pool(feature_map_C1, 28, 28, 6, 2, 2);  // S2, 6@28x28-in, 6@14x14-out
    check_map(feature_map_C1);

    cout << "C3" << endl;
    conv(feature_map_C1,
         feature_map_C3,
         14,
         14,
         5,
         6,
         16);  // C3, 6@14x14-in, 16@10x10-out
    check_map(feature_map_C3);

    cout << "S4" << endl;
    max_pool(feature_map_C3, 10, 10, 16, 2, 2);  // S4, 16@10x10-in, 16@5x5-out
    check_map(feature_map_C3);

    // S4, 16@10x10-in, 16@5x5-out
    // C5, 16@5x5-in, 120@1x1-out
    // F6, 120-in, 10-out

    // fstream fout;
    // fout.open("0", ios::out);

    // for (size_t i = 0; i < feature_map_C3.size(); ++i) {
    //     for (size_t j = 0; j < feature_map_C3[i].size(); ++j) {
    //         fout << feature_map_C3[i][j] << " ";
    //     }
    //     fout << endl;
    // }
}

void test() {}

void check_map(tensor_t map) {
    for (size_t i = 0; i < map.size(); ++i) {
        if (map[i].size() == 0) {
            cout << i << " error" << endl;
            exit(0);
        }
    }
}
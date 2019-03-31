#include "activation.h"

void func_ReLU(tensor_t &feature_map) {
    for (size_t i = 0; i < feature_map.size(); ++i) {
        for (size_t j = 0; j < feature_map[i].size(); ++j) {
            feature_map[i][j] =
                feature_map[i][j] > 0.0 ? feature_map[i][j] : 0.0;
        }
    }
}
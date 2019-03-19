#include "activation.h"

void func_ReLU(vec_t &feature_map) {
    for (size_t i = 0; i < feature_map.size(); ++i) {
        feature_map[i] = feature_map[i] > 0.0 ? feature_map[i] : 0.0;
    }
}
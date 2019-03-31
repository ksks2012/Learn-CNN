#include "pooling_layer.h"

void max_pool(tensor_t &feature_map,
              size_t in_width,
              size_t in_height,
              size_t in_channels,
              size_t stride,
              size_t filter_size) {
    tensor_t pooled_feature_map(feature_map.size());

    size_t pool_size = (in_width - filter_size) / stride + 1;

    for (size_t i = 0; i < feature_map.size(); ++i) {
        pooled_feature_map[i].resize(pool_size * pool_size);
        pool(feature_map[i],
             pooled_feature_map[i],
             in_width,
             stride,
             filter_size,
             pool_size);
    }
    feature_map = pooled_feature_map;
}

void pool(vec_t &feature_map,
          vec_t &pooled_feature_map,
          size_t map_size,
          size_t stride,
          size_t filter_size,
          size_t pool_size) {
    for (size_t i = 0; i < pool_size; ++i) {
        for (size_t j = 0; j < pool_size; ++j) {
            pooled_feature_map[i * pool_size + j] = 0;

            float max_number = INT32_MAX * -1;

            for (size_t m = 0; m < filter_size; ++m) {
                for (size_t n = 0; n < filter_size; ++n) {
                    size_t feature_map_idx =
                        (i * stride + m) * map_size + j * stride + n;

                    if (feature_map.at(feature_map_idx) > max_number)
                        max_number = feature_map.at(feature_map_idx);
                }
            }
            pooled_feature_map[i * pool_size + j] = max_number;
        }
    }
}
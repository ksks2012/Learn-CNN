#include "convolution_layer.h"

void conv(tensor_t &image,
          tensor_t &map_ptr,
          size_t in_width,
          size_t in_height,
          size_t window_size,
          size_t in_channels,
          size_t out_channels,
          size_t w_stride,
          size_t h_stride,
          size_t w_dilation,
          size_t h_dilation) {
    size_t map_size = (in_width - window_size) / w_stride + 1;

    tensor_t feature_map(in_channels * out_channels);

    tensor_t feature_detector(in_channels * out_channels);
    for (size_t i = 0; i < in_channels; ++i) {
        for (size_t j = 0; j < out_channels; ++j) {
            size_t idx = i * out_channels + j;

            // detector
            feature_detector[idx].resize(window_size * window_size);

            rand_vec(feature_detector[idx]);

            feature_map[idx].resize(map_size * map_size);

            // TODO: stride
            convolution(image[i],
                        feature_map[idx],
                        feature_detector[idx],
                        in_width,
                        map_size,
                        window_size);
        }
    }
    map_ptr = feature_map;
}

void rand_vec(vec_t &vec) {
    srand(time(NULL));

    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = rand() % 2;
    }
    // print_vec(vec);
    // fgetc(stdin);
}

void convolution(vec_t image,
                 vec_t &feature_map,
                 vec_t &detector,
                 size_t image_size,
                 size_t map_size,
                 size_t window_size) {
    for (size_t i = 0; i < map_size; ++i) {
        for (size_t j = 0; j < map_size; ++j) {
            feature_map[i * map_size + j] = 0;
            for (size_t m = 0; m < window_size; ++m) {
                for (size_t n = 0; n < window_size; ++n) {
                    feature_map.at(i * map_size + j) +=
                        image.at((i + m) * image_size + j + n) *
                        detector.at(m * window_size + n);
                }
            }
        }
    }
}

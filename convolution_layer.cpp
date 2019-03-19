#include "convolution_layer.h"

void conv(vec_t &image,
          size_t in_width,
          size_t in_height,
          size_t window_size,
          size_t in_channels,
          size_t out_channels,
          size_t w_stride,
          size_t h_stride,
          size_t w_dilation,
          size_t h_dilation) {
    cout << image.size() << endl;

    // image.resize(28 * 28);

    size_t map_size = in_width - window_size + 1;

    tensor_t feature_map(out_channels);

    tensor_t feature_detector(out_channels);

    for (size_t i = 0; i < out_channels; ++i) {
        feature_detector[i].resize(window_size * window_size);

        rand_vec(feature_detector[i]);

        feature_map[i].resize(map_size * map_size);

        convolution(image,
                    feature_map[i],
                    feature_detector[i],
                    in_width,
                    map_size,
                    window_size);
    }

    cout << feature_map.size() << endl;

    // image = feature_map;
}

void rand_vec(vec_t &vec) {
    srand(time(NULL));

    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = rand() % 2;
    }

    // print_vec(vec);
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
                    // cout << "fixed " << i << " " << j << " " << m << " " << n
                    //      << endl;
                    // cout << "offset feature_map:" << i * image_size + j << "
                    // image "
                    //      << (i + m) * image_size + j + n << " "
                    //      << m * window_size + n << endl;
                    feature_map.at(i * map_size + j) +=
                        image.at((i + m) * image_size + j + n) *
                        detector.at(m * window_size + n);
                }
            }
            // fgetc(stdin);
        }
    }
}

void Relu(vec_t &feature_map) {}
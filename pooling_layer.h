#pragma once

#include <limits>

#include "read_mnist.h"

void max_pool(tensor_t &, size_t, size_t, size_t, size_t, size_t);

void pool(vec_t &feature_map,
          vec_t &pooled_feature_map,
          size_t map_size,
          size_t stride,
          size_t filter_size,
          size_t pool_size);
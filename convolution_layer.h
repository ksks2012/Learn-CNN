#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

void conv(vector<vec_t> *,
          size_t in_width,
          size_t in_height,
          size_t window_size,
          size_t in_channels,
          size_t out_channels,
          size_t w_stride = 1,
          size_t h_stride = 1,
          size_t w_dilation = 1,
          size_t h_dilation = 1);

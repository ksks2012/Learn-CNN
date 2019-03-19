#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "read_mnist.h"

void conv(tensor_t &,
          tensor_t &,
          size_t,
          size_t,
          size_t,
          size_t,
          size_t,
          size_t = 1,
          size_t = 1,
          size_t = 1,
          size_t = 1);

void rand_vec(vec_t &);

void convolution(vec_t, vec_t &, vec_t &, size_t, size_t, size_t);

#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "read_mnist.h"

void conv(vec_t &,
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

void func_ReLU(vec_t &);

// TODO: Leaky_ReLU & Sigmoid
// void func_Leaky_ReLU(vec_t &);

// void func_Sigmoid(vec_t &);
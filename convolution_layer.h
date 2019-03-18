#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "read_mnist.h"

void conv(vector<vec_t> *,
          size_t,
          size_t,
          size_t,
          size_t,
          size_t,
          size_t = 1,
          size_t = 1,
          size_t = 1,
          size_t = 1);

/*
    Copyright (c) 2013, Taiga Nomi and the respective contributors
    All rights reserved.

    Use of this source code is governed by a BSD-style license that can be found
    in the LICENSE file.

    rewrite 2019 An-Hong Cheng
*/
#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "aligned_allocator.h"

using namespace std;

struct mnist_header {
    uint32_t magic_number;
    uint32_t num_items;
    uint32_t num_rows;
    uint32_t num_cols;
};

// label's size is one byte and between one to nine
typedef unsigned char label_t;

typedef size_t layer_size_t;  // for backward compatibility

typedef std::vector<float_t, aligned_allocator<float_t, 64>> vec_t;

typedef std::vector<vec_t> tensor_t;

template <typename T>
T *reverse_endian(T *p) {
    std::reverse(reinterpret_cast<char *>(p),
                 reinterpret_cast<char *>(p) + sizeof(T));
    return p;
}

inline bool is_little_endian();

inline void read_mnist_header(ifstream &, mnist_header &);

void parse_mnist_image(std::ifstream &, const mnist_header &, float_t, float_t,
                       int, int, vec_t &);

void read_mnist_images(const string &, vector<vec_t> *, float_t, float_t, int,
                       int);

void read_mnist_labels(const string, vector<label_t> *);

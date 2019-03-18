#include "read_mnist.h"

/**
 * check endian
 **/
inline bool is_little_endian() {
    uint16_t x = 0x0001;
    return *reinterpret_cast<uint8_t *>(&x) != 0;
}

inline void read_mnist_header(ifstream &fin, mnist_header &header) {
    fin.read(reinterpret_cast<char *>(&header.magic_number), 4);
    fin.read(reinterpret_cast<char *>(&header.num_items), 4);
    fin.read(reinterpret_cast<char *>(&header.num_rows), 4);
    fin.read(reinterpret_cast<char *>(&header.num_cols), 4);

    if (is_little_endian()) {
        reverse_endian(&header.magic_number);
        reverse_endian(&header.num_items);
        reverse_endian(&header.num_rows);
        reverse_endian(&header.num_cols);
    }

    if (header.magic_number != 0x00000803 || header.num_items <= 0)
        cout << "MNIST image-file header error" << endl;

    if (fin.fail() || fin.bad())
        cout << "file error" << endl;
}

void parse_mnist_image(std::ifstream &fin,
                       const mnist_header &header,
                       float_t scale_min,
                       float_t scale_max,
                       int x_padding,
                       int y_padding,
                       vec_t &dst) {
    const int width = header.num_cols + 2 * x_padding;
    const int height = header.num_rows + 2 * y_padding;

    std::vector<uint8_t> image_vec(header.num_rows * header.num_cols);

    fin.read(reinterpret_cast<char *>(&image_vec[0]),
             header.num_rows * header.num_cols);

    // for (uint32_t y = 0; y < header.num_rows; y++) {
    //     for (uint32_t x = 0; x < header.num_cols; x++) {
    //         printf("%3d ", image_vec[y * header.num_cols + x]);
    //     }
    //     cout << endl;
    // }

    // fgetc(stdin);

    // 28*28 -> 32*32
    dst.resize(width * height, scale_min);

    for (uint32_t y = 0; y < header.num_rows; y++) {
        for (uint32_t x = 0; x < header.num_cols; x++) {
            dst[width * (y + y_padding) + x + x_padding] =
                (image_vec[y * header.num_cols + x] / float_t(255)) *
                    (scale_max - scale_min) +
                scale_min;

            if ((image_vec[y * header.num_cols + x] / float_t(255)) *
                        (scale_max - scale_min) +
                    scale_min !=
                -1) {
                ;
                // cout << y << " " << x << endl;
                // fgetc(stdin);
            }
        }
    }
}

/**
 * parse MNIST database format images with rescaling/resizing
 * http://yann.lecun.com/exdb/mnist/
 * - if original image size is WxH, output size is
 *(W+2*x_padding)x(H+2*y_padding)
 * - extra padding pixels are filled with scale_min
 *
 * @param image_file [in]  filename of database (i.e.train-images-idx3-ubyte)
 * @param images     [out] parsed image data
 * @param scale_min  [in]  min-value of output
 * @param scale_max  [in]  max-value of output
 * @param x_padding  [in]  adding border width (left,right)
 * @param y_padding  [in]  adding border width (top,bottom)
 *
 * [example]
 * scale_min=-1.0, scale_max=1.0, x_padding=1, y_padding=0
 *
 * [input]       [output]
 *  64  64  64   -1.0 -0.5 -0.5 -0.5 -1.0
 * 128 128 128   -1.0  0.0  0.0  0.0 -1.0
 * 255 255 255   -1.0  1.0  1.0  1.0 -1.0
 *
 **/
void read_mnist_images(const string &image_file,
                       vector<vec_t> *images,
                       float_t scale_min,
                       float_t scale_max,
                       int x_padding,
                       int y_padding) {
    if (x_padding < 0 || y_padding < 0)
        cout << "padding size must not be negative" << endl;
    if (scale_min >= scale_max)
        cout << "scale_max must be greater than scale_min" << endl;

    ifstream fin(image_file.c_str(), std::ios::in | std::ios::binary);

    if (fin.bad() || fin.fail())
        cout << "failed to open file:" + image_file << endl;

    mnist_header header;

    read_mnist_header(fin, header);

    images->resize(header.num_items);
    for (uint32_t i = 0; i < header.num_items; i++) {
        vec_t image;
        parse_mnist_image(
            fin, header, scale_min, scale_max, x_padding, y_padding, image);
        (*images)[i] = image;
    }
}

/**
 * read label file
 * http://yann.lecun.com/exdb/mnist/
 *
 * @param label_file [in]  filename of database (i.e.train-labels-idx1-ubyte)
 * @param labels     [out] parsed label data
 **/
void read_mnist_labels(const string label_file, vector<label_t> *labels) {
    ifstream fin(label_file.c_str(), std::ios::in | std::ios::binary);

    if (fin.bad() || fin.fail())
        cout << "failed to open file: " << label_file << endl;

    uint32_t magic_number, num_items;

    fin.read(reinterpret_cast<char *>(&magic_number), 4);
    fin.read(reinterpret_cast<char *>(&num_items), 4);

    if (is_little_endian()) {  // MNIST data is big-endian format
        reverse_endian(&magic_number);
        reverse_endian(&num_items);
    }

    if (magic_number != 0x00000801 || num_items <= 0)
        cout << "MNIST label-file header error" << endl;

    labels->resize(num_items);
    for (uint32_t i = 0; i < num_items; i++) {
        uint8_t label;
        fin.read(reinterpret_cast<char *>(&label), 1);
        (*labels)[i] = static_cast<label_t>(label);
    }
}

void print_vec(vec_t vec) {
    size_t width = sqrt(vec.size());

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < width; ++j) {
            cout << vec[i * width + j] << " ";
        }
        cout << endl;
    }
}
#include <algorithm>
#include <string>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "image.hpp"

qimg::image &qimg::image::operator|=(const image &rhs) {
  if (
    (w != rhs.w) ||
    (h != rhs.h) ||
    (ch != rhs.ch)
  ) {
    throw std::invalid_argument("Images must be the same dimensions");
  }

  for (int i = 0; i < (w * h * ch); ++i) {
    data[i] |= rhs.data[i];
  }

  return *this;
}

qimg::image qimg::load_image(const char *path) {
  image img;

  unsigned char *data = stbi_load(path, &img.w, &img.h, &img.ch, 0);

  int data_size = img.w * img.h * img.ch;
  img.data.assign(data, data + data_size);

  stbi_image_free(data);

  return img;
}

bool qimg::save_image_png(const image &img, const std::string &path) {
  return stbi_write_png(
    path.c_str(), img.w, img.h, img.ch, img.data.data(), img.w * img.ch
  );
}

qimg::image qimg::copy_image(const image &img) {
  image a;

  a.w = img.w;
  a.h = img.h;
  a.ch = img.ch;
  a.data = img.data;

  return a;
}
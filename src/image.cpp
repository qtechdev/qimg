#include <algorithm>
#include <string>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "image.hpp"

qimg::pixel &qimg::pixel::operator|=(const pixel &rhs) {
  r |= rhs.r;
  g |= rhs.g;
  b |= rhs.b;

  return *this;
}

qimg::pixel &qimg::pixel::operator+=(const pixel &rhs) {
  r += rhs.r;
  g += rhs.g;
  b += rhs.b;

  return *this;
}

qimg::pixel &qimg::pixel::operator*=(const float &rhs) {
  r = std::clamp<int>(r * rhs, 0, 255);
  g = std::clamp<int>(g * rhs, 0, 255);
  b = std::clamp<int>(b * rhs, 0, 255);

  return *this;
}

qimg::image &qimg::image::operator|=(const image &rhs) {
  if (
    (w != rhs.w) ||
    (h != rhs.h)
  ) {
    throw std::invalid_argument("Images must be the same dimensions");
  }

  for (int i = 0; i < (w * h); ++i) {
    data[i] |= rhs.data[i];
  }

  return *this;
}

qimg::image qimg::load_image(const std::string &path) {
  image img;
  int ch;

  unsigned char *data = stbi_load(path.c_str(), &img.w, &img.h, &ch, 3);

  if (ch != 3) {
    throw std::invalid_argument("Image must have three colour channels");
  }

  int data_size = img.w * img.h * 3;

  for (int i = 0; i < data_size; i += 3) {
    img.data.push_back({data[i], data[i + 1], data[i + 2]});
  }

  stbi_image_free(data);

  return img;
}

bool qimg::save_image_png(const image &img, const std::string &path) {
  std::vector<unsigned char> data;
  for (auto &p : img.data) {
    data.push_back(p.r);
    data.push_back(p.g);
    data.push_back(p.b);
  }

  return stbi_write_png(
    path.c_str(), img.w, img.h, 3, data.data(), img.w * 3
  );
}

qimg::image qimg::copy_image(const image &img) {
  image a;

  a.w = img.w;
  a.h = img.h;
  a.data = img.data;

  return a;
}

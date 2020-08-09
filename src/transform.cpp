#include <cmath>
#include <cstdint>
#include <functional>

#include "image.hpp"
#include "transform.hpp"

void qimg::transform(image &img, const tx_func &f, const uint8_t data) {
  for (int y = 0; y < img.h; ++y) {
    for (int x = 0; x < img.w; ++x) {
      int pixel_index = (y * img.w) + x;

      pixel p = img.data[pixel_index];
      pixel new_p;

      f(p.r, p.g, p.b, new_p.r, new_p.g, new_p.b, data);

      img.data[pixel_index].r = new_p.r;
      img.data[pixel_index].g = new_p.g;
      img.data[pixel_index].b = new_p.b;
    }
  }
}

void qimg::greyscale(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  [[maybe_unused]] const uint8_t data
) {
  uint8_t grey = (r * 0.3) + (g * 0.59) + (b * 0.11);

  new_r = grey;
  new_g = grey;
  new_b = grey;
}

void qimg::mask(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  const uint8_t data
) {
  new_r = r & data;
  new_g = g & data;
  new_b = b & data;
}

void qimg::shrink(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  const uint8_t data
) {
  float factor = 255 / (1 << (data - 1));

  new_r = std::round(r / factor);
  new_g = std::round(g / factor);
  new_b = std::round(b / factor);
}

void qimg::expand(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  const uint8_t data
) {
  float factor = 255 / (1 << (data - 1));

  new_r = r * factor;
  new_g = g * factor;
  new_b = b * factor;
}

void qimg::split(
  const uint8_t r, [[maybe_unused]] const uint8_t g, [[maybe_unused]] const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  [[maybe_unused]] const uint8_t data
) {
  new_r = (r & 0b00110000) >> 4;
  new_g = (r & 0b00001100) >> 2;
  new_b = (r & 0b00000011);
}

void qimg::combine(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  [[maybe_unused]] const uint8_t data
) {
  uint8_t grey = (
    ((r & 0b00000011) << 4) |
    ((g & 0b00000011) << 2) |
     (b & 0b00000011)
  );

  new_r = grey;
  new_g = grey;
  new_b = grey;
}

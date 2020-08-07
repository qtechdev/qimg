#include <cmath>
#include <cstdint>
#include <functional>

#include "image.hpp"
#include "transform.hpp"

void tx::transform(qimg::image &img, const tx_func &f, const uint8_t data) {
  for (int y = 0; y < img.h; ++y) {
    for (int x = 0; x < img.w; ++x) {
      int pixel_index = ((y * img.w) + x) * img.ch;

      uint8_t r = img.data[pixel_index    ];
      uint8_t g = img.data[pixel_index + 1];
      uint8_t b = img.data[pixel_index + 2];
      uint8_t new_r;
      uint8_t new_g;
      uint8_t new_b;

      f(r, g, b, new_r, new_g, new_b, data);

      img.data[pixel_index    ] = new_r;
      img.data[pixel_index + 1] = new_g;
      img.data[pixel_index + 2] = new_b;
    }
  }
}

void tx::greyscale(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  [[maybe_unused]] const uint8_t data
) {
  uint8_t grey = (r * 0.3) + (g * 0.59) + (b * 0.11);

  new_r = grey;
  new_g = grey;
  new_b = grey;
}

void tx::mask(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  const uint8_t data
) {
  new_r = r & data;
  new_g = g & data;
  new_b = b & data;
}

void tx::shrink(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  const uint8_t data
) {
  float factor = 255 / (1 << (data - 1));

  new_r = std::round(r / factor);
  new_g = std::round(g / factor);
  new_b = std::round(b / factor);
}

void tx::expand(
  const uint8_t r, const uint8_t g, const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  const uint8_t data
) {
  float factor = 255 / (1 << (data - 1));

  new_r = r * factor;
  new_g = g * factor;
  new_b = b * factor;
}

void tx::split(
  const uint8_t r, [[maybe_unused]] const uint8_t g, [[maybe_unused]] const uint8_t b,
  uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
  [[maybe_unused]] const uint8_t data
) {
  new_r = (r & 0b00110000) >> 4;
  new_g = (r & 0b00001100) >> 2;
  new_b = (r & 0b00000011);
}

void tx::combine(
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

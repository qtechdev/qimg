#include <cstdint>

#include "image.hpp"
#include "ktransform.hpp"

void qimg::transform(image &img, const tx_kernel_func &f, const uint8_t data) {
  for (int y = 0; y < img.h; ++y) {
    for (int x = 0; x < img.w; ++x) {
      mat3 m = getmat3(img, x, y);
      pixel new_pixel;

      f(m, new_pixel, data);

      int pixel_index = (y * img.w) + x;
      img.data[pixel_index] = new_pixel;
    }
  }
}

void qimg::transform(image &img, const tx_kernel5_func &f, const uint8_t data) {
  for (int y = 0; y < img.h; ++y) {
    for (int x = 0; x < img.w; ++x) {
      mat5 m = getmat5(img, x, y);
      pixel new_pixel;

      f(m, new_pixel, data);

      int pixel_index = (y * img.w) + x;
      img.data[pixel_index] = new_pixel;
    }
  }
}

void qimg::identity(
  const mat3 &m, pixel &new_pixel, [[maybe_unused]] const uint8_t data
) {
  kernel3 k = {0, 0, 0, 0, 1, 0, 0, 0, 0};

  pixel p;

  for (int i = 0; i < 9; ++i) {
    p += m.p[i] * k.p[i];
  }

  new_pixel = p;
}

void qimg::blur(
  const mat3 &m, pixel &new_pixel, const uint8_t data
) {
  kernel3 k;
  float x;

  switch (data) {
    case 1:
      k = {
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
      };
      x = 16.0;
      break;
    case 0: default:
      k = {
        1, 1, 1,
        1, 1, 1,
        1, 1, 1
      };
      x = 9.0;
  }

  pixel p;

  for (int i = 0; i < 9; ++i) {
    p += m.p[i] * (k.p[i] / x);
  }

  new_pixel = p;
}

void qimg::blur5(
  const mat5 &m, pixel &new_pixel, const uint8_t data
) {
  kernel5 k;
  float x;

  switch (data) {
    case 1:
      k = {
        1,  4,  6,  4, 1,
        4, 16, 24, 16, 4,
        6, 24, 36, 24, 6,
        4, 16, 24, 16, 4,
        1,  4,  6,  4, 1
      };
      x = 256.0;
      break;
    case 0: default:
      k = {
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1
      };
      x = 25.0;
  }

  pixel p;

  for (int i = 0; i < 25; ++i) {
    p += m.p[i] * (k.p[i] / x);
  }

  new_pixel = p;
}

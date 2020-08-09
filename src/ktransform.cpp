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

void qimg::identity(
  const mat3 &m, pixel &new_pixel, [[maybe_unused]] const uint8_t data
) {
  kernel3 k = {0, 0, 0, 0, 1, 0, 0, 0, 0};

  pixel p;

  for (int i = 0; i <= 8; i++) {
    p += m.p[i] * k.p[i];
  }

  new_pixel = p;
}

void qimg::blur(
  const mat3 &m, pixel &new_pixel, const uint8_t data
) {
  kernel3 k;

  switch (data) {
    case 1:
      k = {
        1 / 16.0, 2 / 16.0, 1 / 16.0,
        2 / 16.0, 4 / 16.0, 2 / 16.0,
        1 / 16.0, 2 / 16.0, 1 / 16.0
      };
      break;
    case 0: default:
      k = {
        1 / 9.0, 1 / 9.0, 1 / 9.0,
        1 / 9.0, 1 / 9.0, 1 / 9.0,
        1 / 9.0, 1 / 9.0, 1 / 9.0
      };
  }

  pixel p;

  for (int i = 0; i <= 8; i++) {
    p += m.p[i] * k.p[i];
  }

  new_pixel = p;
}

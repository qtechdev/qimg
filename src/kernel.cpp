#include <algorithm>
#include <iostream>

#include <cstdint>

#include "image.hpp"

#include "kernel.hpp"

qimg::mat3 qimg::getmat3(const image &img, int x, int y) {
  mat3 m;

  for (int j = -1; j <= 1; ++j) {
    int y_pos = std::clamp(y + j, 0, img.h);

    for (int i = -1; i <= 1; ++i) {
      int x_pos = std::clamp(x + i, 0, img.w);

      int index = (i + 1) + ((j + 1) * 3);

      m.p[index] = img.data[(x_pos) + (y_pos * img.w)];
    }
  }

  return m;
}

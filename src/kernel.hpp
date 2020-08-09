#ifndef __KERNEL_HPP__
#define __KERNEL_HPP__

#include <cstdint>

#include "image.hpp"

namespace qimg {
  struct mat3 {
    pixel p[9];
  };

  struct kernel3 {
    float p[9];
  };

  mat3 getmat3(const image &img, int x, int y);
}

#endif // __KERNEL_HPP__

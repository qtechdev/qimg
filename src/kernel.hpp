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

  struct mat5 {
    pixel p[25];
  };

  struct kernel5 {
    float p[25];
  };

  mat5 getmat5(const image &img, int x, int y);
}

#endif // __KERNEL_HPP__

#ifndef __KTRANSFORM_HPP__
#define __KTRANSFORM_HPP__

#include <cstdint>
#include <functional>

#include "image.hpp"
#include "kernel.hpp"

namespace qimg {
  using tx_kernel_func = std::function<void(
    const mat3 &m, pixel &new_pixel, const uint8_t data
  )>;

  void transform(image &img, const tx_kernel_func &f, const uint8_t data=0);

  void identity(
    const mat3 &m, pixel &new_pixel, const uint8_t data
  );
  void blur(
    const mat3 &m, pixel &new_pixel, const uint8_t data
  );
}

#endif // __KTRANSFORM_HPP__

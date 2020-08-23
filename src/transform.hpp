#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__
#include <cstdint>
#include <functional>

#include "image.hpp"

namespace qimg {
  using tx_func = std::function<void(
    const uint8_t r, const uint8_t g, const uint8_t b,
    uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
    const uint8_t data
  )>;

  void transform(image &img, const tx_func &f, const uint8_t data=0);

  void greyscale(
    const uint8_t r, const uint8_t g, const uint8_t b,
    uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
    const uint8_t data=0
  );
  void mask(
    const uint8_t r, const uint8_t g, const uint8_t b,
    uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
    const uint8_t data=0
  );
  void shrink(
    const uint8_t r, const uint8_t g, const uint8_t b,
    uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
    const uint8_t data=0
  );
  void expand(
    const uint8_t r, const uint8_t g, const uint8_t b,
    uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
    const uint8_t data=0
  );
  void split(
    const uint8_t r, const uint8_t g, const uint8_t b,
    uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
    const uint8_t data=0
  );
  void combine(
    const uint8_t r, const uint8_t g, const uint8_t b,
    uint8_t &new_r, uint8_t &new_g, uint8_t &new_b,
    const uint8_t data=0
  );
}

#endif // __TRANSFORM_HPP__

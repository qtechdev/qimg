#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include "image.hpp"

namespace tx {
  void grey(qimg::image &img);

  void quantise(qimg::image &img, const int levels);
  void shrink(qimg::image &img, const int levels);
  void expand(qimg::image &img, const int levels);

  void mask(qimg::image &img, const unsigned char count);
}

#endif // __TRANSFORM_HPP__

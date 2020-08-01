#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include "image.hpp"

namespace tx {
  void grey(qimg::image &img);
  void quantise(qimg::image &img, const int levels);
}

#endif // __TRANSFORM_HPP__

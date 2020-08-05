#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__
#include <string>
#include <vector>

namespace qimg {
  struct image {
    int w;
    int h;
    int ch;
    std::vector<unsigned char> data;

    image &operator|=(const image &rhs);
  };

  inline image operator|(image lhs, const image &rhs) { return lhs |= rhs; }

  image load_image(const std::string &p);
  bool save_image_png(const image &img, const std::string &path);
  image copy_image(const image &img);
}

#endif // __IMAGE_HPP__

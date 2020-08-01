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
  };

  image load_image(const char *p);
  bool save_image_png(const image &img, const std::string &path);
  image copy_image(const image &img);
}

#endif // __IMAGE_HPP__

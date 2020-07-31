#include <algorithm>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "image.hpp"

image load_image(const char *path) {
  image img;

  unsigned char *data = stbi_load(path, &img.w, &img.h, &img.ch, 0);

  int data_size = img.w * img.h * img.ch;
  img.data.assign(data, data + data_size);

  stbi_image_free(data);

  return img;
}

bool save_image_png(const image &img, const std::string &path) {
  return stbi_write_png(
    path.c_str(), img.w, img.h, img.ch, img.data.data(), img.w * img.ch
  );
}

image copy_image(const image &img) {
  image a;

  a.w = img.w;
  a.h = img.h;
  a.ch = img.ch;
  a.data = img.data;

  return a;
}

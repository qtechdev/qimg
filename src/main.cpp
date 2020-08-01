#include <iostream>

#include "image.hpp"
#include "transform.hpp"

int main(int argc, const char *argv[]) {
  qimg::image img = qimg::load_image("data/kitten.png");

  std::cout << "image size: " << img.w << " by " << img.h << "\n";
  std::cout << "number of channels: " << img.ch << "\n";

  qimg::image copy = qimg::copy_image(img);
  tx::grey(copy);

  qimg::save_image_png(copy, "data/out.png");

  return 0;
}

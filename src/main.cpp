#include <iostream>

#include "image.hpp"

int main(int argc, const char *argv[]) {
  image img = load_image("data/kitten.png");

  std::cout << "image size: " << img.w << " by " << img.h << "\n";
  std::cout << "number of channels: " << img.ch << "\n";

  image copy = copy_image(img);

  for (int y = 0; y < copy.h; ++y) {
    for (int x = 0; x < copy.w; ++x) {
      int pixel_index = ((y * copy.w) + x) * copy.ch;

      float r = copy.data[pixel_index];
      float g = copy.data[pixel_index + 1];
      float b = copy.data[pixel_index + 2];

      float grey = (r * 0.3) + (g * 0.59) + (b * 0.11);

      copy.data[pixel_index] = grey;
      copy.data[pixel_index + 1] = grey;
      copy.data[pixel_index + 2] = grey;
    }
  }

  save_image_png(copy, "data/out.png");

  return 0;
}

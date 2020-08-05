#include <bitset>
#include <iostream>

#include "image.hpp"
#include "transform.hpp"

int main(int argc, const char *argv[]) {
  qimg::image carrier = qimg::load_image("data/kitten.png");
  qimg::image secret  = qimg::load_image("data/kitten2.png");

  std::cout << "image size: " << carrier.w << " by " << carrier.h << "\n";
  std::cout << "number of channels: " << carrier.ch << "\n";

  std::cout << "image size: " << secret.w << " by " << secret.h << "\n";
  std::cout << "number of channels: " << secret.ch << "\n";

  if (
    (carrier.w != secret.w) ||
    (carrier.h != secret.h) ||
    (carrier.ch != secret.ch)
  ) {
    std::cerr << "Images must be the same dimensions\n";
    return 1;
  }

  tx::mask(carrier, 0b11111100);
  tx::shrink(secret,  2);

  qimg::image output = carrier | secret;

  qimg::save_image_png(output, "data/out.png");

  return 0;
}

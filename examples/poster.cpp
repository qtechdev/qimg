#include <iostream>
#include <utility> // pair
#include <vector>

#include <qarg/qarg.hpp>

#include "image.hpp"
#include "transform.hpp"

using operation_list = std::vector<std::pair<tx::tx_func, uint8_t>>;
static const operation_list op_list = {
  {tx::shrink, 4},
  {tx::expand, 4},
};

int manip(const std::string &c, const std::string &o, const bool verbose);

int main([[maybe_unused]] int argc, [[maybe_unused]] const char *argv[]) {
  qarg::parser args;
  args.add<bool>('h', "display this text");
  args.add<bool>('v', "verbose");
  args.add<std::string>('i', "input file", true);
  args.add<std::string>('o', "output file", true);

  int c = 5;
  const char *v[] = {
    "poster",
    "-i",
    "data/kitten.png",
    "-o",
    "data/out.png"
  };

  try {
    args.parse(c, v);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << "\n";
    std::cerr << args.help();
    return 1;
  }

  if (*args.get<bool>('h')) {
    std::cout << args.help();
    return 0;
  }

  std::string input_filepath = *args.get<std::string>('i');
  std::string output_filepath = *args.get<std::string>('o');

  manip(input_filepath, output_filepath, *args.get<bool>('v'));
}

int manip(const std::string &c, const std::string &o, const bool verbose) {
  qimg::image img = qimg::load_image(c);

  if (verbose) {
    std::cout << "image size: " << img.w << " by " << img.h << "\n";
    std::cout << "number of channels: " << img.ch << "\n";
  }

  for (const auto &[f, v] : op_list) {
    tx::transform(img, f, v);
  }

  qimg::save_image_png(img, o);

  return 0;
}

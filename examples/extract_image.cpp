#include <iostream>
#include <utility> // pair
#include <vector>

#include <qarg/qarg.hpp>

#include "image.hpp"
#include "transform.hpp"

using op_list = std::vector<std::pair<qimg::tx_func, uint8_t>>;

// #define CONVERT_TO_GREYSCALE
#ifdef CONVERT_TO_GREYSCALE
constexpr uint8_t bit_mask = 0b00000011;
static const op_list op_ex = {
  {qimg::combine, 0},
  {qimg::expand, 6}
};
#else
constexpr uint8_t bit_mask = 0b00001111;
static const op_list op_ex = {
  {qimg::expand, 4}
};
#endif

int extract(const std::string &c, const std::string &o);
int insert(
  const std::string &c, const std::string &o, const std::string &s,
  bool verbose=false
);

int main([[maybe_unused]] int argc, [[maybe_unused]] const char *argv[]) {
  qarg::parser args;
  args.add<bool>('h', "display this text");
  args.add<bool>('v', "verbose");
  args.add<std::string>('i', "input file", true);
  args.add<std::string>('o', "output file", true);

  int c = 5;
  const char *v[] = {
    "extract_image",
    "-i",
    "data/out.png",
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

  if (auto h = args.get<bool>('h'); h && *h) {
    std::cout << args.help();
    return 0;
  }

  std::string carrier_filepath = *args.get<std::string>('i');
  std::string output_filepath = *args.get<std::string>('o');

  return extract(carrier_filepath, output_filepath);
}

int extract(const std::string &c, const std::string &o) {
  qimg::image hidden = qimg::load_image(c);

  qimg::transform(hidden, qimg::mask, bit_mask);

  for (const auto &[f, v] : op_ex) {
    qimg::transform(hidden, f, v);
  }

  qimg::save_image_png(hidden, o);

  return 0;
}

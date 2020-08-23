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
static const op_list op_in = {
  {qimg::greyscale, 0},
  {qimg::shrink, 6},
  {qimg::split, 0}
};
#else
constexpr uint8_t bit_mask = 0b00001111;
static const op_list op_in = {
  {qimg::shrink, 4},
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
  args.add<std::string>('s', "secret file", true);

  int c = 7;
  const char *v[] = {
    "hide_image",
    "-i",
    "data/kitten.png",
    "-s",
    "data/kitten2.png",
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
  std::string secret_filepath = *args.get<std::string>('s');

  return insert(
    carrier_filepath, output_filepath, secret_filepath, *args.get<bool>('v')
  );
}

int insert(
  const std::string &c, const std::string &o, const std::string &s,
  bool verbose
) {
  qimg::image carrier = qimg::load_image(c);
  qimg::image secret  = qimg::load_image(s);

  if (verbose) {
    std::cout << "carrier image size: " << carrier.w << " by " << carrier.h << "\n";
    std::cout << "secret image size: " << secret.w << " by " << secret.h << "\n";
  }

  if (
    (carrier.w != secret.w) ||
    (carrier.h != secret.h)
  ) {
    std::cerr << "Images must be the same dimensions\n";
    return 1;
  }

  qimg::transform(carrier, qimg::mask, ~bit_mask);

  for (const auto &[f, v] : op_in) {
    qimg::transform(secret, f, v);
  }

  secret |= carrier;

  qimg::save_image_png(secret, o);

  return 0;
}

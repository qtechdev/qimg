#include <iostream>

#include <qarg/qarg.hpp>

#include "image.hpp"
#include "transform.hpp"

int extract(const std::string &c, const std::string &o);
int insert(const std::string &c, const std::string &o, const std::string &s);

int main(int argc, const char *argv[]) {
  qarg::parser args;
  args.add<bool>('h', "display this text");
  args.add<bool>('x', "extract hidden image");
  args.add<std::string>('i', "input file", true);
  args.add<std::string>('o', "output file", true);
  args.add<std::string>('s', "secret file");

  try {
    args.parse(argc, argv);
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

  bool do_extraction = *args.get<bool>('x');

  std::string secret_filepath;
  if (!do_extraction) {
    auto args_s = args.get<std::string>('s');
    if (!args_s) {
      std::cerr << "please specify one of -s, -x\n";
      return 2;
    } else {
      secret_filepath = *args_s;
    }
  }

  if (do_extraction) {
    return extract(carrier_filepath, output_filepath);
  } else {
    return insert(carrier_filepath, output_filepath, secret_filepath);
  }
}

int extract(const std::string &c, const std::string &o) {
  qimg::image hidden = qimg::load_image(c);

  tx::transform(hidden, tx::mask, 0b00001111);
  tx::transform(hidden, tx::expand, 4);

  qimg::save_image_png(hidden, o);

  return 0;
}


int insert(const std::string &c, const std::string &o, const std::string &s) {
  qimg::image carrier = qimg::load_image(c);
  qimg::image secret  = qimg::load_image(s);

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

  tx::transform(carrier, tx::mask, 0b11110000);
  tx::transform(secret, tx::shrink, 4);

  qimg::image output = carrier | secret;

  qimg::save_image_png(output, o);

  return 0;
}

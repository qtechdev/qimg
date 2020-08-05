#include <cmath>

#include "image.hpp"
#include "transform.hpp"

void tx::grey(qimg::image &img) {
  for (int y = 0; y < img.h; ++y) {
    for (int x = 0; x < img.w; ++x) {
      int pixel_index = ((y * img.w) + x) * img.ch;

      float r = img.data[pixel_index    ];
      float g = img.data[pixel_index + 1];
      float b = img.data[pixel_index + 2];

      unsigned char grey = (r * 0.3) + (g * 0.59) + (b * 0.11);

      img.data[pixel_index    ] = grey;
      img.data[pixel_index + 1] = grey;
      img.data[pixel_index + 2] = grey;
    }
  }
}

void tx::quantise(qimg::image &img, const int levels) {
  shrink(img, levels);
  expand(img, levels);
}

void tx::shrink(qimg::image &img, const int bits) {
  const int levels = 1 << (bits - 1);

  for (int y = 0; y < img.h; ++y) {
    for (int x = 0; x < img.w; ++x) {
      int pixel_index = ((y * img.w) + x) * img.ch;

      float r = img.data[pixel_index    ];
      float g = img.data[pixel_index + 1];
      float b = img.data[pixel_index + 2];

      float factor = 255 / (levels - 1);

      img.data[pixel_index    ] = std::round(r / factor);
      img.data[pixel_index + 1] = std::round(g / factor);
      img.data[pixel_index + 2] = std::round(b / factor);
    }
  }
}

void tx::expand(qimg::image &img, const int bits) {
  const int levels = 1 << (bits - 1);

  for (int y = 0; y < img.h; ++y) {
    for (int x = 0; x < img.w; ++x) {
      int pixel_index = ((y * img.w) + x) * img.ch;

      float r = img.data[pixel_index    ];
      float g = img.data[pixel_index + 1];
      float b = img.data[pixel_index + 2];

      float factor = 255 / (levels - 1);

      img.data[pixel_index    ] = r * factor;
      img.data[pixel_index + 1] = g * factor;
      img.data[pixel_index + 2] = b * factor;
    }
  }
}

void tx::mask(qimg::image &img, const unsigned char m) {
  for (int y = 0; y < img.h; ++y) {
    for (int x = 0; x < img.w; ++x) {
      int pixel_index = ((y * img.w) + x) * img.ch;

      unsigned char r = img.data[pixel_index    ];
      unsigned char g = img.data[pixel_index + 1];
      unsigned char b = img.data[pixel_index + 2];

      img.data[pixel_index    ] = r & m;
      img.data[pixel_index + 1] = g & m;
      img.data[pixel_index + 2] = b & m;
    }
  }
}

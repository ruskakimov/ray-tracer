#include <stdio.h>
#include <stdlib.h>
#include "utils/image.h"

int main() {
  ImageHandle img = image_make(256, 256);

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      uint8_t red = 255 * c / img.width;
      uint8_t green = 255 * r / img.height;
      Pixel pixel = { red, green, 64 };
      *(img.pixels + r * img.width + c) = pixel;
    }
  }

  image_printAsPPM(&img);
  free(img.pixels);
}

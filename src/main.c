#include <stdio.h>
#include <stdlib.h>
#include "utils/image.h"
#include "utils/math.h"

int main() {
  ImageHandle img = image_make(400, 300);
  Sphere sphere = { .center = { 0.0, 0.0, -20.0 }, .radius = 8.0 };

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      // shoot ray from 0,0,0 through pixel
      // color red if hit
      uint8_t red = 255 * c / img.width;
      uint8_t green = 255 * r / img.height;
      Pixel pixel = { red, green, 64 };
      *(img.pixels + r * img.width + c) = pixel;
    }
  }

  image_printAsPPM(&img);
  free(img.pixels);
}

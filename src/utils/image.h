#pragma once

#include <cstdint>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Pixel;

typedef struct {
  uint32_t width;
  uint32_t height;
  Pixel* pixels;
} ImageHandle;

ImageHandle image_make(uint32_t width, uint32_t height);
void image_printAsPPM(ImageHandle* img);
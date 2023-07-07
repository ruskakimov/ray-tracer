#pragma once

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB;

typedef struct {
  uint32_t width;
  uint32_t height;
  RGB* pixels;
} ImageHandle;

void printImageAsPPM(ImageHandle img);
ImageHandle makeRandomNoiseImage(uint32_t width, uint32_t height);
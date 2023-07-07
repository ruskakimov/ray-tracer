#pragma once

struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct ImageHandle {
  uint32_t width;
  uint32_t height;
  struct RGB* pixels;
};

void printImageAsPPM(struct ImageHandle img);
struct ImageHandle makeRandomNoiseImage(uint32_t width, uint32_t height);
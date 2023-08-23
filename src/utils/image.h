#pragma once

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;

typedef struct {
  int width;
  int height;
  Pixel* pixels;
} ImageHandle;

ImageHandle image_make(int width, int height);
void image_printAsPPM(ImageHandle* img);
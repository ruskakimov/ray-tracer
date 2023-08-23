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

ImageHandle make_image(int width, int height);
void print_image_as_ppm(ImageHandle* img);
#pragma once

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Color;

typedef struct {
  int width;
  int height;
  Color* pixels;
} ImageHandle;

ImageHandle make_image(int width, int height);
void print_image(ImageHandle* img);

Color lerp(Color c1, Color c2, double a);

#include <stdlib.h>
#include <stdio.h>
#include "image.h"

ImageHandle make_image(int width, int height) {
  Pixel* pixels = (Pixel*)malloc((width * height) * sizeof(Pixel));
  return (ImageHandle) { width, height, pixels };
}

void print_image(ImageHandle* img) {
  printf("P3\n");
  printf("%d %d\n", img->width, img->height);
  printf("%d\n", 255);

  Pixel* p = img->pixels;
  Pixel* end_p = img->pixels + (img->width * img->height);
  while (p < end_p) {
    printf("%d %d %d\n", p->r, p->g, p->b);
    p++;
  }
}
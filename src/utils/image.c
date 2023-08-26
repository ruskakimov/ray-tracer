#include <stdlib.h>
#include <stdio.h>
#include "image.h"

ImageHandle make_image(int width, int height) {
  Color* pixels = (Color*)malloc((width * height) * sizeof(Color));
  return (ImageHandle) { width, height, pixels };
}

void print_image(ImageHandle* img) {
  printf("P3\n");
  printf("%d %d\n", img->width, img->height);
  printf("%d\n", 255);

  Color* p = img->pixels;
  Color* end_p = img->pixels + (img->width * img->height);
  while (p < end_p) {
    printf("%d %d %d\n", p->r, p->g, p->b);
    p++;
  }
}
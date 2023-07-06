#include <stdio.h>
#include <stdlib.h>
#include "image.h"

#define frand() ((double) rand() / (RAND_MAX+1.0))

void print_image_as_ppm(struct image_handle img) {
  printf("P3\n");
  printf("%d %d\n", img.width, img.height);
  printf("%d\n", 255); // max color

  struct rgb* p = img.pixels;
  struct rgb* end_p = img.pixels + (img.width * img.height);
  while (p < end_p) {
    printf("%d %d %d\n", p->r, p->g, p->b);
    p++;
  }
}

struct rgb make_random_color() {
  return (struct rgb) {
    (unsigned short)(frand() * 255.0),
      (unsigned short)(frand() * 255.0),
      (unsigned short)(frand() * 255.0),
  };
}

struct image_handle make_random_noise_image(int width, int height) {
  int pixel_count = width * height;
  struct rgb* pixels = malloc(pixel_count * sizeof(struct rgb));

  struct rgb* p = pixels;
  struct rgb* end_p = pixels + pixel_count;
  while (p < end_p) {
    *p = make_random_color();
    p++;
  }

  return (struct image_handle) { width, height, pixels };
}
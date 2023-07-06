#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main() {
  struct image_handle img_handle = make_random_noise_image(100, 100);
  print_image_as_ppm(img_handle);
  free(img_handle.pixels);
}

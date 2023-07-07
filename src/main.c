#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main() {
  ImageHandle img_handle = image_make(100, 100);
  image_printAsPPM(&img_handle);
  free(img_handle.pixels);
}

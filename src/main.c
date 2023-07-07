#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main() {
  ImageHandle img_handle = makeRandomNoiseImage(100, 100);
  printImageAsPPM(img_handle);
  free(img_handle.pixels);
}

#include <stdio.h>
#include <stdlib.h>
#include "utils/image.h"
#include "utils/math.h"
#include "utils/Vec3.h"

int main() {
  ImageHandle img = image_make(400, 300);
  Sphere sphere = { Vec3(0, 0, -20), 12 };

  Vec3 camera(0, 0, 0);
  Vec3 windowTopLeft(-4, 3, -2);
  Vec3 windowTopRight(4, 3, -2);
  Vec3 windowBottomLeft(-4, -3, -2);

  Vec3 windowRight = windowTopRight - windowTopLeft;
  Vec3 windowDown = windowBottomLeft - windowTopLeft;

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      double rightMult = (c + 0.5) / img.width;
      double downMult = (r + 0.5) / img.height;
      Vec3 right = windowRight * rightMult;
      Vec3 down = windowDown * downMult;
      Vec3 windowPoint = windowTopLeft + right + down;
      Ray ray = { .origin = camera, .dir = windowPoint - camera };
      double t = ray_sphereHitTime(ray, sphere);

      if (t > 0) {
        *(img.pixels + r * img.width + c) = (Pixel){ 255, 0, 0 };
      }
      else {
        *(img.pixels + r * img.width + c) = (Pixel){ 0, 0, 0 };
      }
    }
  }

  image_printAsPPM(&img);
  free(img.pixels);
}

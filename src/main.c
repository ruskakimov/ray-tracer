#include <stdlib.h>
#include <stdio.h>
#include "utils/image.h"
#include "utils/math.h"

int main() {
  ImageHandle img = make_image(400, 300);
  Sphere sphere = { (Vec3) { 0, 0, -20 }, 12 };

  Vec3 camera = { 0, 0, 0 };
  Vec3 windowTopLeft = { -4, 3, -2 };
  Vec3 windowTopRight = { 4, 3, -2 };
  Vec3 windowBottomLeft = { -4, -3, -2 };

  Vec3 windowRight = sub_vect(windowTopRight, windowTopLeft);
  Vec3 windowDown = sub_vect(windowBottomLeft, windowTopLeft);

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      double rightMult = (c + 0.5) / img.width;
      double downMult = (r + 0.5) / img.height;
      Vec3 right = mul_vect(windowRight, rightMult);
      Vec3 down = mul_vect(windowDown, downMult);
      Vec3 windowPoint = add_vect(windowTopLeft, add_vect(right, down));
      Ray ray = { camera, sub_vect(windowPoint, camera) };
      double t = ray_sphere_t(ray, sphere);

      if (t > 0) {
        *(img.pixels + r * img.width + c) = (Pixel){ 255, 0, 0 };
      }
      else {
        *(img.pixels + r * img.width + c) = (Pixel){ 0, 0, 0 };
      }
    }
  }

  print_image(&img);
  free(img.pixels);
}

#include <stdlib.h>
#include <stdio.h>
#include "utils/image.h"
#include "utils/math.h"

Vec3 lerp(Vec3 p1, Vec3 p2, double a) {
  double b = 1 - a;
  return add_vect(mul_vect(p1, b), mul_vect(p2, a));
}

Pixel vec_to_color(Vec3 v) {
  Vec3 rgb = mul_vect(v, 255);
  return (Pixel) { rgb.x, rgb.y, rgb.z };
}

Pixel sky_color(Ray ray) {
  Vec3 u = unit_vect(ray.dir);
  double a = (u.y + 1) / 2;
  Vec3 color1 = (Vec3){ 1.0, 1.0, 1.0 };
  Vec3 color2 = (Vec3){ 0.5, 0.7, 1.0 };
  return vec_to_color(lerp(color1, color2, a));
}

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

      *(img.pixels + r * img.width + c) = (t > 0) ? (Pixel) { 255, 0, 0 } : sky_color(ray);
    }
  }

  print_image(&img);
  free(img.pixels);
}

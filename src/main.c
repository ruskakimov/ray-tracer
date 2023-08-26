#include <stdlib.h>
#include <stdio.h>
#include "utils/image.h"
#include "utils/math.h"

Vec3 lerp(Vec3 p1, Vec3 p2, double a) {
  double b = 1 - a;
  return add_vec(mul_vec(p1, b), mul_vec(p2, a));
}

Color vec_to_color(Vec3 v) {
  Vec3 rgb = mul_vec(v, 255);
  return (Color) { rgb.x, rgb.y, rgb.z };
}

Color sky_color(Ray ray) {
  Vec3 u = unit_vec(ray.dir);
  double a = (u.y + 1.0) / 2.0;
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

  Vec3 windowRight = sub_vec(windowTopRight, windowTopLeft);
  Vec3 windowDown = sub_vec(windowBottomLeft, windowTopLeft);

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      double rightMult = (c + 0.5) / img.width;
      double downMult = (r + 0.5) / img.height;
      Vec3 right = mul_vec(windowRight, rightMult);
      Vec3 down = mul_vec(windowDown, downMult);
      Vec3 windowPoint = add_vec(windowTopLeft, add_vec(right, down));
      Ray ray = { camera, sub_vec(windowPoint, camera) };
      double t = ray_sphere_t(ray, sphere);

      *(img.pixels + r * img.width + c) = (t > 0) ? (Color) { 255, 0, 0 } : sky_color(ray);
    }
  }

  print_image(&img);
  free(img.pixels);
}

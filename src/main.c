#include <stdlib.h>
#include <stdio.h>
#include "utils/image.h"
#include "utils/math.h"

const Color skyColor1 = (Color){ 255, 255, 255 };
const Color skyColor2 = (Color){ 128, 179, 255 };

Color unit_vec_to_color(Vec3 v) {
  return (Color) {
    (v.x + 1.0) / 2.0 * 255.0,
      (v.y + 1.0) / 2.0 * 255.0,
      (v.z + 1.0) / 2.0 * 255.0,
  };
}

Color sky_color(Ray ray) {
  Vec3 u = unit_vec(ray.dir);
  double a = (u.y + 1.0) / 2.0;
  return lerp(skyColor1, skyColor2, a);
}

int main() {
  ImageHandle img = make_image(800, 600);
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

      Vec3 hitPoint = ray_point(ray, t);
      Vec3 surfaceNormal = div_vec(sub_vec(hitPoint, sphere.center), sphere.radius);
      Ray reflectedRay = (Ray){ hitPoint, surfaceNormal };

      *(img.pixels + r * img.width + c) = (t > 0) ? unit_vec_to_color(surfaceNormal) : sky_color(ray);
    }
  }

  print_image(&img);
  free(img.pixels);
}

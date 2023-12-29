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
  Vec3 u = vec_unit(ray.dir);
  double a = (u.y + 1.0) / 2.0;
  return lerp(skyColor1, skyColor2, a);
}

const Sphere spheres[] = {
  {.center = { 0, 0, -20 }, .radius = 12 },
  {.center = { -15, 0, -20 }, .radius = 3 },
  {.center = { 16, 0, -20 }, .radius = 4 },
};
const size_t sphereCount = sizeof(spheres) / sizeof(Sphere);

typedef struct {
  int hit;
  Color color;
} HitResult;

HitResult get_hit(Ray ray) {
  for (int i = 0; i < sphereCount; i++) {
    Sphere sphere = spheres[i];
    double t = ray_sphere_t(ray, sphere);
    if (t < 0) continue;

    Vec3 hitPoint = ray_point(ray, t);
    Vec3 surfaceNormal = vec_div(vec_sub(hitPoint, sphere.center), sphere.radius);
    Color color = unit_vec_to_color(surfaceNormal);
    return (HitResult) { .hit = 1, .color = color };
  }
  return (HitResult) { .hit = 0 };
}

int main() {
  ImageHandle img = make_image(800, 600);

  Vec3 camera = { 0, 0, 0 };
  Vec3 windowTopLeft = { -4, 3, -2 };
  Vec3 windowTopRight = { 4, 3, -2 };
  Vec3 windowBottomLeft = { -4, -3, -2 };

  Vec3 windowRight = vec_sub(windowTopRight, windowTopLeft);
  Vec3 windowDown = vec_sub(windowBottomLeft, windowTopLeft);

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      double rightMult = (c + 0.5) / img.width;
      double downMult = (r + 0.5) / img.height;
      Vec3 right = vec_mul(windowRight, rightMult);
      Vec3 down = vec_mul(windowDown, downMult);
      Vec3 windowPoint = vec_add(windowTopLeft, vec_add(right, down));
      Ray ray = { camera, vec_sub(windowPoint, camera) };

      HitResult hitResult = get_hit(ray);

      *(img.pixels + r * img.width + c) = hitResult.hit ? hitResult.color : sky_color(ray);
    }
  }

  print_image(&img);
  free(img.pixels);
}

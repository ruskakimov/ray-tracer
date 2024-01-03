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

Vec3 color2vec(Color color) {
  return (Vec3) { color.r, color.g, color.b };
}

Color vec2color(Vec3 vector) {
  return (Color) { vector.x, vector.y, vector.z };
}

const int ANTIALIAS_SAMPLES = 8;

int main() {
  ImageHandle img = make_image(800, 600);

  Vec3 camera = { 0, 0, 0 };
  Vec3 windowTopLeft = { -4, 3, -2 };
  Vec3 windowTopRight = { 4, 3, -2 };
  Vec3 windowBottomLeft = { -4, -3, -2 };

  Vec3 windowXAxis = vec_sub(windowTopRight, windowTopLeft);
  Vec3 windowYAxis = vec_sub(windowBottomLeft, windowTopLeft);

  Vec3 cellXAxis = vec_div(windowXAxis, img.width);
  Vec3 cellYAxis = vec_div(windowYAxis, img.height);

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      Vec3 rightOffset = vec_mul(windowXAxis, c / img.width);
      Vec3 downOffset = vec_mul(windowYAxis, r / img.height);
      Vec3 cellTopLeft = vec_add(windowTopLeft, vec_add(rightOffset, downOffset));

      Vec3 cellColorAcc = { 0,0,0 };

      for (int i = 0; i < ANTIALIAS_SAMPLES; i++) {
        Vec3 xOffset = vec_mul(cellXAxis, rnd());
        Vec3 yOffset = vec_mul(cellYAxis, rnd());
        Vec3 cellSample = vec_add(cellTopLeft, vec_add(xOffset, yOffset));

        Ray ray = { camera, vec_sub(cellSample, camera) };
        HitResult hitResult = get_hit(ray);

        Color color = hitResult.hit ? hitResult.color : sky_color(ray);
        cellColorAcc = vec_add(cellColorAcc, color2vec(color));
      }

      Color cellColor = vec2color(vec_div(cellColorAcc, ANTIALIAS_SAMPLES));
      *(img.pixels + r * img.width + c) = cellColor;
    }
  }

  print_image(&img);
  free(img.pixels);
}

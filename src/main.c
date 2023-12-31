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
  {.center = { 0, 0, -1 }, .radius = 0.5 },
  {.center = { -1, 0, -1 }, .radius = 0.5 },
  {.center = { 1, 0, -1 }, .radius = 0.5 },
  {.center = { 0, -100.5, -1 }, .radius = 100 },
};
const size_t sphereCount = sizeof(spheres) / sizeof(Sphere);

Vec3 color2vec(Color color) {
  return (Vec3) { color.r, color.g, color.b };
}

Color vec2color(Vec3 vector) {
  return (Color) { vector.x, vector.y, vector.z };
}

Color get_ray_color(Ray ray) {
  for (int i = 0; i < sphereCount; i++) {
    Sphere sphere = spheres[i];
    double t = ray_sphere_t(ray, sphere);

    if (t >= 0) {
      Vec3 hitPoint = ray_point(ray, t);
      Vec3 surfaceNormal = vec_div(vec_sub(hitPoint, sphere.center), sphere.radius);
      Vec3 reflectedDir = rnd_on_hemisphere(surfaceNormal);
      Ray reflectedRay = (Ray){ .dir = reflectedDir, .origin = hitPoint };
      return vec2color(vec_mul(color2vec(get_ray_color(reflectedRay)), 0.5));
    }
  }
  return sky_color(ray);
}

const int ANTIALIAS_SAMPLES = 32;

int main() {
  ImageHandle img = make_image(800, 600);

  double focal_length = 1.0;
  double viewport_h = 2.0;
  double viewport_w = viewport_h / (double)img.height * (double)img.width;
  Vec3 camera_center = { 0, 0, 0 };

  Vec3 focal_v = (Vec3){ 0, 0, -focal_length };
  Vec3 viewport_hv = (Vec3){ 0, -viewport_h, 0 };
  Vec3 viewport_wv = (Vec3){ viewport_w, 0, 0 };

  Vec3 windowTopLeft = vec_sub(vec_sub(vec_add(camera_center, focal_v), vec_div(viewport_hv, 2)), vec_div(viewport_wv, 2));
  Vec3 windowTopRight = vec_add(vec_sub(vec_add(camera_center, focal_v), vec_div(viewport_hv, 2)), vec_div(viewport_wv, 2));
  Vec3 windowBottomLeft = vec_sub(vec_add(vec_add(camera_center, focal_v), vec_div(viewport_hv, 2)), vec_div(viewport_wv, 2));

  Vec3 windowXAxis = vec_sub(windowTopRight, windowTopLeft);
  Vec3 windowYAxis = vec_sub(windowBottomLeft, windowTopLeft);

  Vec3 cellXAxis = vec_div(windowXAxis, img.width);
  Vec3 cellYAxis = vec_div(windowYAxis, img.height);

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      Vec3 xWindowOffset = vec_mul(windowXAxis, (double)c / img.width);
      Vec3 yWindowOffset = vec_mul(windowYAxis, (double)r / img.height);
      Vec3 cellTopLeft = vec_add(windowTopLeft, vec_add(xWindowOffset, yWindowOffset));

      Vec3 cellColorAcc = { 0,0,0 };

      for (int i = 0; i < ANTIALIAS_SAMPLES; i++) {
        Vec3 xCellOffset = vec_mul(cellXAxis, rnd());
        Vec3 yCellOffset = vec_mul(cellYAxis, rnd());
        Vec3 cellSample = vec_add(cellTopLeft, vec_add(xCellOffset, yCellOffset));

        Ray ray = { camera_center, vec_sub(cellSample, camera_center) };
        Color color = get_ray_color(ray);
        cellColorAcc = vec_add(cellColorAcc, color2vec(color));
      }

      Color cellColor = vec2color(vec_div(cellColorAcc, ANTIALIAS_SAMPLES));
      *(img.pixels + r * img.width + c) = cellColor;
    }
  }

  print_image(&img);
  free(img.pixels);
}

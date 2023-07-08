#include <stdio.h>
#include <stdlib.h>
#include "utils/image.h"
#include "utils/math.h"

int main() {
  ImageHandle img = image_make(400, 300);

  Sphere sphere = { .center = { 0, 0, -20 }, .radius = 12 };

  Vec3 camera = { 0, 0, 0 };
  Vec3 windowTopLeft = { -4, 3, -2 };
  Vec3 windowTopRight = { 4, 3, -2 };
  Vec3 windowBottomLeft = { -4, -3, -2 };

  Vec3 windowRight = vec3_sub(windowTopRight, windowTopLeft);
  Vec3 windowDown = vec3_sub(windowBottomLeft, windowTopLeft);

  for (int r = 0; r < img.height; r++) {
    for (int c = 0; c < img.width; c++) {
      Vec3 right = vec3_scale(windowRight, (double)(c + 0.5) / img.width);
      Vec3 down = vec3_scale(windowDown, (double)(r + 0.5) / img.height);
      Vec3 windowPoint = vec3_add(vec3_add(windowTopLeft, right), down);
      Ray ray = { .origin = camera, .dir = vec3_sub(windowPoint, camera) };
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

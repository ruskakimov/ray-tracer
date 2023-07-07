#include "ray.h"
#include "vec3.h"

Vec3 ray_pointAt(Ray ray, double t) {
  return vec3_add(ray.origin, vec3_scale(ray.dir, t));
}
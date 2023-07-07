#include <math.h>
#include "math.h"

Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  return (Vec3) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vec3 vec3_scale(Vec3 v1, double scalar) {
  return (Vec3) { v1.x* scalar, v1.y* scalar, v1.z* scalar };
}

double vec3_sqLen(Vec3 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vec3 ray_pointAt(Ray ray, double t) {
  return vec3_add(ray.origin, vec3_scale(ray.dir, t));
}

double calcDiscriminant(double a, double b, double c) {
  return b * b - 4 * a * c;
}

Vec2 calcRoots(double a, double b, double discriminant) {
  double sqDis = sqrt(discriminant);
  return (Vec2) { (-b + sqDis) / (2 * a), (-b - sqDis) / (2 * a) };
}
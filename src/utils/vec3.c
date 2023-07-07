#include "vec3.h"

Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  return (Vec3) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vec3 vec3_scale(Vec3 v1, double scalar) {
  return (Vec3) { v1.x* scalar, v1.y* scalar, v1.z* scalar };
}

double vec3_sqLen(Vec3 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}
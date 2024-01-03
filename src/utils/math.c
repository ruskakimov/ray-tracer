#include <math.h>
#include <stdlib.h>
#include "math.h"

Vec3 vec_add(Vec3 v1, Vec3 v2) {
  return (Vec3) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// Returns a vector from `v2` to `v1`, if `v1` and `v2` represent points.
Vec3 vec_sub(Vec3 v1, Vec3 v2) {
  return (Vec3) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

Vec3 vec_mul(Vec3 v, double s) {
  return (Vec3) { v.x* s, v.y* s, v.z* s };
}

Vec3 vec_div(Vec3 v, double s) {
  return (Vec3) { v.x / s, v.y / s, v.z / s };
}

Vec3 vec_unit(Vec3 v) {
  return vec_div(v, vec_len(v));
}

double vec_len(Vec3 v) {
  return sqrt(vec_sqlen(v));
}

double vec_sqlen(Vec3 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

double vec_dot(Vec3 v1, Vec3 v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 ray_point(Ray ray, double t) {
  return vec_add(ray.origin, vec_mul(ray.dir, t));
}

double ray_sphere_t(Ray ray, Sphere sphere) {
  // Sphere eq:
  // (x-a)^2 + (y-b)^2 + (z-c)^2 = r^2

  // Ray eq:
  // x0, y0, z0 = ray.origin
  // dx, dy, dz = ray.dir
  // x = x0 + dx * t
  // y = y0 + dy * t
  // z = z0 + dz * t

  // Plug x, y, z into sphere eq:
  // (x0 + dx*t - a)^2 + (y0 + dy*t - b)^2 + (z0 + dz*t - c)^2 = r^2

  // x0^2 + 2*x0*dx*t - x0*a + dx^2*t^2 - 2*a*dx*t - a*x0 + a^2 +
  // y0^2 + 2*y0*dy*t - y0*b + dy^2*t^2 - 2*b*dy*t - b*y0 + b^2 +
  // z0^2 + 2*z0*dz*t - z0*c + dz^2*t^2 - 2*c*dz*t - c*z0 + c^2 = r^2

  // A = dx^2 + dy^2 + dz^2
  // B = 2*x0*dx + 2*y0*dy + 2*z0*dz - 2*a*dx - 2*b*dy - 2*c*dz
  // C = x0^2 + y0^2 + z0^2 - x0*a - y0*b - z0*c - a*x0 - b*y0 - c*z0 + a^2 + b^2 + c^2 - r^2

  Vec3 oc = vec_sub(ray.origin, sphere.center);
  double a = vec_dot(ray.dir, ray.dir);
  double bHalf = vec_dot(ray.origin, ray.dir) - vec_dot(sphere.center, ray.dir);
  double c = vec_dot(oc, oc) - (sphere.radius * sphere.radius);

  double discr = bHalf * bHalf - a * c;

  if (discr < 0) return -1.0;

  double sqDiscr = sqrt(discr);
  double root1 = (-bHalf - sqDiscr) / a;
  if (root1 > 0) return root1;

  double root2 = (-bHalf + sqDiscr) / a;
  if (root2 > 0) return root2;

  return -1.0; // Sphere is behind the camera.
}

// Returns a random double from [0.0, 1.0) range.
double rnd() {
  return rand() / (RAND_MAX + 1.0);
}

double rnd_between(double min, double max) {
  return min + rnd() * (max - min);
}

Vec3 rnd_vec() {
  return (Vec3) { rnd(), rnd(), rnd() };
}

Vec3 rnd_vec_between(double min, double max) {
  return (Vec3) { rnd_between(min, max), rnd_between(min, max), rnd_between(min, max) };
}

Vec3 rnd_in_unit_sphere() {
  while (1) {
    Vec3 vec = rnd_vec_between(-1, 1);
    if (vec_len(vec) < 1) return vec;
  }
}

Vec3 rnd_unit_vec() {
  return vec_unit(rnd_in_unit_sphere());
}

Vec3 rnd_on_hemisphere(Vec3 normal) {
  Vec3 u = rnd_unit_vec();
  if (vec_dot(u, normal) > 0) {
    // Positive dot product, angle is less than 90deg.
    return u;
  }
  else {
    return vec_mul(u, -1);
  }
}
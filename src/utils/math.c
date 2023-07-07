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

Vec3 ray_pointAt(Ray ray, double time) {
  return vec3_add(ray.origin, vec3_scale(ray.dir, time));
}

double ray_sphereHitTime(Ray ray, Sphere sphere) {
  // Sphere eq:
  // (x-a)^2 + (y-b)^2 + (z-c)^2 = r^2

  // Ray eq:
  // x0, y0, z0 = ray.origin
  // dx, dy, dz = ray.dir
  // x = x0 + dx * t
  // y = y0 + dy * t
  // z = z0 + dz * t

  // Plug x and y into sphere eq:
  // (x0 + dx*t - a)^2 + (y0 + dy*t - b)^2 + (z0 + dz*t - c)^2 = r^2

  // x0^2 + 2*x0*dx*t - x0*a + dx^2*t^2 - 2*a*dx*t - a*x0 + a^2 +
  // y0^2 + 2*y0*dy*t - y0*b + dy^2*t^2 - 2*a*dy*t - b*y0 + b^2 +
  // z0^2 + 2*z0*dz*t - z0*c + dz^2*t^2 - 2*a*dz*t - c*z0 + c^2 = r^2

  // A = dx^2 + dy^2 + dz^2
  // B = 2*x0*dx + 2*y0*dy + 2*z0*dz - 2*a*dx - 2*a*dy - 2*a*dz
  // C = x0^2 + y0^2 + z0^2 - x0*a - y0*b - z0*c - a*x0 - b*y0 - c*z0 + a^2 + b^2 + c^2 - r^2

  double a = sphere.center.x;
  double b = sphere.center.y;
  double c = sphere.center.z;
  double r = sphere.radius;

  double x0 = ray.origin.x;
  double y0 = ray.origin.y;
  double z0 = ray.origin.z;
  double dx = ray.dir.x;
  double dy = ray.dir.y;
  double dz = ray.dir.z;

  double A = (dx * dx) + (dy * dy) + (dz * dz);
  double B = (2 * x0 * dx) + (2 * y0 * dy) + (2 * z0 * dz) - (2 * a * dx) - (2 * a * dy) - (2 * a * dz);
  double C = (x0 * x0) + (y0 * y0) + (z0 * z0) - (x0 * a) - (y0 * b) - (z0 * c) - (a * x0 - b * y0 - c * z0) + (a * a) + (b * b) + (c * c) - (r * r);

  double discr = calcDiscriminant(A, B, C);

  if (discr < 0) return -1.0;
  Vec2 roots = calcRoots(A, B, discr);

  if (roots.x < 0) return roots.y; // Smaller root is behind ray origin.
  return roots.x;
}

double calcDiscriminant(double a, double b, double c) {
  return b * b - 4 * a * c;
}

// Calculates two roots to a quadratic equation. Roots are sorted.
Vec2 calcRoots(double a, double b, double discriminant) {
  double sqDis = sqrt(discriminant);
  return (Vec2) { (-b - sqDis) / (2 * a), (-b + sqDis) / (2 * a) };
}
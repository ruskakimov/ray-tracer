#pragma once

typedef struct {
  double x;
  double y;
  double z;
} Vec3;

typedef struct {
  Vec3 origin;
  Vec3 dir;
} Ray;

typedef struct {
  Vec3 center;
  double radius;
} Sphere;

Vec3 vec_add(Vec3 v1, Vec3 v2);
Vec3 vec_sub(Vec3 v1, Vec3 v2);
Vec3 vec_mul(Vec3 v, double s);
Vec3 vec_div(Vec3 v, double s);
Vec3 vec_unit(Vec3 v);
double vec_len(Vec3 v);
double vec_sqlen(Vec3 v);
double vec_dot(Vec3 v1, Vec3 v2);

Vec3 ray_point(Ray ray, double t);
double ray_sphere_t(Ray ray, Sphere sphere);

double discr(double a, double b, double c);

double rnd();
double rnd_between(double min, double max);
Vec3 rnd_vec();
Vec3 rnd_vec_between(double min, double max);
Vec3 rnd_in_unit_sphere();
Vec3 rnd_unit_vec();
Vec3 rnd_on_hemisphere(Vec3 normal);
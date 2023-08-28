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

Vec3 add_vec(Vec3 v1, Vec3 v2);
Vec3 sub_vec(Vec3 v1, Vec3 v2);
Vec3 mul_vec(Vec3 v, double s);
Vec3 div_vec(Vec3 v, double s);
Vec3 unit_vec(Vec3 v);
double vec_len(Vec3 v);
double vec_sqlen(Vec3 v);
double vec_dot(Vec3 v1, Vec3 v2);

Vec3 ray_point(Ray ray, double t);
double ray_sphere_t(Ray ray, Sphere sphere);

double discr(double a, double b, double c);

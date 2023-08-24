#pragma once

typedef struct {
  double x;
  double y;
} Vec2;

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

Vec3 add_vect(Vec3 v1, Vec3 v2);
Vec3 sub_vect(Vec3 v1, Vec3 v2);
Vec3 mul_vect(Vec3 v, double s);
Vec3 div_vect(Vec3 v, double s);
double vect_len(Vec3 v);
double vect_sqlen(Vec3 v);

Vec3 ray_point(Ray ray, double t);
double ray_sphere_t(Ray ray, Sphere sphere);

double discr(double a, double b, double c);
Vec2 sqroots(double a, double b, double discr);

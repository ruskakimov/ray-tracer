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

Vec3 vec3_add(Vec3 v1, Vec3 v2);
Vec3 vec3_scale(Vec3 v1, double scalar);
double vec3_sqLen(Vec3 v);

typedef struct {
  Vec3 origin;
  Vec3 dir;
} Ray;

Vec3 ray_pointAt(Ray ray, double t);

double calcDiscriminant(double a, double b, double c);
Vec2 calcRoots(double a, double b, double discriminant);
#pragma once

#include "Vec3.h"

typedef struct {
  double x;
  double y;
} Vec2;

typedef struct {
  Vec3 origin;
  Vec3 dir;
} Ray;

typedef struct {
  Vec3 center;
  double radius;
} Sphere;

Vec3 ray_pointAt(Ray ray, double time);
double ray_sphereHitTime(Ray ray, Sphere sphere);

double calcDiscriminant(double a, double b, double c);
Vec2 calcRoots(double a, double b, double discriminant);
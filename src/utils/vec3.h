#pragma once

typedef struct {
  double x;
  double y;
  double z;
} Vec3;

Vec3 vec3_add(Vec3 v1, Vec3 v2);
Vec3 vec3_scale(Vec3 v1, double scalar);
double vec3_sqLen(Vec3 v);
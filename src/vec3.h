#pragma once

typedef struct {
  double x;
  double y;
  double z;
} Vec3;

Vec3 vecAdd(Vec3* v1, Vec3* v2);
Vec3 vecScale(Vec3* v1, double scalar);
double vecSqLen(Vec3* v);
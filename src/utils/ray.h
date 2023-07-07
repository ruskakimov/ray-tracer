#pragma once
#include "vec.h"

typedef struct {
  Vec3 origin;
  Vec3 dir;
} Ray;

Vec3 ray_pointAt(Ray ray, double t);
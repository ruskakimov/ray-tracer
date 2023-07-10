#include "Vec3.h"

#include <cmath>

Vec3::Vec3(double x, double y, double z) : m_x{ x }, m_y{ y }, m_z{ z } {}

double Vec3::sqLen() const {
  return m_x * m_x + m_y * m_y + m_z * m_z;
}

double Vec3::len() const {
  return sqrt(sqLen());
}

Vec3& Vec3::operator+=(const Vec3& v) {
  m_x += v.m_x;
  m_y += v.m_y;
  m_z += v.m_z;
  return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
  *this += -v;
  return *this;
}

Vec3& Vec3::operator*=(const double t) {
  m_x *= t;
  m_y *= t;
  m_z *= t;
  return *this;
}

Vec3& Vec3::operator/=(const double t) {
  *this *= 1.0 / t;
  return *this;
}

Vec3 operator-(Vec3 a) {
  a *= -1;
  return a;
}

Vec3 operator+(Vec3 a, const Vec3& b) {
  a += b;
  return a;
}

Vec3 operator-(Vec3 a, const Vec3& b) {
  a -= b;
  return a;
}

Vec3 operator*(Vec3 a, const double t) {
  a *= t;
  return a;
}
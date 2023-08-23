#pragma once

class Vec3 {
private:
  double m_x, m_y, m_z;
public:
  Vec3(double x, double y, double z);

  double x() const { return m_x; };
  double y() const { return m_y; };
  double z() const { return m_z; };

  double sqLen() const;
  double len() const;

  Vec3& operator+=(const Vec3& v);
  Vec3& operator-=(const Vec3& v);
  Vec3& operator*=(const double t);
  Vec3& operator/=(const double t);
};

Vec3 operator-(Vec3 a);
Vec3 operator+(Vec3 a, const Vec3& b);
Vec3 operator-(Vec3 a, const Vec3& b);
Vec3 operator*(Vec3 a, const double t);
#ifndef VEC3
#define VEC3
#include <cmath>
class Vec3
{
public:
    double x, y, z;
    Vec3();
    Vec3(double xx, double yy, double zz);
    double length2();
    Vec3& normalize();
    Vec3 operator * (double &f);
    double dot(Vec3 &v);
    Vec3 operator - (Vec3 &v);
    Vec3& operator += (Vec3 &v);
};
#endif

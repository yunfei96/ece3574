#include "vector3d.h"

Vec3::Vec3()
{
    x = double(0.);
    y = double(0.);
    z = double(0.);
}

Vec3::Vec3(double xx, double yy, double zz)
{
    x = xx;
    y = yy;
    z = zz;
}

double Vec3::length2()
{
    return x * x + y * y + z * z;
}


Vec3 & Vec3::normalize()
{
    double nor2 = length2();
    if (nor2 > 0)
    {
        double invNor = 1 / sqrt(nor2);
        x *= invNor, y *= invNor, z *= invNor;
    }
    return *this;
}

Vec3 Vec3::operator * (double &f)
{
    return Vec3(x * f, y * f, z * f);
}


double Vec3::dot(Vec3 &v)
{
    return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::operator - (Vec3 &v)
{
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3& Vec3::operator += (Vec3 &v)
{
    x += v.x, y += v.y, z += v.z;
    return *this;
}






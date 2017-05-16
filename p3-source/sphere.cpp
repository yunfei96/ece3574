#include "sphere.h"
Sphere::Sphere( Vec3 &c,Vec3 &sc,double &r,double &lb)
{
    center = c;
    radius = r;
    radius2 = r * r;
    surfaceColor = sc;
    lambert = lb;
}
bool Sphere::intersect(Vec3 &rayorig, Vec3 &raydir, double &t0, double &t1)
{
    Vec3 l = center - rayorig;
    double tca = l.dot(raydir);
    if (tca < 0)
    {
        return false;
    }
    double d2 = l.dot(l) - tca * tca;
    if (d2 > radius2)
    {
        return false;
    }
    double thc = sqrt(radius2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;
    return true;
}

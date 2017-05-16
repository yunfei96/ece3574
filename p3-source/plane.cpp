#include "plane.h"
Plane::Plane(Vec3 &c,Vec3 &sc, Vec3 &nl, double &lb)
{
    center = c;
    surfaceColor = sc;
    normal = nl;
    lambert = lb;
}
bool Plane::intersectPlane( Vec3 &n,  Vec3 &p0,  Vec3 &l0,  Vec3 &l, double &t)
{
    // assuming vectors are all normalized
    double denom = n.dot(l);
    Vec3 p0l0 = p0 - l0;
    t = ((p0l0.dot(n)) / denom)-0.000000000001;
    return (t >= 0);
}

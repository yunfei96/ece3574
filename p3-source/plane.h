#ifndef PLANE
#define PLANE
#include "vector3d.h"

class Plane
{
public:
    Vec3 center;
    Vec3 normal;
    double lambert;
    Vec3 surfaceColor;
    Plane(Vec3 &c,Vec3 &sc, Vec3 &nl, double &lb);
    
    bool intersectPlane( Vec3 &n,  Vec3 &p0,  Vec3 &l0,  Vec3 &l, double &t);
};
#endif  

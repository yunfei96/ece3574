#ifndef SPHERE
#define SPHERE
#include "vector3d.h"

class Sphere
{
public:
    Vec3 center;
    double radius, radius2, lambert;
    Vec3 surfaceColor;
    Sphere(Vec3 &c,Vec3 &sc,double &r, double &lb);
    
    bool intersect(Vec3 &rayorig, Vec3 &raydir, double &t0, double &t1);
    
};
#endif 

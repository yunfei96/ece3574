#ifndef CAL
#define CAL
#include <QPixmap>
#include "parsejson.h"
#include <vector>
#include "sphere.h"
#include "plane.h"
#include <QString>
#include <QDataStream>
#include <thread>
#include <mutex> 
#include <iostream>
using namespace std;

void func(vector<double> &camera_center, double &camera_focus,vector<double> &camera_normal,vector<double> &camera_resolution, vector<double> &camera_size, vector<light_struct> &lights_vector, vector<objects_struct> &objects_vector, int width, int height, vector<Sphere> &spheres, vector<Plane> &planes, double &max_x, double &max_y, double &max_z, vector<vector<Vec3>> &Array, int s_w, int s_h);

void tracing(vector<double> camera_center, double camera_focus,vector<double> camera_normal,vector<double> camera_resolution, vector<double> camera_size, vector<light_struct> lights_vector, vector<objects_struct> objects_vector, string name, int thread_number);
#endif

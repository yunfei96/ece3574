#include "calculate.h"
void func(vector<double> &camera_center, double &camera_focus,vector<double> &camera_normal,vector<double> &camera_resolution, vector<double> &camera_size, vector<light_struct> &lights_vector, vector<objects_struct> &objects_vector, int width, int height, vector<Sphere> &spheres, vector<Plane> &planes, double &max_x, double &max_y, double &max_z, vector<vector<Vec3>> &Array, int s_w, int s_h)
{
    for(int w = s_w; w < width; w++)
    {
        for(int h = s_h; h< height; h++)
        {
            //rayorig raydir, calculate coordinate
            Vec3 rayorig(camera_normal[0]*(-camera_focus),camera_normal[1]*(-camera_focus), camera_normal[2]*(-camera_focus));
            Vec3 raydir;
            if(abs(camera_normal[0]) != 0)
            {
                double x = (w - (camera_size[0])/2)* camera_resolution[0];
                double y = (h - (camera_size[1])/2)* camera_resolution[1];
                raydir = (Vec3(0,y,x) - rayorig).normalize();
            }
            if(abs(camera_normal[1]) != 0)
            {
                double x = (w - (camera_size[0])/2)* camera_resolution[0];
                double y = (h - (camera_size[1])/2)* camera_resolution[1];
                raydir = (Vec3(x,0,y) - rayorig).normalize();
            }
            if(abs(camera_normal[2]) != 0)
            {
                double x = (w - (camera_size[0])/2)* camera_resolution[0];
                double y = (h - (camera_size[1])/2)* camera_resolution[1];
                raydir = (Vec3(x,y,0) - rayorig).normalize();
            }
            
            //for each sphere in the scene
            Sphere * sphere = nullptr;
            double t0 = INFINITY, t1 = INFINITY, tnear = INFINITY;
            for(int i =0; i <spheres.size(); i++)
            {
                if (spheres[i].intersect(rayorig, raydir, t0, t1))
                {
                    if (t0 < 0)
                        t0 = t1;
                    if (t0 < tnear)
                    {
                        tnear = t0;
                        sphere = &spheres[i];
                    }
                }
            }
            //for each plane in the scene
            Plane * plane = nullptr;
            double t = INFINITY,tplane_near = INFINITY;
            for(int i =0; i < planes.size(); i++)
            {
                if(planes[i].intersectPlane(planes[i].normal, planes[i].center,rayorig,raydir,t))
                {
                    if(t < tplane_near)
                    {
                        tplane_near = t;
                        plane = &planes[i];
                    }
                }
            }
            Vec3 Phit;
            Vec3 Nhit;
            if(tplane_near < tnear && plane != nullptr) //intersect with plane
            {
                Phit = raydir * tplane_near;
                Phit += rayorig;
                Nhit = plane->normal;
                sphere = nullptr;
            }
            else if(tnear < tplane_near && sphere != nullptr)
            {
                Phit = raydir * tnear;
                Phit += rayorig;
                Nhit = (Phit - sphere->center).normalize();
                plane = nullptr;
            }
            //-------------------------shadow ray--------------
            if( plane != nullptr || sphere != nullptr)
            {
                
                //find shadow ray
                Vec3 sumpixelcolor;
                
                for(int i = 0; i < lights_vector.size();i++)
                {
                    Vec3 light(lights_vector[i].location[0], lights_vector[i].location[1],lights_vector[i].location[2]);
                    Vec3 shadowraydir = (light-Phit).normalize();
                    //Vec3 shadowray = (light - Phit).normalize();
                    bool block = false;
                    //for each light source, loop each sphere
                    double t0,t1 = 0;
                    for(int j =0; j < spheres.size();j++)
                    {
                        if(spheres[j].intersect(Phit, shadowraydir, t0, t1))
                        {
                            Vec3 Phit_t0 = shadowraydir * t0;
                            Phit_t0 += Phit;
                            Vec3 Phit_t1 = shadowraydir * t1;
                            Phit_t1 += Phit;
                            if(t0 >= 0 || t1 >= 0)
                            {
                                block = true;
                            }
                        }
                    }
                    //for each light source, loop each plane
                    double t = 0;
                    for(int j =0; j < planes.size();j++)
                    {
                        
                        if(planes[j].intersectPlane(planes[j].normal, planes[j].center, Phit, shadowraydir,t))
                        {
                            Vec3 Phit_t = shadowraydir * t;
                            Phit_t += Phit;
                            if(camera_normal[0] < 0)
                            {
                                if(Phit_t.x < 0)
                                {
                                    block = true;
                                }
                            }
                            else if(camera_normal[0] > 0)
                            {
                                if(Phit_t.x > 0)
                                {
                                    block = true;
                                }
                            }
                            else if(camera_normal[1] < 0)
                            {
                                if(Phit_t.y < 0)
                                {
                                    block = true;
                                }
                            }
                            else if(camera_normal[1] > 0)
                            {
                                if(Phit_t.y > 0)
                                {
                                    block = true;
                                }
                            }
                            else if(camera_normal[2] < 0)
                            {
                                if(Phit_t.z < 0)
                                {
                                    block = true;
                                }
                            }
                            else if(camera_normal[2] > 0)
                            {
                                if(Phit_t.z > 0)
                                {
                                    block = true;
                                }
                            }
                            
                        }
                    }
                    //calculate the color
                    Vec3 pixel_color;
                    if(!block)
                    {
                        //scale = dot_product(surface_normal, shadow_ray)*surface_lambert
                        if(sphere != nullptr)
                        {
                            double scale = Nhit.dot(shadowraydir)*sphere->lambert;
                            double temp = (scale*lights_vector[i].intensity);
                            pixel_color = sphere->surfaceColor * temp;
                        }
                        else
                        {
                            double scale = Nhit.dot(shadowraydir)*plane->lambert;
                            double temp = (scale*lights_vector[i].intensity);
                            pixel_color = plane->surfaceColor * temp;
                            if(pixel_color.x < 0)
                            {
                                pixel_color.x = 0;
                            }
                            if(pixel_color.y < 0)
                            {
                                pixel_color.y = 0;
                            }
                            if(pixel_color.z < 0)
                            {
                                pixel_color.z = 0;
                            }
                        }
                        //pixel_color = scale*light_intensity*surface_color;
                        
                    }
                    sumpixelcolor += pixel_color;
                }
                if(sumpixelcolor.x > max_x)//b
                {
                    max_x = sumpixelcolor.x;
                }
                if(sumpixelcolor.y > max_y)//g
                {
                    max_y = sumpixelcolor.y;
                }
                if(sumpixelcolor.z > max_z)//r
                {
                    max_z = sumpixelcolor.z;
                }
                
                Array[w][h] = sumpixelcolor;
            }
            else
            {
                Vec3 zero;
                Array[w][h] = zero;
            }
        }
    }
}

void tracing(vector<double> camera_center, double camera_focus,vector<double> camera_normal,vector<double> camera_resolution, vector<double> camera_size, vector<light_struct> lights_vector, vector<objects_struct> objects_vector, string name, int thread_number)
{
    int width = camera_size[0];
    int height = camera_size[1];
    if(thread_number >= width)
    {
        throw logic_error("too many thread");
    }
    vector<vector<Vec3> >Array(width, std::vector<Vec3>(height));
    QImage img(width, height, QImage::Format_RGB888);
    vector<Sphere> spheres;
    vector<Plane> planes;
    for(int i =0; i < objects_vector.size(); i++)
    {
        if(objects_vector[i].type == "sphere")
        {
            Vec3 c(objects_vector[i].center[0], objects_vector[i].center[1], objects_vector[i].center[2]);
            Vec3 sc(objects_vector[i].color[0], objects_vector[i].color[1],objects_vector[i].color[2]);
            Sphere mysphere(c,sc,objects_vector[i].radius,objects_vector[i].lambert);
            spheres.push_back(mysphere);
        }
        else
        {
            Vec3 c(objects_vector[i].center[0], objects_vector[i].center[1], objects_vector[i].center[2]);
            Vec3 sc(objects_vector[i].color[0], objects_vector[i].color[1],objects_vector[i].color[2]);
            Vec3 nm(objects_vector[i].normal[0], objects_vector[i].normal[1],objects_vector[i].normal[2]);
            Plane myplane(c,sc,nm,objects_vector[i].lambert);
            planes.push_back(myplane);
        }
    }
    //--------------------------
    double max_x = 0;
    double max_y = 0;
    double max_z = 0;
    int zero = 0;
    thread* threads[thread_number];
    int step = width/thread_number;
    int last_step = width%thread_number;
    for(int i =0; i < thread_number; i++)
    {
        int this_wd = i*step;
        int next_wd = (i+1)*step;
        if(i == (thread_number-1))
        {
            next_wd = next_wd + last_step;
        }
        thread * temp = new thread(func,ref(camera_center), ref(camera_focus),ref(camera_normal),ref(camera_resolution), ref(camera_size), ref(lights_vector), ref(objects_vector), next_wd, height, ref(spheres),ref(planes), ref(max_x), ref(max_y), ref(max_z),ref(Array),this_wd,zero);
        threads[i] = temp;
    }
    //
    for (int i = 0; i < thread_number; i++)
    {
        while(threads[i]->joinable())
        {
            threads[i]->join();
            
        }
    }
    //
    for (int i = 0; i < thread_number; i++)
    {
        delete threads[i];
    }
    //
    for(int w =0; w < width; w++)
    {
        for(int h =0; h < height; h++)
        {
            QRgb value = qRgb((1/max_z)*Array[w][h].z*255, (1/max_y)*Array[w][h].y*255, (1/max_x)*Array[w][h].x*255);
            img.setPixel(w, h, value);
        }
    }
    QString qstr = name.c_str();
    bool suc = img.save(qstr);
    if(!suc)
    {
        throw logic_error("cannot save image");
    }
}

// implement vtray main here
#include <iostream>
#include "calculate.h"
#include <fstream>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <string>
using namespace std;

int main(int argc, char*argv[])
{
    objects camera;
    QString file_name;
    QString image_name;
    int tnumber = 1;
    if(argc == 3)
    {
        file_name = argv[1];
        image_name = argv[2];
    }
    else if(argc == 5)
    {
        if(argv[1] == string("-t"))
        {
            tnumber = atoi(argv[2]);
            if(tnumber <= 0)
            {
                return EXIT_FAILURE;
            }
            file_name = argv[3];
            image_name = argv[2];}
        else
        {
            cerr << "argument number not right" << endl;
        }
    }
    else
    {
        cerr << "argument number not right" << endl;
        return EXIT_FAILURE;
    }
    QFile file(file_name);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        cerr << "json parsing error" <<endl;
        return EXIT_FAILURE;
    }
    //make a stream of the file
    QTextStream in(&file);
    QString js;
    js = in.readAll();
    file.close();
    try
    {
        camera.fromJSON(js);
    }
    catch (QJsonParseError)
    {
        cerr << "json parsing error" <<endl;
        return EXIT_FAILURE;
    }
    try
    {
        tracing(camera.camera_center, camera.camera_focus,camera.camera_normal,camera.camera_resolution, camera.camera_size, camera.lights_vector, camera.objects_vector, image_name.toStdString(), tnumber);
    } catch (logic_error)
    {
        cerr << "ray tacing error" <<endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

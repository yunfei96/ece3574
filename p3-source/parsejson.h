#ifndef PARSEJSON
#define PARSEJSON
#include <QString>
#include <QList>
#include <QJsonObject>
#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <vector>
#include <string>
using namespace std;

struct light_struct
{
    double intensity;
    vector<double> location;
};

struct objects_struct
{
    vector<double> center;
    vector<double> color;
    double lambert;
    double radius;
    vector<double> normal;
    string type;
};

class objects
{
public:
    void fromJSON(QString json);
    vector<double> camera_center;
    double camera_focus;
    vector<double> camera_normal;
    vector<double> camera_resolution;
    vector<double> camera_size;
    vector<light_struct> lights_vector;
    vector<objects_struct> objects_vector;
private:
    bool isint(string str);
    bool isnumber(string str);
    void parsing_camera();
    void parsing_light();
    void parsing_objects();
    void check_positive(double a, double b);
    void check_size(int a, int b);
    void check_positive_with0(double a);
    QJsonObject camera;
    QJsonArray lights;
    QJsonArray objects;
};

#endif

#include "parsejson.h"

void objects::fromJSON(QString json)
{
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        throw error;
    }
    QJsonObject obj = jsonDoc.object();
    camera = obj["camera"].toObject();
    lights = obj["lights"].toArray();
    objects = obj["objects"].toArray();
    parsing_camera();
    parsing_light();
    parsing_objects();
}
void objects::parsing_objects()
{
    //----------------------parse objects--------------------
    for(QJsonValue it : objects)
    {
        QJsonObject objects = it.toObject();
        objects_struct o;
        //center
        QJsonObject center = objects["center"].toObject();
        check_size(center.size(), 3);
        o.center.push_back(center["x"].toDouble());
        o.center.push_back(center["y"].toDouble());
        o.center.push_back(center["z"].toDouble());
        //color
        QJsonObject color = objects["color"].toObject();
        check_size(color.size(), 3);
        if(color["b"].toDouble() != color["b"].toInt() || color["g"].toDouble() != color["g"].toInt()||color["r"].toDouble() != color["r"].toInt())
        {
            throw QJsonParseError();
        }
        if( color["b"].toDouble() < 0 || color["b"].toDouble() > 255 || color["g"].toDouble() < 0 || color["g"].toDouble() > 255 || color["r"].toDouble() < 0 || color["r"].toDouble() > 255)
        {
            throw QJsonParseError();
        }
        o.color.push_back(color["b"].toDouble());
        o.color.push_back(color["g"].toDouble());
        o.color.push_back(color["r"].toDouble());
        //lambert
        if(objects["lambert"].toDouble() != objects["lambert"].toInt())
        {
            throw QJsonParseError();
        }
        if(objects["lambert"].toDouble() < 0 || objects["lambert"].toDouble() > 1)
        {
            throw QJsonParseError();
        }
        o.lambert = objects["lambert"].toDouble();
        o.type = objects["type"].toString().toStdString();
        if(o.type == "sphere")
        {
            check_positive_with0(objects["radius"].toDouble());
            o.radius = objects["radius"].toDouble();
        }
        else
        {
            QJsonObject normal = objects["normal"].toObject();
            check_size(normal.size(), 3);
            o.normal.push_back(normal["x"].toDouble());
            o.normal.push_back(normal["y"].toDouble());
            o.normal.push_back(normal["z"].toDouble());
        }
        objects_vector.push_back(o);
    }

}
void objects::parsing_light()
{
    //----------------------parse lights---------------------
    for (QJsonValue it : lights)
    {
        QJsonObject light_object = it.toObject();
        light_struct l;
        //------------------intensity-----------------
        check_positive_with0(light_object["intensity"].toDouble());
        //
        l.intensity = light_object["intensity"].toDouble();
        //-------------------location
        QJsonObject location = light_object["location"].toObject();
        //check
        check_size(location.size(), 3);
        //
        l.location.push_back(location["x"].toDouble());
        l.location.push_back(location["y"].toDouble());
        l.location.push_back(location["z"].toDouble());
        lights_vector.push_back(l);
    }
}

void objects::parsing_camera()
{
    //-----------------------parse camera------------------
    QJsonObject center = camera["center"].toObject();
    //parse center
    QJsonValue centerx = center["x"];
    QJsonValue centery = center["y"];
    QJsonValue centerz = center["z"];
    //check
    check_size(center.size(), 3);
    //
    camera_center.push_back(centerx.toDouble());
    camera_center.push_back(centery.toDouble());
    camera_center.push_back(centerz.toDouble());
    //---------------------------parse focus------------
    QJsonValue focus = camera["focus"];
    camera_focus = focus.toDouble();
    //---------------------------parse normal------------
    QJsonObject normal = camera["normal"].toObject();
    QJsonValue normalx = normal["x"];
    QJsonValue normaly = normal["y"];
    QJsonValue normalz = normal["z"];
    //check
    check_size(normal.size(), 3);
    //
    camera_normal.push_back(normalx.toDouble());
    camera_normal.push_back(normaly.toDouble());
    camera_normal.push_back(normalz.toDouble());
    //----------------------------parse resolution--------
    QJsonArray resolution = camera["resolution"].toArray();
    //check
    check_size(resolution.size(), 2);
    check_positive(resolution[0].toDouble(), resolution[1].toDouble());
    //
    camera_resolution.push_back(resolution[0].toDouble());
    camera_resolution.push_back(resolution[1].toDouble());
    //----------------------------parse size---------------
    QJsonArray size = camera["size"].toArray();
    //check
    check_size(size.size(), 2);
    string x = size[0].toString().toStdString();
    if(size[0].toDouble() != size[0].toInt() || size[1].toDouble() != size[1].toInt())
    {
        throw QJsonParseError();
    }
    check_positive(size[0].toDouble(), size[1].toDouble());
    //
    camera_size.push_back(size[0].toDouble());
    camera_size.push_back(size[1].toDouble());
}
void objects::check_size(int a, int b)
{
    if(a != b)
    {
        throw QJsonParseError();
    }
}
void objects::check_positive_with0(double a)
{
    if(a < 0)
    {
        throw QJsonParseError();
    }
}
void objects::check_positive(double a, double b)
{
    if(a <= 0 || b <= 0)
    {
        throw QJsonParseError();
    }
}

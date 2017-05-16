#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <iostream>
#include "calculate.h"
#include "test_config.hpp"
#include <fstream>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <string>

TEST_CASE( "Parsing JSON", "[JSON]" )
{
    objects camera;
    QString DIR = (TEST_FILE_DIR + "/scene0.json").c_str() ;
    QFile file(DIR);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&file);
    QString js;
    js = in.readAll();
    file.close();
    camera.fromJSON(js);
    REQUIRE(camera.camera_focus == 10.);
    REQUIRE(camera.objects_vector[0].radius == 1.);
}

TEST_CASE( "fail JSON-prof", "[JSON]" )
{
    {//wrong input
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene3.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        REQUIRE_THROWS_AS(camera.fromJSON(js), QJsonParseError);
    }
    {//wrong json
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene4.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        REQUIRE_THROWS_AS(camera.fromJSON(js), QJsonParseError);
    }
    {//empty
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene5.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        REQUIRE_THROWS_AS(camera.fromJSON(js), QJsonParseError);
    }
 
}

TEST_CASE( "fail JSON-mine", "[JSON]" )
{
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene6.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        REQUIRE_THROWS_AS(camera.fromJSON(js), QJsonParseError);
    }
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene7.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        REQUIRE_THROWS_AS(camera.fromJSON(js), QJsonParseError);
    }
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene8.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        REQUIRE_THROWS_AS(camera.fromJSON(js), QJsonParseError);
    }
}

TEST_CASE( "1 thread", "[tracing]" )
{
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene1.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        camera.fromJSON(js);
        tracing(camera.camera_center, camera.camera_focus,camera.camera_normal,camera.camera_resolution, camera.camera_size, camera.lights_vector, camera.objects_vector, TEST_FILE_DIR+"/mytest2.png",1);
    }
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene2-s.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        camera.fromJSON(js);
        tracing(camera.camera_center, camera.camera_focus,camera.camera_normal,camera.camera_resolution, camera.camera_size, camera.lights_vector, camera.objects_vector, TEST_FILE_DIR+"/mytest3.png",1);
    }
}
TEST_CASE( "many thread", "[threading]" )
{
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene0.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        camera.fromJSON(js);
        tracing(camera.camera_center, camera.camera_focus,camera.camera_normal,camera.camera_resolution, camera.camera_size, camera.lights_vector, camera.objects_vector, TEST_FILE_DIR+"/mytest0.png",255);
    }
}
TEST_CASE( "too much thread", "[threading]" )
{
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene0.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        camera.fromJSON(js);
        REQUIRE_THROWS_AS(tracing(camera.camera_center, camera.camera_focus,camera.camera_normal,camera.camera_resolution, camera.camera_size, camera.lights_vector, camera.objects_vector, TEST_FILE_DIR+"/mytest0.png",1000), logic_error);
    }
    
}

TEST_CASE( "camera rotation", "[tracing]" )
{
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene0-r.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        camera.fromJSON(js);
        tracing(camera.camera_center, camera.camera_focus,camera.camera_normal,camera.camera_resolution, camera.camera_size, camera.lights_vector, camera.objects_vector, TEST_FILE_DIR+"/mytest0-r.png",1);
    }
    {
        objects camera;
        QString DIR = (TEST_FILE_DIR + "/scene1-r.json").c_str() ;
        QFile file(DIR);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&file);
        QString js;
        js = in.readAll();
        file.close();
        camera.fromJSON(js);
        tracing(camera.camera_center, camera.camera_focus,camera.camera_normal,camera.camera_resolution, camera.camera_size, camera.lights_vector, camera.objects_vector, TEST_FILE_DIR+"/mytest1-r.png",1);
    }
}

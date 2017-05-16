#include "qt_interpreter.hpp"
#include <QString>
#include <QDebug>
QtInterpreter ::QtInterpreter(QObject * parent)
{
    
}
void QtInterpreter::parseAndEvaluate(QString entry)
{
    //output the entry
    string input_string;
    input_string = entry.toStdString();
    istringstream iss(input_string);
    readfile(iss);
}
void QtInterpreter::readfile(std::istream & expression)
{
    bool ok = interp.parse(expression);
    bool flag = calndis(ok);
    if(!flag)
    {
        emit error(result);
        result.clear();
    }
    else
    {
        emit info(result);
        result.clear();
    }
    draw();
}
bool QtInterpreter::calndis(bool ok)
{
    if(ok)
    {
        Expression myresult;
        try
        {
            myresult = interp.eval();
        }
        catch (InterpreterSemanticError e)
        {
            QString temp1 = QString::fromStdString("Error: ");
            QString temp2 = QString::fromStdString(e.what());
            result.push_back(temp1);
            result.push_back(temp2);
            Interpreter new_interp;
            interp = new_interp;
            return false;
        }
        if(myresult.type == "number")
        {
            QString temp1 = QString::fromStdString("(");
            std::stringstream buffer;
            buffer << myresult.number_value;
            QString temp2 = QString::fromStdString(buffer.str());
            QString temp3 = QString::fromStdString(")");
            result.push_back(temp1);
            result.push_back(temp2);
            result.push_back(temp3);
        }
        else if(myresult.type == "bool")
        {
            if(myresult.bool_value == true)
                result = QString::fromStdString("(True)");
            else
                result = QString::fromStdString("(False)");
        }
        else if(myresult.type == "point")
        {
            std::stringstream buffer;
            buffer << "(" << get<0>(myresult.start)<< "," <<  get<1>(myresult.start)<< ")";
            result = QString::fromStdString(buffer.str());
        }
        else if(myresult.type == "line")
        {
            std::stringstream buffer;
            buffer << "((" << get<0>(myresult.start)<< "," <<  get<1>(myresult.start)<< ")" << "(" << get<0>(myresult.end)<< "," <<  get<1>(myresult.end) << "))";
            result = QString::fromStdString(buffer.str());
        }
        else if(myresult.type == "arc")
        {
            std::stringstream buffer;
            buffer << "((" << get<0>(myresult.center)<< "," <<  get<1>(myresult.center)<< ")" << "(" << get<0>(myresult.start)<< "," <<  get<1>(myresult.start) << ")"<< myresult.angle << ")";
            result = QString::fromStdString(buffer.str());
        }
        return true;
    }
    result = QString::fromStdString("Error: parsing failed");
    Interpreter new_interp;
    interp = new_interp;
    return false;
}
void QtInterpreter::draw()
{
    for(int i=0; i<interp.drawlist.size();i++)
    {
        if(interp.drawlist[i].type == "line")
        {
            int x;
            int y;
            int z;
            int k;
            x = get<0>(interp.drawlist[i].start);
            y = get<1>(interp.drawlist[i].start);
            z = get<0>(interp.drawlist[i].end);
            k = get<1>(interp.drawlist[i].end);
            QGraphicsLineItem *line = new QGraphicsLineItem(QLineF(x,y,z,k));
    
            emit drawGraphic(line);
        }
        else if(interp.drawlist[i].type == "point")
        {
            int x;
            int y;
            x = get<0>(interp.drawlist[i].start);
            y = get<1>(interp.drawlist[i].start);
            
            QGraphicsEllipseItem *point = new QGraphicsEllipseItem(x,y,2,2);
            point->setBrush(QBrush(Qt::black, Qt::SolidPattern));
            emit drawGraphic(point);
        }
        else
        {
            int x;
            int y;
            int z;
            int k;
            double angle;
            x = get<0>(interp.drawlist[i].center);
            y = get<1>(interp.drawlist[i].center);
            z = get<0>(interp.drawlist[i].start);
            k = get<1>(interp.drawlist[i].start);
            angle = interp.drawlist[i].angle;
            QGraphicsArcItem *arc = new QGraphicsArcItem(x,y,z,k,angle);
            emit drawGraphic(arc);
        }
        
    }
    interp.drawlist.clear();
}



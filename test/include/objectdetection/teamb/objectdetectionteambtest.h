#ifndef OBJECTDETECTIONTEAMBTEST_H
#define OBJECTDETECTIONTEAMBTEST_H

#include "objectdetection/teamb/objectdetectionalgorithmteamb.h"
#include "line.h"
#include "objectdetection/object.h"
#include "objectdetection/databaseutils.h"
#include "objectdetection/model.h"

#include <QtTest/QtTest>
#include <QObject>
#include <QDir>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <iostream>

using namespace formseher;

class ObjectDetectionTeamBTest : public QObject
{
    Q_OBJECT

    private slots:

    void initTestCase()
    {
        dbFileName = "formseherdatabase";
        dbFilePath = QDir::temp().absoluteFilePath(dbFileName);
    }

    void testCalculate(){

        // create database entry first
        // this one shall be a quader
        DatabaseUtils dbu(dbFilePath.toStdString());
        dbu.read();

        Object obj;
        obj.setName("Quader");
        obj.addLine(Line(0,0,0,10));
        obj.addLine(Line(0,0,10,0));
        obj.addLine(Line(10,0,10,10));
        obj.addLine(Line(10,10,0,10));
        dbu.addObject(obj);

        dbu.write();

        std::vector<Model> models = dbu.read();

        // simulate lines from edl
        std::vector<Line> linesFromEDL;

        linesFromEDL.push_back(Line(1,1,1,9));
        linesFromEDL.push_back(Line(1,1,9,1));
        linesFromEDL.push_back(Line(9,1,9,9));
        linesFromEDL.push_back(Line(9,9,1,9));

        // now test the calculate
//        ObjectDetectionAlgorithmTeamB objDATb;

//        objDATb.setModels(models);
//        std::vector<Object> receivedObjects = objDATb.calculate(linesFromEDL);

//        std::cout << receivedObjects.size() << std::endl;
//        for(int i = 0; i < receivedObjects.size(); i++){
//            // @bartosch
//            // hier siehst wie alle linien das selbe rating bekommen und daher 4⁴ moeglichkeiten entstehen weil keins aussortiert wird
//            std::cout << receivedObjects[i].getName() << "|" << receivedObjects[i].getRating() << "|" << receivedObjects[i].getLines().size()<<std::endl;
//        }

//        QVERIFY(receivedObjects[0].getName().compare("Quader") == 0);
    }

    void cleanupTestCase()
    {
        QDir::temp().remove(dbFileName);
    }

private:
    QString dbFileName;
    QString dbFilePath;

};



#endif // OBJECTDETECTIONTEAMBTEST_H

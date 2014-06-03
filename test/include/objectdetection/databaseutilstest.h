#ifndef DATABASEUTILSTEST_H
#define DATABASEUTILSTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "objectdetection/databaseutils.h"
#include "objectdetection/model.h"
#include "objectdetection/object.h"
#include "line.h"
#include "iostream"

using namespace formseher;

class DatabaseUtilsTest : public QObject
{

    Q_OBJECT

private slots:

    void readTest(){

        DatabaseUtils dbu("/home/michl/utilTest/db.txt");
        std::vector<Model> models = dbu.read();

        QVERIFY(models[0].getName() == "name");
        QVERIFY(models.size() == 2);
    }

    void addObjectTest(){

        DatabaseUtils dbu("/home/michl/utilTest/db.txt");
        std::vector<Model> models = dbu.read();

        uint currSize = models.size();
        Object obj;
        obj.setName("testObj");
        obj.addLine(Line(4,5,6,7));
        dbu.addObject(obj);

        dbu.write();

        models = dbu.read();

        QVERIFY(models.size() > currSize);
    }

    void removeObjectTest(){

        DatabaseUtils dbu("/home/michl/utilTest/db.txt");
        std::vector<Model> models = dbu.read();

        uint currSize = models.size();

        Object obj;
        obj.setName("objToRemove");

        dbu.removeObject(obj);

        dbu.write();
        models = dbu.read();

        QVERIFY(models.size() < currSize);
    }
};

#endif // DATABASEUTILSTEST_H

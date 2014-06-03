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

        DatabaseUtils dbu("db.txt");
        std::vector<Model> models = dbu.read();

        QVERIFY(models.empty());
    }

    void addObjectTest(){

        DatabaseUtils dbu("db.txt");
        std::vector<Model> models = dbu.read();

        uint currSize = models.size();

        Object obj;
        obj.setName("objToRemove");
        obj.addLine(Line(4,5,6,7));
        dbu.addObject(obj);

        dbu.write();

        models = dbu.read();

        QVERIFY(models.size() > currSize);
    }

    void removeObjectTest(){

        DatabaseUtils dbu("db.txt");
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

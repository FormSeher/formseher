#ifndef DATABASEUTILSTEST_H
#define DATABASEUTILSTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QDir>
#include <QString>
#include <string>

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
    void initTestCase()
    {
        dbFileName = "formseherdatabase";
        dbFilePath = QDir::temp().absoluteFilePath(dbFileName);
    }

    void readTest(){

        DatabaseUtils dbu(dbFilePath.toStdString());
        std::vector<Model> models = dbu.read();

        QVERIFY(models.empty());
    }

    void addObjectTest(){

        DatabaseUtils dbu(dbFilePath.toStdString());
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

        DatabaseUtils dbu(dbFilePath.toStdString());
        std::vector<Model> models = dbu.read();

        uint currSize = models.size();

        Object obj;
        obj.setName("objToRemove");

        dbu.removeObject(obj);

        dbu.write();
        models = dbu.read();

        QVERIFY(models.size() < currSize);
    }

    void cleanupTestCase()
    {
        QDir::temp().remove(dbFileName);
    }

private:
    QString dbFileName;
    QString dbFilePath;
};

#endif // DATABASEUTILSTEST_H

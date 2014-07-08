#ifndef FS_HAFFDATABASETEST_H
#define FS_HAFFDATABASETEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "objectdetection/haff/haffdatabase.h"

using namespace formseher;

class HaffDatabaseTest : public QObject
{
Q_OBJECT

private slots:

/*****
 * Disabled because of error message if test is not executed
 * from formseher root directory, because resource file is not found.
 *****/
//    void loadTest()
//    {
//        HaffDatabase database("./res/test/hafftestdatabase");
//        QVERIFY(database.load());
//        QVERIFY(2 == database.getObjects().size());

//        QVERIFY("Object 1" == database.getObjects().at(0)->getName());
//        QVERIFY("Object 2" == database.getObjects().at(1)->getName());

//        QVERIFY(cv::Point2i(40, 12) == database.getObjects().at(0)->getLines().at(0)->getEnd());
//        QVERIFY(cv::Point2i(77, 94) == database.getObjects().at(1)->getLines().at(0)->getEnd());
//    }
};

#endif // FS_HAFFDATABASETEST_H

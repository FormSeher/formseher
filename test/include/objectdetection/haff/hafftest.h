#ifndef FS_HAFFTEST_H
#define FS_HAFFTEST_H

#include <QtTest>
#include <QObject>

#include "objectdetection/haff/haff.h"
#include "line.h"
#include "objectdetection/object.h"

using namespace formseher;

class HaffTest : public QObject
{
Q_OBJECT

private slots:
    void calcualateTest()
    {
        Haff haff;

        std::vector<Line> detectedLines;
        detectedLines.push_back(Line(0, 0, 1, 0));
        detectedLines.push_back(Line(1, 0, 1, 1));
        detectedLines.push_back(Line(1, 1, 0, 1));
        detectedLines.push_back(Line(0, 1, 0, 0));

        std::vector<Model> databaseModels;

        Model model;
        model.setName("model");
        model.addLine(Line(0, 0, 1, 0));
        model.addLine(Line(1, 0, 1, 1));
        model.addLine(Line(1, 1, 0, 1));
        model.addLine(Line(0, 1, 0, 0));

        databaseModels.push_back(model);

        haff.setModels(databaseModels);

        std::vector<Object> objects = haff.calculate(detectedLines);

        QCOMPARE(objects.size(), (size_t)1);
    }

};

#endif // FS_HAFFTEST_H

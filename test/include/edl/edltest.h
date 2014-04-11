#ifndef EDLTEST_H
#define EDLTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "edl/edl.h"

class EDLTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        edl = new EDL();
    }

    void cleanupTestCase()
    {
        delete edl;
    }

private:
    EDL* edl;
};

#endif // EDLTEST_H

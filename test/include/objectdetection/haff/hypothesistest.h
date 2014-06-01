#ifndef FS_HYPOTHESISTEST_H
#define FS_HYPOTHESISTEST_H

#include <QtTest/QtTest>
#include <QObject>

// brute force private to public (don't do this at home kids!)
#undef private
#define private public

#include "objectdetection/haff/hypothesis.h"

// Restore visibilities
#undef private
#define private private

using namespace formseher;

class HypothesisTest : public QObject
{
Q_OBJECT

private slots:

};

#endif // FS_HYPOTHESISTEST_H

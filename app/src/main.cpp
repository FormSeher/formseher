/*
* This file is part of FormSeher.
*
* FormSeher is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* FormSeher is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2014 FormSeher
*/

#include <gui/mainwindow.h>
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "gui/linedetection/edl/edlconfigdialog.h"
#include "gui/linedetection/edl2/edl2configdialog.h"
#include "gui/linedetection/hough/houghconfigdialog.h"

#include "gui/objectdetection/stub/stubconfigdialog.h"
#include "gui/objectdetection/haff/haffconfigdialog.h"

#include "gui/objectdetection/teamb/objectdetectionalgorithmteambdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    formseher::EDLConfigDialog edlDialog1;
    formseher::EDLConfigDialog edlDialog2;

    formseher::EDL2ConfigDialog edl2Dialog1;
    formseher::EDL2ConfigDialog edl2Dialog2;

    formseher::HoughConfigDialog houghDialog1;
    formseher::HoughConfigDialog houghDialog2;

    formseher::StubConfigDialog stubDialog1;
    formseher::StubConfigDialog stubDialog2;

    formseher::ObjectDetectionAlgorithmTeamBDialog objDetTeambDialog1;
    formseher::ObjectDetectionAlgorithmTeamBDialog objDetTeambDialog2;

    formseher::HaffConfigDialog haffDialog1;
    formseher::HaffConfigDialog haffDialog2;

    formseher::MainWindow w;

    w.registerLineAlgorithmConfigDialog(1, "EDL2", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&edl2Dialog1));
    w.registerLineAlgorithmConfigDialog(2, "EDL2", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&edl2Dialog2));
    w.registerLineAlgorithmConfigDialog(1, "EDL", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&edlDialog1));
    w.registerLineAlgorithmConfigDialog(2, "EDL", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&edlDialog2));
    w.registerLineAlgorithmConfigDialog(1, "Hough", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&houghDialog1));
    w.registerLineAlgorithmConfigDialog(2, "Hough", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&houghDialog2));

    w.registerObjectAlgorithmConfigDialog(1, "Stub", static_cast<formseher::ObjectDetectionAlgorithmConfigDialog*>(&stubDialog1));
    w.registerObjectAlgorithmConfigDialog(2, "Stub", static_cast<formseher::ObjectDetectionAlgorithmConfigDialog*>(&stubDialog2));
    w.registerObjectAlgorithmConfigDialog(1, "Haff", static_cast<formseher::ObjectDetectionAlgorithmConfigDialog*>(&haffDialog1));
    w.registerObjectAlgorithmConfigDialog(2, "Haff", static_cast<formseher::ObjectDetectionAlgorithmConfigDialog*>(&haffDialog2));
    w.registerObjectAlgorithmConfigDialog(1, "ObjDetTeamB", static_cast<formseher::ObjectDetectionAlgorithmConfigDialog*>(&objDetTeambDialog1));
    w.registerObjectAlgorithmConfigDialog(2, "ObjDetTeamB", static_cast<formseher::ObjectDetectionAlgorithmConfigDialog*>(&objDetTeambDialog2));

    w.show();

    return a.exec();
}

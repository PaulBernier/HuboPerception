/*
* Copyright (c) 2014, Georgia Tech Research Corporation
* All rights reserved.
*
* Author: Paul Bernier <bernier.pja@gmail.com>
* Date: Jan 2014
*
* Humanoid Robotics Lab Georgia Institute of Technology
* Director: Mike Stilman http://www.golems.org
*
*
* This file is provided under the following "BSD-style" License:
* Redistribution and use in source and binary forms, with or
* without modification, are permitted provided that the following
* conditions are met:
*
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following
* disclaimer in the documentation and/or other materials provided
* with the distribution.
*
* * Neither the name of the Humanoid Robotics Lab nor the names of
* its contributors may be used to endorse or promote products
* derived from this software without specific prior written
* permission
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
* USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>
#include <thread>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>

#include "URG2OSG/urgcppwrapper.h"
#include "URG2OSG/circle.h"

#include <pcl/io/pcd_io.h>

#include "URG2OSG/dxl.h"
#include <osg/Point>
#include "URG2OSG/scanner3d.h"
#include <boost/timer/timer.hpp>

using namespace std;

void setUpOSGNodes(osg::ref_ptr<osg::Group> root, URGCPPWrapper &urg);
void URG_subroutine(URGCPPWrapper* urg, osg::ref_ptr<osg::Group>  root);

int main()
{
    URGCPPWrapper urg("192.168.0.10", 10940);

    cout << urg.getAllInfo() << endl;

    osgViewer::Viewer viewer;

    osg::ref_ptr<osg::Group> root = new osg::Group;
    setUpOSGNodes(root, urg);

    // Thread getting data from the laser
    thread urg_thread(URG_subroutine, &urg, root);

    // Set viewer
    viewer.setSceneData(root);
    viewer.setUpViewInWindow(50, 50, 800, 600);
    viewer.run();

    urg_thread.join();

    return 0;
}

void setUpOSGNodes(osg::ref_ptr<osg::Group> root, URGCPPWrapper& urg)
{
    osg::ref_ptr<osg::Geode> landmarkGeode = new osg::Geode;

    root->addChild(landmarkGeode);

    // Sphere at origin
    osg::ref_ptr<osg::Sphere> unitSphere = new osg::Sphere(osg::Vec3(0,0,0), 10.0f);
    osg::ref_ptr<osg::ShapeDrawable> unitSphereDrawable = new osg::ShapeDrawable(unitSphere);
    landmarkGeode->addDrawable(unitSphereDrawable);

    // x-axis
    osg::ref_ptr<osg::Box> stick = new osg::Box(osg::Vec3(500,0,0), 1000.0f, 10.0f, 10.0f);
    osg::ref_ptr<osg::ShapeDrawable> stickDrawable = new osg::ShapeDrawable(stick);
    stickDrawable->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    landmarkGeode->addDrawable(stickDrawable);

    // y-axis
    osg::ref_ptr<osg::Box> stick2 = new osg::Box(osg::Vec3(0,500,0), 10.0f, 1000.0f, 10.0f);
    osg::ref_ptr<osg::ShapeDrawable> stickDrawable2 = new osg::ShapeDrawable(stick2);
    stickDrawable2->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    landmarkGeode->addDrawable(stickDrawable2);

    // z-axis
    osg::ref_ptr<osg::Box> stick3 = new osg::Box(osg::Vec3(0,0,500), 10.0f, 10.0f, 1000.0f);
    osg::ref_ptr<osg::ShapeDrawable> stickDrawable3 = new osg::ShapeDrawable(stick3);
    stickDrawable3->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    landmarkGeode->addDrawable(stickDrawable3);

    // Min distance circle
    osg::ref_ptr<Circle> minDistanceCircle = new Circle(urg.getMinDistance());
    landmarkGeode->addDrawable(minDistanceCircle);

    // Max distance circle
//    osg::ref_ptr<Circle> maxDistanceCircle = new Circle(urg.getMaxDistance());
//    landmarkGeode->addDrawable(maxDistanceCircle);
}

void URG_subroutine(URGCPPWrapper* urg, osg::ref_ptr<osg::Group> root)
{

    const int start_angle_degree = 220;
    const int end_angle_degree = 110;
    const double scan_step_degree = 0.5;

    Dxl dxl;

    try
    {
        Scanner3d scanner(urg, &dxl, start_angle_degree, end_angle_degree, scan_step_degree);
        scanner.scan();

        // Save point cloud
        scanner.savePointCloudToPCD("hubo.pcd");

        // Display point cloud
        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        scanner.getScan3dGeode(geode);
        root->addChild(geode);
    }
    catch(const std::runtime_error& e)
    {
        cout << e.what() << endl;
    }

}


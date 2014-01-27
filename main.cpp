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
#include "URG2OSG/urgtoosg.h"
#include "URG2OSG/laserscanlinenode.h"

using namespace std;

void URG_subroutine(URGCPPWrapper* urg, osgViewer::Viewer* viewer);

int main()
{
    URGCPPWrapper urg("192.168.0.10", 10940);

    osgViewer::Viewer viewer;

    osg::ref_ptr<osg::Group> root = new osg::Group;
    osg::ref_ptr<LaserScanLineNode> laser_scan_line_node = new LaserScanLineNode(urg);
    osg::ref_ptr<osg::Geode> originGeode = new osg::Geode;

    root->addChild(originGeode);
    root->addChild(laser_scan_line_node);

    // Cube at origin
    osg::ref_ptr<osg::Box> unitCube = new osg::Box(osg::Vec3(0,0,0), 150.0f);
    osg::ref_ptr<osg::ShapeDrawable> unitCubeDrawable = new osg::ShapeDrawable(unitCube);
    originGeode->addDrawable(unitCubeDrawable);

    // Thread getting data from the laser
    thread urg_thread(URG_subroutine, &urg, &viewer);

    // Set viewer
    viewer.setSceneData(root);
    viewer.setUpViewInWindow(50, 50, 800, 600);
    viewer.run();

    urg_thread.join();

    return 0;
}

void URG_subroutine(URGCPPWrapper* urg, osgViewer::Viewer* viewer)
{
    try
    {
        urg->sync();

        cout << urg->getAllInfo();

        urg->start();

        while(!viewer->done())
        {
            urg->grabScan();
        }

        urg->stop();

    }catch(const std::runtime_error& e){
        cout << e.what() << endl;
    }
}


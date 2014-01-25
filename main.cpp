#include <iostream>
#include <thread>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>

#include "urgcppwrapper.h"
#include "urgtoosg.h"
#include "laserscanlinenode.h"

using namespace std;

void URG_routine(URGCPPWrapper* urg);

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
    osg::ref_ptr<osg::Box> unitCube = new osg::Box( osg::Vec3(0,0,0), 150.0f);
    osg::ref_ptr<osg::ShapeDrawable> unitCubeDrawable = new osg::ShapeDrawable(unitCube);
    originGeode->addDrawable(unitCubeDrawable);

    thread urg_thread(URG_routine, &urg);

    viewer.setSceneData(root);
    viewer.setUpViewInWindow(50, 50, 800, 600);
    viewer.run();

    urg_thread.join();

    return 0;
}

void URG_routine(URGCPPWrapper* urg)
{
    try
    {
        urg->sync();

        cout << urg->getAllInfo();

        urg->start();

        while(1)
        {
            urg->grabScanWithIntensity();
        }

        urg->stop();

    }catch(const std::runtime_error& e){
        cout << e.what() << endl;
    }
}


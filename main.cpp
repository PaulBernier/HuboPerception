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
            urg->grabScanWithIntensity();
        }

        urg->stop();

    }catch(const std::runtime_error& e){
        cout << e.what() << endl;
    }
}


#include <iostream>
#include <thread>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>

#include "urgcppwrapper.h"
#include "urgtoosg.h"
#include "laserscanline.h"

using namespace std;

void URG_routine(osg::ref_ptr<osg::Geode> geode, osg::ref_ptr<osg::Geometry> geometry);

int main()
{

    osgViewer::Viewer viewer;

    osg::ref_ptr<osg::Group> root = new osg::Group;
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::Geode> originGeode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;

    geode->addDrawable(geometry);
    root->addChild(originGeode);
    root->addChild(geode);

    // Cube at origin
    osg::ref_ptr<osg::Box> unitCube = new osg::Box( osg::Vec3(0,0,0), 150.0f);
    osg::ref_ptr<osg::ShapeDrawable> unitCubeDrawable = new osg::ShapeDrawable(unitCube);
    originGeode->addDrawable(unitCubeDrawable);

    thread urg_thread(URG_routine, geode, geometry);

    viewer.setSceneData(root);
    viewer.setUpViewInWindow(50, 50, 800, 600);
    viewer.run();

    urg_thread.join();

    return 0;
}

void URG_routine(osg::ref_ptr<osg::Geode> geode, osg::ref_ptr<osg::Geometry> geometry)
{
    try
    {
        URGCPPWrapper urg("192.168.0.10", 10940);
        urg.sync();

        cout << urg.getAllInfo();

        urg.start();

        while(1)
        {
            urg.grabScanWithIntensity();
            geode->removeDrawable(geometry);
            UrgToOsg::to2DGeometry(urg, geometry);
            geode->addDrawable(geometry);
            std::this_thread::sleep_for(chrono::milliseconds(100));
        }

        urg.stop();
    }catch(const std::runtime_error& e){
        cout << e.what() << endl;
    }
}


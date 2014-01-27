#ifndef LASERSCANLINENODE_H
#define LASERSCANLINENODE_H

#include <osg/Geode>
#include "laserscanline.h"
#include "laserscanlinecallback.h"

class LaserScanLineNode : public osg::Geode
{
public:
    LaserScanLineNode(URGCPPWrapper &urg);
    void update();

protected:
    osg::ref_ptr<LaserScanLine> laser_scan_line;
};

#endif // LASERSCANLINENODE_H

#ifndef LASERSCANLINENODE_H
#define LASERSCANLINENODE_H

#include <osg/Node>
#include "laserscanline.h"
#include "laserscanlinecallback.h"

class LaserScanLineNode : public osg::Node
{
public:
    LaserScanLineNode(URGCPPWrapper &urg);
    void update();

protected:
    LaserScanLine laser_scan_line;
};

#endif // LASERSCANLINENODE_H

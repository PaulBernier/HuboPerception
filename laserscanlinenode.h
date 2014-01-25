#ifndef LASERSCANLINENODE_H
#define LASERSCANLINENODE_H

#include <osg/Node>
#include "laserscanline.h"

class LaserScanLineNode : public osg::Node
{
public:
    LaserScanLineNode();
    void update();

protected:
    LaserScanLine laser_scan_line;
};

#endif // LASERSCANLINENODE_H

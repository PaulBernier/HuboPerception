#ifndef LASERSCANLINE_H
#define LASERSCANLINE_H

#include <osg/Geometry>
#include "urgcppwrapper.h"

class LaserScanLine : public osg::Geometry
{
public:
    LaserScanLine(URGCPPWrapper &urg);
    void updateVertices();

protected:
    URGCPPWrapper& urg;

    osg::ref_ptr<osg::Vec3Array> vertices;
    osg::ref_ptr<osg::Vec4Array> color;
};

#endif // LASERSCANLINE_H

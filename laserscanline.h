#ifndef LASERSCANLINE_H
#define LASERSCANLINE_H

#include <osg/Geometry>

class LaserScanLine : public osg::Geometry
{
public:
    LaserScanLine();
    void updateVertices();

protected:

    void init();

    osg::ref_ptr<osg::Vec3Array> vertices;
    osg::ref_ptr<osg::Vec4Array> color;
};

#endif // LASERSCANLINE_H

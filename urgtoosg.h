#ifndef URGTOOSG_H
#define URGTOOSG_H

#include <osg/Geometry>
#include <osg/Vec3>
#include "urgcppwrapper.h"

class UrgToOsg
{
public:

    static void getOsgPoints(const URGCPPWrapper& urg, osg::ref_ptr<osg::Vec3Array> vertices, osg::ref_ptr<osg::Vec4Array> colors);
    static osg::Vec3 polarToCartesian(const long distance, const double angle_rad);

private:
    UrgToOsg();
};

#endif // URGTOOSG_H

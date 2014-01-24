#ifndef URGTOOSG_H
#define URGTOOSG_H

#include <osg/Geometry>
#include <osg/Vec3>
#include "urgcppwrapper.h"

class UrgToOsg
{
public:

    static void to2DGeometry(const URGCPPWrapper& urg, osg::ref_ptr<osg::Geometry> geometry);
    static osg::Vec3 to2DSpace(const long distance, const double angle_rad);
private:
    UrgToOsg();
};

#endif // URGTOOSG_H

#include "URG2OSG/laserscanline.h"
#include "URG2OSG/urgtoosg.h"
#include <osg/Point>

LaserScanLine::LaserScanLine(URGCPPWrapper &urg)
    : urg(urg), vertices(new osg::Vec3Array(urg.getNumberOfPoints())), color(new osg::Vec4Array(1))
{
    setDataVariance(osg::Object::DYNAMIC);
    getOrCreateStateSet()->setAttribute(new osg::Point(3), osg::StateAttribute::ON);
    addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, urg.getNumberOfPoints()));

    setColorBinding(osg::Geometry::BIND_OVERALL);
    (*color)[0] = osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f);
    setColorArray(color);
}

void LaserScanLine::updateVertices()
{
    UrgToOsg::getOsgPoints(urg, vertices);
    setVertexArray(vertices);
}

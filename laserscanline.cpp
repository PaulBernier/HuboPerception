#include "laserscanline.h"

LaserScanLine::LaserScanLine()
{
    init();
}

void LaserScanLine::init()
{
    setDataVariance(osg::Object::DYNAMIC);
}

void LaserScanLine::updateVertices()
{
    setVertexArray(vertices);
}

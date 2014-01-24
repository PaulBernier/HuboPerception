#include "urgtoosg.h"

void UrgToOsg::to2DGeometry(const URGCPPWrapper& urg, osg::ref_ptr<osg::Geometry> geometry)
{
    const unsigned long int numberOfPoints = urg.getNumberOfPoints();
    const std::vector<long>& distance = urg.getDistance();


    osg::ref_ptr<osg::Vec3Array> vertices(new osg::Vec3Array(numberOfPoints));


    for(unsigned int i=0 ; i<numberOfPoints ; ++i)
    {
        (*vertices)[i] = to2DSpace(distance[i], urg.index2rad(i));
    }

    geometry->setVertexArray(vertices.get());


    if(urg.useIntensity())
    {
        const std::vector<unsigned short>& intensity = urg.getIntensity();
        osg::ref_ptr<osg::Vec4Array> colors(new osg::Vec4Array(numberOfPoints));

        for(unsigned int i=0 ; i<numberOfPoints ; ++i)
        {
            (*colors)[i] = osg::Vec4f(1, 0, 0, 1);
        }
        geometry->setColorArray(colors.get());
        geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    }

    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->size()));
}

osg::Vec3 UrgToOsg::to2DSpace(const long distance, const double angle_rad)
{
    return osg::Vec3(distance * cos(angle_rad), distance * sin(angle_rad), 0);
}

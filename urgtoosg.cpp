#include "urgtoosg.h"

void UrgToOsg::getOsgPoints(const URGCPPWrapper& urg, osg::ref_ptr<osg::Vec3Array> vertices, osg::ref_ptr<osg::Vec4Array> colors)
{
    const unsigned long int numberOfPoints = urg.getNumberOfPoints();
    const std::vector<long>& distance = urg.getDistance();

    vertices->resize(numberOfPoints);

    for(unsigned int i=0 ; i<numberOfPoints ; ++i)
    {
        (*vertices)[i] = polarToCartesian(distance[i], urg.index2rad(i));
    }

    if(urg.useIntensity())
    {
        const std::vector<unsigned short>& intensity = urg.getIntensity();

        for(unsigned int i=0 ; i<numberOfPoints ; ++i)
        {
            (*colors)[i] = osg::Vec4f(1, 0, 0, 1);
        }
    }
}

osg::Vec3 UrgToOsg::polarToCartesian(const long distance, const double angle_rad)
{
    return osg::Vec3(distance * cos(angle_rad), distance * sin(angle_rad), 0);
}

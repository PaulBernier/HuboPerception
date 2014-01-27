#include "URG2OSG/urgtoosg.h"

void UrgToOsg::getOsgPoints(const URGCPPWrapper& urg, osg::ref_ptr<osg::Vec3Array> vertices)
{
    const unsigned long int numberOfPoints = urg.getNumberOfPoints();
    const std::vector<long>& distance = urg.getDistance();

    vertices->resize(numberOfPoints);

    for(unsigned int i=0 ; i<numberOfPoints ; ++i)
    {
        (*vertices)[i] = polarToCartesian(distance[i], urg.index2rad(i));
    }
}

osg::Vec3 UrgToOsg::polarToCartesian(const long distance, const double angle_rad)
{
    return osg::Vec3(distance * cos(angle_rad), distance * sin(angle_rad), 0);
}

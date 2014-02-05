#include "URG2OSG/scanner3d.h"
#include "URG2OSG/urgtoosg.h"
#include <osg/Point>

Scanner3d::Scanner3d(URGCPPWrapper* urg, Dxl* dxl,
                     int start_angle_degree, int end_angle_degree, double scan_step_degree)
    : urg(urg), dxl(dxl),
      start_angle_degree(start_angle_degree), end_angle_degree(end_angle_degree), scan_step_degree(scan_step_degree)
{
    updateScanParam();
}


void Scanner3d::scan()
{
    moveHeadToInitialPosition();

    // Start measurement
    urg->start(false);

    for(unsigned int i=0 ; i<number_of_scans ; ++i)
    {
        dxl->moveToDegree(start_angle_degree - i * scan_step_degree, 3);
        // Wait
        while(dxl->isMoving(3)){}

        angles[i] = dxl->getCurrentAngleRadian(3);
        //Launch scan
        urg->grabScan();
        // Add scan result to distance vector
        // TODO use of forward list ?
        //TODO grabScan copie direct ?
        distances.insert(distances.begin() + i * number_of_points_per_scan, urg->getDistance().begin(), urg->getDistance().end());
    }

    // Stop measurement
    urg->stop();

}

void Scanner3d::getScan3dGeode(osg::ref_ptr<osg::Geode> geode)
{
    osg::ref_ptr<osg::Vec3Array> vertices(new osg::Vec3Array());
    UrgToOsg::getOsg3DPointsts(urg, vertices, distances, angles, number_of_points, number_of_points_per_scan);

    osg::ref_ptr<osg::Geometry> geometry(new osg::Geometry);
    geometry->setVertexArray(vertices);
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->size()));
    geometry->getOrCreateStateSet()->setAttribute(new osg::Point(1), osg::StateAttribute::ON);

    // Color
    osg::ref_ptr<osg::Vec4Array> color(new osg::Vec4Array(1));
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    (*color)[0] = osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f);
    geometry->setColorArray(color);

    geode->addDrawable(geometry);
}

void Scanner3d::setScanParameters(int start_angle_degree, int end_angle_degree, double scan_step_degree)
{
    this->start_angle_degree = start_angle_degree;
    this->end_angle_degree = end_angle_degree;
    this->scan_step_degree = scan_step_degree;

    updateScanParam();
}

void Scanner3d::updateScanParam()
{
    number_of_scans = abs(start_angle_degree - end_angle_degree) / scan_step_degree;
    number_of_points_per_scan = urg->getNumberOfPoints();
    number_of_points = number_of_scans * number_of_points_per_scan;

    distances.resize(number_of_points);
    angles.resize(number_of_scans);
}

void Scanner3d::moveHeadToInitialPosition()
{
    // Move to initial position
    dxl->moveToDegree(180, 1);
    dxl->moveToDegree(180, 2);
    dxl->moveToDegree(start_angle_degree, 3);

    // Wait end of move
    while(dxl->isMoving(1)){}
    while(dxl->isMoving(2)){}
    while(dxl->isMoving(3)){}
}

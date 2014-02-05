#ifndef SCANNER3D_H
#define SCANNER3D_H

#include "URG2OSG/dxl.h"
#include "URG2OSG/urgcppwrapper.h"
#include <osg/Geode>
#include <vector>

class Scanner3d
{
public:
    Scanner3d(URGCPPWrapper *urg, Dxl *dxl,
              int start_angle_degree = 220, int end_angle_degree = 110, double scan_step_degree = 1);
    void scan();
    void getScan3dGeode(osg::ref_ptr<osg::Geode> geode);

    void setScanParameters(int start_angle_degree, int end_angle_degree, double scan_step_degree);

private:
    URGCPPWrapper* urg;
    Dxl* dxl;

    std::vector<long> distances;
    std::vector<double> angles;

    // Params
    int start_angle_degree;
    int end_angle_degree;
    double scan_step_degree;

    unsigned int number_of_scans;
    unsigned long number_of_points_per_scan;
    unsigned int number_of_points;

    void updateScanParam();
    void moveHeadToInitialPosition();
};

#endif // SCANNER3D_H

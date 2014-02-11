#ifndef SCANNER3D_H
#define SCANNER3D_H

#include "URG2OSG/dxl.h"
#include "URG2OSG/urgcppwrapper.h"
#include <osg/Geode>
#include <vector>
#include "URG2OSG/scanresultstruct.h"

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

    RawScan3dResult raw_scan3d_result;

    // Params
    int start_angle_degree;
    int end_angle_degree;
    double scan_step_degree;

    void updateScanParam();
    void moveHeadToInitialPosition();
};

#endif // SCANNER3D_H

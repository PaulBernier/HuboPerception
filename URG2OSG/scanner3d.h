#ifndef SCANNER3D_H
#define SCANNER3D_H

#include "URG2OSG/dxl.h"
#include "URG2OSG/urgcppwrapper.h"

class Scanner3d
{
public:
    Scanner3d(URGCPPWrapper &urg, Dxl &dxl);

private:
    URGCPPWrapper& urg;
    Dxl& dxl;
};

#endif // SCANNER3D_H

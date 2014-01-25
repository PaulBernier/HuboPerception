#include "URG2OSG/laserscanlinenode.h"

LaserScanLineNode::LaserScanLineNode(URGCPPWrapper &urg) : laser_scan_line(urg)
{
    setUpdateCallback(new LaserScanLineCallback);
}

void LaserScanLineNode::update()
{
    laser_scan_line.updateVertices();
}

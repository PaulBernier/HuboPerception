#include "URG2OSG/laserscanlinenode.h"

LaserScanLineNode::LaserScanLineNode(URGCPPWrapper &urg) : laser_scan_line(new LaserScanLine(urg))
{
    setUpdateCallback(new LaserScanLineCallback);
    addDrawable(laser_scan_line);
}

void LaserScanLineNode::update()
{
    laser_scan_line->updateVertices();
}

#include "laserscanlinenode.h"

LaserScanLineNode::LaserScanLineNode()
{
}

void LaserScanLineNode::update()
{
    laser_scan_line.updateVertices();
}

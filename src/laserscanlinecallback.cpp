#include "URG2OSG/laserscanlinecallback.h"
#include "URG2OSG/laserscanlinenode.h"

void LaserScanLineCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    osg::ref_ptr<LaserScanLineNode> currentNode = dynamic_cast<LaserScanLineNode*>(node);

    if(currentNode)
        currentNode->update();

    traverse(node, nv);
}

#include "laserscanlinecallback.h"
#include "laserscanlinenode.h"

void LaserScanLineCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    osg::ref_ptr<LaserScanLineNode> currentNode = dynamic_cast<LaserScanLineNode*>(node);

    if(currentNode)
        currentNode->update();

    traverse(node, nv);
}

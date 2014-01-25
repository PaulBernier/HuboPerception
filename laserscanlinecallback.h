#ifndef LASERSCANLINECALLBACK_H
#define LASERSCANLINECALLBACK_H

#include <osg/NodeCallback>
#include <osg/Node>
#include <osg/NodeVisitor>

class LaserScanLineCallback : public osg::NodeCallback
{
public:
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
};

#endif // LASERSCANLINECALLBACK_H

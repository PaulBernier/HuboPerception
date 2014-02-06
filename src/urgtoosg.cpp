/*
* Copyright (c) 2014, Georgia Tech Research Corporation
* All rights reserved.
*
* Author: Paul Bernier <bernier.pja@gmail.com>
* Date: Jan 2014
*
* Humanoid Robotics Lab Georgia Institute of Technology
* Director: Mike Stilman http://www.golems.org
*
*
* This file is provided under the following "BSD-style" License:
* Redistribution and use in source and binary forms, with or
* without modification, are permitted provided that the following
* conditions are met:
*
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following
* disclaimer in the documentation and/or other materials provided
* with the distribution.
*
* * Neither the name of the Humanoid Robotics Lab nor the names of
* its contributors may be used to endorse or promote products
* derived from this software without specific prior written
* permission
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
* USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#include "URG2OSG/urgtoosg.h"

void UrgToOsg::getOsg2DPoints(URGCPPWrapper* urg, osg::ref_ptr<osg::Vec3Array> vertices)
{
    const unsigned long int number_of_points = urg->getNumberOfPoints();
    const long max_distance = urg->getMaxDistance() - EPSILON;
    const std::vector<long>& distance = urg->getDistance();

    vertices->reserve(number_of_points);

    for(unsigned int i=0 ; i<number_of_points ; ++i)
    {
        // Remove extreme points
        if(distance[i] < max_distance)
            vertices->push_back(polarToCartesian(distance[i], urg->index2rad(i)));
    }
}

osg::Vec3 UrgToOsg::polarToCartesian(const long distance, const double angle_rad)
{
    return osg::Vec3(distance * cos(angle_rad), distance * sin(angle_rad), 0);
}

void UrgToOsg::getOsg3DPointsts(URGCPPWrapper* urg, osg::ref_ptr<osg::Vec3Array> vertices,
                      const std::vector<long>& distances, const std::vector<double>& angles,
                      unsigned int number_of_points,
                      unsigned long number_of_points_per_scan)
{
    const long max_distance = urg->getMaxDistance() - EPSILON;
    vertices->reserve(number_of_points);

    for(unsigned int i=0 ; i< number_of_points ; ++i)
    {
        // Remove extreme points
        if(distances[i] < max_distance)
        {
            const double phi = angles[i / number_of_points_per_scan];
            const double theta = urg->index2rad(i % number_of_points_per_scan) - 3.1415926 / 2;

            vertices->push_back(sphericalToCartesian(distances[i], theta, phi));
        }
    }
}

osg::Vec3 UrgToOsg::sphericalToCartesian(const long distance, const double theta, const double phi)
{
    return osg::Vec3(distance * cos(phi) * sin(theta),
                     distance * cos(theta),
                     distance * sin(phi) * sin(theta));
}



#ifndef __WAYPOINT_DATA_H
#define __WAYPOINT_DATA_H

#include "ObjectGuid.h"

struct WaypointData : Position
{
    WaypointData(float x_, float y_, float z_, float o_, uint32 point_, uint32 splineFlags_, uint32 splineCount_, bool isSpline_, time_t timestamp_) :
        Position(x_, y_, z_, o_), point(point_), splineFlags(splineFlags_), splineCount(splineCount_), isSpline(isSpline_), timestamp(timestamp_) {}
    uint32 point = 0;
    uint32 splineFlags = 0;
    uint32 splineCount = 0;
    bool isSpline = false;
    time_t timestamp = 0;
};

#endif
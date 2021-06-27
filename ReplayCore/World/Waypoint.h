#ifndef __WAYPOINT_H
#define __WAYPOINT_H

#include "Unit.h"
#include "WaypointData.h"

class Waypoint : public Unit
{
public:
    Waypoint(CreatureData const& unitData, WaypointData const& waypointData) : Unit(unitData), m_waypointData(waypointData)
    {
        m_isVisible = true;
    }
    WaypointData const& GetWaypointData() const { return m_waypointData; }
private:
    WaypointData const m_waypointData;
};

#endif
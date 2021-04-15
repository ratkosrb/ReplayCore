#ifndef __OBJECT_DEFINES_H
#define __OBJECT_DEFINES_H

#include "../Common.h"
struct Position
{
    Position() = default;
    Position(float position_x, float position_y, float position_z, float orientation) : x(position_x), y(position_y), z(position_z), o(orientation) {}
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float o = 0.0f;
    bool operator!=(Position const& other) const
    {
        return !(x == other.x && y == other.y && z == other.z && o == other.o);
    }
};

#endif
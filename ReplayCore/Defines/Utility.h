#ifndef _UTILITY_DEFS_H
#define _UTILITY_DEFS_H

#include "Common.h"
#include <string>

struct IpAddress
{
    union
    {
        uint8 separate[4];
        uint32 together;
    } data;

    std::string GetString() const
    {
        return std::to_string(uint32(data.separate[0])) + "." + std::to_string(uint32(data.separate[1])) + "." + std::to_string(uint32(data.separate[2])) + "." + std::to_string(uint32(data.separate[3]));
    }
};

template <typename T>
void ReverseArray(T arr[], size_t size)
{
    for (size_t i = 0; i < size / 2; ++i)
    {
        T temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

inline uint32 secsToTimeBitFields(time_t secs)
{
    tm* lt = localtime(&secs);
    return (lt->tm_year - 100) << 24 | lt->tm_mon << 20 | (lt->tm_mday - 1) << 14 | lt->tm_wday << 11 | lt->tm_hour << 6 | lt->tm_min;
}


#endif


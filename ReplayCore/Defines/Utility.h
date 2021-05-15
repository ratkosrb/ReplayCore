#ifndef _UTILITY_DEFS_H
#define _UTILITY_DEFS_H

#include "Common.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <time.h>

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

inline std::tm localtime_r(const time_t& time)
{
    std::tm tm_snapshot;
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
    localtime_s(&tm_snapshot, &time);
#else
    localtime_r(&time, &tm_snapshot); // POSIX
#endif
    return tm_snapshot;
}

inline std::string TimeToTimestampStr(time_t t)
{
    tm aTm = localtime_r(t);
    //       YYYY   year
    //       MM     month (2 digits 01-12)
    //       DD     day (2 digits 01-31)
    //       HH     hour (2 digits 00-23)
    //       MM     minutes (2 digits 00-59)
    //       SS     seconds (2 digits 00-59)
    char buf[20];
    snprintf(buf, 20, "%04d-%02d-%02d_%02d-%02d-%02d", aTm.tm_year + 1900, aTm.tm_mon + 1, aTm.tm_mday, aTm.tm_hour, aTm.tm_min, aTm.tm_sec);
    return std::string(buf);
}

inline uint32 secsToTimeBitFields(time_t secs)
{
    tm* lt = localtime(&secs);
    return (lt->tm_year - 100) << 24 | lt->tm_mon << 20 | (lt->tm_mday - 1) << 14 | lt->tm_wday << 11 | lt->tm_hour << 6 | lt->tm_min;
}

inline void ParseStringIntoVector(std::string const& text, std::vector<uint32> data)
{
    std::string tmp;
    std::stringstream ss(text);

    while (std::getline(ss, tmp, ' '))
    {
        uint32 value = static_cast<uint32>(atol(tmp.c_str()));
        data.push_back(value);
    }
}

inline std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

inline void StringToLower(std::string& text)
{
    std::for_each(text.begin(), text.end(), [](char & c) {
        c = ::tolower(c);
    });
}

#endif


#ifndef _SHARED_DEFS_H
#define _SHARED_DEFS_H

#include <cassert>
#include <cstdint>
#include <stdio.h>
#ifdef __linux__
#include <cstring>
#include <cfloat>
#include <memory>
#include <cmath>
#endif

#define ASSERT(a) assert(a)

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

enum TimeConstants
{
    MINUTE = 60,
    HOUR   = MINUTE*60,
    DAY    = HOUR*24,
    WEEK   = DAY*7,
    MONTH  = DAY*30,
    YEAR   = MONTH*12,
    IN_MILLISECONDS = 1000
};

#endif
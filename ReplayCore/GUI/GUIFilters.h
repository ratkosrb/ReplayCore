#ifndef _GUI_FILTERS_H
#define _GUI_FILTERS_H

#include "../Defines/Common.h"
#include <set>

enum GUIObjectTypeFilters
{
    FILTER_ANY = 0,
    FILTER_GAMEOBJECT = 1,
    FILTER_TRANSPORT = 2,
    FILTER_UNIT = 3,
    FITLER_CREATURE = 4,
    FILTER_PET = 5,
    FILTER_PLAYER = 6,
};

struct SniffedEvent;

struct ObjectFilterEntry
{
    uint32 guid = 0;
    uint32 id = 0;
    uint32 type = 0;
    std::set<uint32> eventTypes;

    bool IsEventFitForFilter(SniffedEvent const* pEvent) const;
};

#endif
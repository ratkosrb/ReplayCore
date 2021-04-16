#ifndef _UPDATE_FIELD_DEFS_H
#define _UPDATE_FIELD_DEFS_H

#include "../Defines/Common.h"
#include <map>
#include <string>

#define OBJECT_FIELD_GUID uint16(0)

namespace UpdateFields
{
    extern std::map<std::string, uint16> g_updateFieldValues5875;
    extern std::map<std::string, uint16> g_updateFieldValues8606;
    extern std::map<std::string, uint16> g_updateFieldValues12340;

    std::map<std::string, uint16>* GetUpdateFieldsMapForBuild(uint16 build);
    uint16 GetUpdateFieldValue(std::string name, uint16 build);
    std::string GetUpdateFieldName(uint16 id, uint16 build);
}

#endif
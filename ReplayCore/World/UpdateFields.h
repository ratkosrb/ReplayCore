#ifndef _UPDATE_FIELD_DEFS_H
#define _UPDATE_FIELD_DEFS_H

#include "../Defines/Common.h"
#include <map>
#include <string>

#define OBJECT_FIELD_GUID uint16(0)
#define OBJECT_FIELD_TYPE uint16(2)
#define OBJECT_FIELD_ENTRY uint16(3)
#define OBJECT_FIELD_SCALE_X uint16(4)
#define OBJECT_FIELD_PADDING uint16(5)
#define OBJECT_END uint16(6)

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
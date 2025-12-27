#ifndef _UPDATE_FIELD_DEFS_H
#define _UPDATE_FIELD_DEFS_H

#include "../Defines/Common.h"
#include <map>
#include <string>
#include <vector>

#define OBJECT_FIELD_GUID uint16(0)

enum UpdateFieldValueTypes
{
	UF_TYPE_NONE      = 0,
	UF_TYPE_INT       = 1,
	UF_TYPE_TWO_SHORT = 2,
	UF_TYPE_FLOAT     = 3,
	UF_TYPE_GUID      = 4,
	UF_TYPE_BYTES     = 5,
	UF_TYPE_BYTES2    = 6
};

enum UpdateFieldFlags
{
	UF_FLAG_NONE         = 0x000,
	UF_FLAG_PUBLIC       = 0x001,
	UF_FLAG_PRIVATE      = 0x002,
	UF_FLAG_OWNER_ONLY   = 0x004,
	UF_FLAG_UNK4         = 0x008,
	UF_FLAG_ITEM_OWNER   = 0x010,
	UF_FLAG_SPECIAL_INFO = 0x020,
	UF_FLAG_GROUP_ONLY   = 0x040,
	UF_FLAG_UNK8         = 0x080,
	UF_FLAG_DYNAMIC      = 0x100,
};

struct UpdateFieldDefinition
{
    UpdateFieldDefinition() = default;
    UpdateFieldDefinition(uint8 objectTypeMask_, const char* name_, uint16 offset_, uint16 size_, UpdateFieldValueTypes valueType_, uint16 flags_) :
        objectTypeMask(objectTypeMask_), name(name_), offset(offset_), size(size_), valueType(valueType_), flags(flags_) {}
    uint8 objectTypeMask = 0;
    const char* name = "";
    uint16 offset = 0;
    uint16 size = 0;
    UpdateFieldValueTypes valueType = UF_TYPE_NONE;
    uint16 flags = UF_FLAG_NONE;
};

namespace UpdateFields
{
    // Full definitions.
    extern std::vector<UpdateFieldDefinition> g_updateFieldDefinitions5875;
    extern std::vector<UpdateFieldDefinition> g_updateFieldDefinitions8606;
    extern std::vector<UpdateFieldDefinition> g_updateFieldDefinitions12340;
    extern std::vector<UpdateFieldDefinition> g_updateFieldDefinitions15595;

    // Fetch update field offset by name. Auto generated.
    extern std::map<std::string, uint16> g_updateFieldValues5875;
    extern std::map<std::string, uint16> g_updateFieldValues8606;
    extern std::map<std::string, uint16> g_updateFieldValues12340;
    extern std::map<std::string, uint16> g_updateFieldValues15595;

    // Fetch update field flags by offset. Auto generated.
    extern std::vector<uint32> g_containerUpdateFieldFlags5875;
    extern std::vector<uint32> g_containerUpdateFieldFlags8606;
    extern std::vector<uint32> g_containerUpdateFieldFlags12340;
    extern std::vector<uint32> g_containerUpdateFieldFlags15595;
    extern std::vector<uint32> g_playerUpdateFieldFlags5875;
    extern std::vector<uint32> g_playerUpdateFieldFlags8606;
    extern std::vector<uint32> g_playerUpdateFieldFlags12340;
    extern std::vector<uint32> g_playerUpdateFieldFlags15595;
    extern std::vector<uint32> g_gameObjectUpdateFieldFlags5875;
    extern std::vector<uint32> g_gameObjectUpdateFieldFlags8606;
    extern std::vector<uint32> g_gameObjectUpdateFieldFlags12340;
    extern std::vector<uint32> g_gameObjectUpdateFieldFlags15595;
    extern std::vector<uint32> g_dynamicObjectUpdateFieldFlags5875;
    extern std::vector<uint32> g_dynamicObjectUpdateFieldFlags8606;
    extern std::vector<uint32> g_dynamicObjectUpdateFieldFlags12340;
    extern std::vector<uint32> g_dynamicObjectUpdateFieldFlags15595;
    extern std::vector<uint32> g_corpseObjectUpdateFieldFlags5875;
    extern std::vector<uint32> g_corpseObjectUpdateFieldFlags8606;
    extern std::vector<uint32> g_corpseObjectUpdateFieldFlags12340;
    extern std::vector<uint32> g_corpseObjectUpdateFieldFlags15595;

    void SetupUpdateFieldMaps();
    void SetupUpdateFieldValuesMap(std::map<std::string, uint16>& valuesMap, std::vector<UpdateFieldDefinition> const& definitions);
    void SetupUpdateFieldFlagsVector(uint8 objectTypeMask, std::vector<uint32>& flagsVector, std::vector<UpdateFieldDefinition> const& definitions);

    std::map<std::string, uint16>* GetUpdateFieldsMapForBuild(uint16 build);
    uint16 GetUpdateFieldValue(std::string name, uint16 build);
    std::string GetUpdateFieldName(uint16 id, uint16 build);
    uint16 GetUpdateFieldFlags(uint8 objectTypeId, uint16 id, uint16 build);
    UpdateFieldDefinition const* GetUpdateFieldDefinitionByName(std::string name, uint16 build);
}

#endif
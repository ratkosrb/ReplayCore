#ifndef __DYNAMICOBJECT_H
#define __DYNAMICOBJECT_H

#include "Object.h"

enum DynamicObjectType
{
    DYNAMIC_OBJECT_PORTAL           = 0x0,      // unused
    DYNAMIC_OBJECT_AREA_SPELL       = 0x1,
    DYNAMIC_OBJECT_FARSIGHT_FOCUS   = 0x2,
};

struct DynamicObjectData;

class DynamicObject : public WorldObject
{
public:
    DynamicObject(DynamicObjectData const& dynamicObjectData);

    void Relocate(WorldLocation const& location) final
    {
        SetLocation(location);
        SetFloatValue("DYNAMICOBJECT_POS_X", location.x);
        SetFloatValue("DYNAMICOBJECT_POS_Y", location.y);
        SetFloatValue("DYNAMICOBJECT_POS_Z", location.z);
        SetFloatValue("DYNAMICOBJECT_FACING", location.o);
    }
    void Relocate(float x, float y, float z) final
    {
        SetPosition(x, y, z);
        SetFloatValue("DYNAMICOBJECT_POS_X", x);
        SetFloatValue("DYNAMICOBJECT_POS_Y", y);
        SetFloatValue("DYNAMICOBJECT_POS_Z", z);
    }
    void Relocate(float x, float y, float z, float o) final
    {
        SetPosition(x, y, z, o);
        SetFloatValue("DYNAMICOBJECT_POS_X", x);
        SetFloatValue("DYNAMICOBJECT_POS_Y", y);
        SetFloatValue("DYNAMICOBJECT_POS_Z", z);
        SetFloatValue("DYNAMICOBJECT_FACING", o);
    }

    void SetCasterGuid(ObjectGuid guid);
    void SetBytes(uint32 bytes);
    void SetSpellId(uint32 spellId);
    void SetRadius(float radius);
};

#endif
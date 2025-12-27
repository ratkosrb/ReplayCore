#include "DynamicObject.h"
#include "WorldServer.h"
#include "ReplayMgr.h"
#include "../Defines/ClientVersions.h"

DynamicObject::DynamicObject(DynamicObjectData const& dynamicObjectData) : WorldObject(dynamicObjectData.guid)
{
    m_objectTypeMask |= TYPEMASK_DYNAMICOBJECT;
    m_objectTypeId = TYPEID_DYNAMICOBJECT;
    m_updateFlags = (UPDATEFLAG_ALL | UPDATEFLAG_HAS_POSITION);

    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2)
        m_updateFlags |= UPDATEFLAG_POSITION;

    m_valuesCount = sWorld.GetUpdateField("DYNAMICOBJECT_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    SetUInt32Value(sWorld.GetUpdateField("OBJECT_FIELD_TYPE"), m_objectTypeMask);
    dynamicObjectData.InitializeDynamicObject(this);
}

void DynamicObject::SetCasterGuid(ObjectGuid guid)
{
    SetGuidValue("DYNAMICOBJECT_CASTER", guid);
}

void DynamicObject::SetBytes(uint32 bytes)
{
    SetUInt32Value("DYNAMICOBJECT_BYTES", bytes);
}

void DynamicObject::SetSpellId(uint32 spellId)
{
    SetUInt32Value("DYNAMICOBJECT_SPELLID", spellId);
}

void DynamicObject::SetRadius(float radius)
{
    SetFloatValue("DYNAMICOBJECT_RADIUS", radius);
}

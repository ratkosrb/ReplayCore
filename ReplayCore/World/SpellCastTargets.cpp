#include "SpellCastTargets.h"
#include "Player.h"
#include "GameObject.h"
#include "WorldServer.h"
#include "../Defines/ClientVersions.h"

SpellCastTargets::SpellCastTargets()
{
    m_itemTargetEntry  = 0;

    m_strTarget.clear();
    m_targetMask = 0;

    m_mapId = UINT32_MAX;
}

SpellCastTargets::~SpellCastTargets()
{
}

void SpellCastTargets::setUnitTarget(Unit const* target)
{
    if (!target)
        return;

    m_destPos = target->GetPosition();
    m_unitTargetGUID = target->GetObjectGuid();
    m_targetMask |= TARGET_FLAG_UNIT;
}

void SpellCastTargets::setDestination(float x, float y, float z)
{
    m_destPos.x = x;
    m_destPos.y = y;
    m_destPos.z = z;
    m_targetMask |= TARGET_FLAG_DEST_LOCATION;
}

void SpellCastTargets::setSource(float x, float y, float z)
{
    m_srcPos.x = x;
    m_srcPos.y = y;
    m_srcPos.z = z;
    m_targetMask |= TARGET_FLAG_SOURCE_LOCATION;
}

void SpellCastTargets::setGOTarget(GameObject const* target)
{
    m_GOTargetGUID = target->GetObjectGuid();
    //    m_targetMask |= TARGET_FLAG_GAMEOBJECT;
}

void SpellCastTargets::setItemTarget(ObjectGuid guid, uint32 entry)
{
    if (guid.IsEmpty() || !entry)
        return;

    m_itemTargetGUID = guid;
    m_itemTargetEntry = entry;
    m_targetMask |= TARGET_FLAG_ITEM;
}


void SpellCastTargets::setCorpseTarget(ObjectGuid guid)
{
    m_CorpseTargetGUID = guid;
}

void SpellCastTargets::read(ByteBuffer& data, WorldObject* caster)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        uint16 targetMask16;
        data >> targetMask16;
        m_targetMask = targetMask16;
    }
    else
        data >> m_targetMask;

    if (m_targetMask == TARGET_FLAG_SELF)
    {
        m_destPos.x = caster->GetPositionX();
        m_destPos.y = caster->GetPositionY();
        m_destPos.z = caster->GetPositionZ();
        return;
    }

    // TARGET_FLAG_UNK2 is used for non-combat pets, maybe other?
    if (m_targetMask & (TARGET_FLAG_UNIT | TARGET_FLAG_UNIT_MINIPET | TARGET_FLAG_UNIT_ENEMY))
        data >> m_unitTargetGUID.ReadAsPacked();

    if (m_targetMask & (TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_LOCKED))
        data >> m_GOTargetGUID.ReadAsPacked();

    if ((m_targetMask & (TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM)) && caster->GetTypeId() == TYPEID_PLAYER)
        data >> m_itemTargetGUID.ReadAsPacked();

    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2)
    {
        if (m_targetMask & (TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_CORPSE_ENEMY))
            data >> m_CorpseTargetGUID.ReadAsPacked();
    }

    if (m_targetMask & TARGET_FLAG_SOURCE_LOCATION)
    {
        if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_2_0)
            data >> m_srcTransportGUID.ReadAsPacked();
        data >> m_srcPos.x >> m_srcPos.y >> m_srcPos.z;
    }

    if (m_targetMask & TARGET_FLAG_DEST_LOCATION)
    {
        if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_8)
            data >> m_destTransportGUID.ReadAsPacked();
        data >> m_destPos.x >> m_destPos.y >> m_destPos.z;
    }

    if (m_targetMask & TARGET_FLAG_STRING)
        data >> m_strTarget;

    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        if (m_targetMask & (TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_CORPSE_ENEMY))
            data >> m_CorpseTargetGUID.ReadAsPacked();
    }
}

void SpellCastTargets::write(ByteBuffer& data) const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        data << uint16(m_targetMask);
    else
        data << uint32(m_targetMask);

    if (m_targetMask & (TARGET_FLAG_UNIT | TARGET_FLAG_CORPSE_ENEMY | TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_UNIT_MINIPET))
    {
        if (m_targetMask & TARGET_FLAG_UNIT)
        {
            if (!m_unitTargetGUID.IsEmpty())
                data << m_unitTargetGUID.WriteAsPacked();
            else
                data << uint8(0);
        }
        else if (m_targetMask & (TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_LOCKED))
        {
            if (!m_GOTargetGUID.IsEmpty())
                data << m_GOTargetGUID.WriteAsPacked();
            else
                data << uint8(0);
        }
        else if (m_targetMask & (TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_CORPSE_ENEMY))
            data << m_CorpseTargetGUID.WriteAsPacked();
        else
            data << uint8(0);
    }

    if (m_targetMask & (TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM))
    {
        if (!m_itemTargetGUID.IsEmpty())
            data << m_itemTargetGUID.WriteAsPacked();
        else
            data << uint8(0);
    }

    if (m_targetMask & TARGET_FLAG_SOURCE_LOCATION)
    {
        if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_2_0)
            data << m_srcTransportGUID.WriteAsPacked();
        data << m_srcPos.x << m_srcPos.y << m_srcPos.z;
    } 

    if (m_targetMask & TARGET_FLAG_DEST_LOCATION)
    {
        if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_8)
            data << m_destTransportGUID.WriteAsPacked();
        data << m_destPos.x << m_destPos.y << m_destPos.z;
    } 

    if (m_targetMask & TARGET_FLAG_STRING)
        data << m_strTarget;
}

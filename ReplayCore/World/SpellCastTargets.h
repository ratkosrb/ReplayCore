#ifndef __SPELL_CAST_TARGETS_H
#define __SPELL_CAST_TARGETS_H

#include "../Defines/Common.h"
#include "../Defines/ByteBuffer.h"
#include "ObjectGuid.h"

class WorldObject;
class Unit;
class GameObject;
class SpellCastTargets;

// SpellEntry::Targets
enum SpellCastTargetFlags
{
    TARGET_FLAG_SELF            = 0x00000000,
    TARGET_FLAG_UNUSED1         = 0x00000001,               // not used in any spells as of 2.4.3 (can be set dynamically)
    TARGET_FLAG_UNIT            = 0x00000002,               // pguid
    TARGET_FLAG_UNIT_RAID       = 0x00000004,               // not used in any spells as of 2.4.3 (can be set dynamically) - raid member
    TARGET_FLAG_UNIT_PARTY      = 0x00000008,               // not used in any spells as of 2.4.3 (can be set dynamically) - party member
    TARGET_FLAG_ITEM            = 0x00000010,               // pguid
    TARGET_FLAG_SOURCE_LOCATION = 0x00000020,               // 3xfloat
    TARGET_FLAG_DEST_LOCATION   = 0x00000040,               // 3xfloat
    TARGET_FLAG_UNIT_ENEMY      = 0x00000080,               // CanAttack == true
    TARGET_FLAG_UNIT_ALLY       = 0x00000100,               // CanAssist == true
    TARGET_FLAG_CORPSE_ENEMY    = 0x00000200,               // pguid, CanAssist == false
    TARGET_FLAG_UNIT_DEAD       = 0x00000400,               // skinning-like effects
    TARGET_FLAG_GAMEOBJECT      = 0x00000800,               // pguid, 0 spells in 2.4.3
    TARGET_FLAG_TRADE_ITEM      = 0x00001000,               // pguid, 0 spells
    TARGET_FLAG_STRING          = 0x00002000,               // string, 0 spells
    TARGET_FLAG_LOCKED          = 0x00004000,               // 199 spells, opening object/lock
    TARGET_FLAG_CORPSE_ALLY     = 0x00008000,               // pguid, CanAssist == true
    TARGET_FLAG_UNIT_MINIPET    = 0x00010000,               // pguid, not used in any spells as of 2.4.3 (can be set dynamically)
    TARGET_FLAG_GLYPH           = 0x00020000,               // used in glyph spells
    TARGET_FLAG_UNK3            = 0x00040000,               //
    TARGET_FLAG_VISUAL_CHAIN    = 0x00080000                // uint32, loop { vec3, guid -> if guid == 0 break }
};

struct SpellCastTargetsReader
{
    explicit SpellCastTargetsReader(SpellCastTargets& _targets, WorldObject* _caster) : targets(_targets), caster(_caster) {}

    SpellCastTargets& targets;
    WorldObject* caster;
};

class SpellCastTargets
{
    public:
        SpellCastTargets();
        ~SpellCastTargets();

        void read(ByteBuffer& data, WorldObject* caster);
        void write(ByteBuffer& data) const;

        SpellCastTargetsReader ReadForCaster(WorldObject* caster) { return SpellCastTargetsReader(*this, caster); }

        SpellCastTargets& operator=(const SpellCastTargets& target)
        {
            m_unitTargetGUID    = target.m_unitTargetGUID;
            m_GOTargetGUID      = target.m_GOTargetGUID;
            m_CorpseTargetGUID  = target.m_CorpseTargetGUID;
            m_itemTargetGUID    = target.m_itemTargetGUID;

            m_itemTargetEntry  = target.m_itemTargetEntry;

            m_srcTransportGUID = target.m_srcTransportGUID;
            m_destTransportGUID = target.m_destTransportGUID;

            m_srcPos = target.m_srcPos;
            m_destPos = target.m_destPos;

            m_strTarget = target.m_strTarget;

            m_targetMask = target.m_targetMask;

            m_mapId = target.m_mapId;

            return *this;
        }

        void setUnitTarget(Unit const* target);
        ObjectGuid getUnitTargetGuid() const { return m_unitTargetGUID; }

        void setDestination(float x, float y, float z);
        void setSource(float x, float y, float z);
        void getDestination(float& x, float& y, float& z) const { x = m_destPos.x; y = m_destPos.y; z = m_destPos.z; }
        Position getDestination() const { return m_destPos; }
        void getDestination(WorldLocation& loc) { loc.x = m_destPos.x; loc.y = m_destPos.y; loc.z = m_destPos.z; }
        void getSource(float& x, float& y, float& z) const { x = m_srcPos.x; y = m_srcPos.y; z = m_srcPos.z; }

        void setGOTarget(GameObject const* target);
        ObjectGuid getGOTargetGuid() const { return m_GOTargetGUID; }

        void setCorpseTarget(ObjectGuid guid);
        ObjectGuid getCorpseTargetGuid() const { return m_CorpseTargetGUID; }

        void setItemTarget(ObjectGuid guid, uint32 entry);
        ObjectGuid getItemTargetGuid() const { return m_itemTargetGUID; }
        uint32 getItemTargetEntry() const { return m_itemTargetEntry; }

        bool IsEmpty() const { return !m_GOTargetGUID && !m_unitTargetGUID && !m_itemTargetEntry && !m_CorpseTargetGUID; }

        Position m_srcPos;
        Position m_destPos;
        std::string m_strTarget;

        uint32 m_targetMask;

        uint32 m_mapId; // not to be written to packet in vanilla/tbc

    private:
        // object GUID/etc, can be used always
        ObjectGuid m_unitTargetGUID;
        ObjectGuid m_GOTargetGUID;
        ObjectGuid m_CorpseTargetGUID;
        ObjectGuid m_itemTargetGUID;
        uint32 m_itemTargetEntry;
        ObjectGuid m_srcTransportGUID;
        ObjectGuid m_destTransportGUID;
};

inline ByteBuffer& operator<< (ByteBuffer& buf, SpellCastTargets const& targets)
{
    targets.write(buf);
    return buf;
}

inline ByteBuffer& operator>> (ByteBuffer& buf, SpellCastTargetsReader const& targets)
{
    targets.targets.read(buf, targets.caster);
    return buf;
}

#endif

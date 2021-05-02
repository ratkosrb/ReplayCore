#include "Unit.h"
#include "WorldServer.h"
#include "ReplayMgr.h"
#include "GameDataMgr.h"
#include "../Defines/ClientVersions.h"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

float baseMoveSpeed[MAX_MOVE_TYPE_WOTLK] =
{
    2.5f,                                                   // MOVE_WALK
    7.0f,                                                   // MOVE_RUN
    4.5f,                                                   // MOVE_RUN_BACK
    4.722222f,                                              // MOVE_SWIM
    2.5f,                                                   // MOVE_SWIM_BACK
    3.141593f,                                              // MOVE_TURN_RATE
    7.0f,                                                   // MOVE_FLIGHT
    4.5f,                                                   // MOVE_FLIGHT_BACK
    3.141593f                                               // MOVE_PITCH_RATE
};

uint32 MoveSpline::m_maxId = 0;

void MoveSpline::Initialize(Vector3 const& startPosition, uint32 moveTime, uint8 type, uint32 flags, float orientation, std::vector<Vector3> const& destinationPoints, bool isCyclic, bool isCatmullrom)
{
    m_id = m_maxId++;
    m_startTimeMs = sReplayMgr.GetCurrentSniffTimeMs();
    m_startPosition = startPosition;
    m_moveTimeMs = moveTime;
    m_type = type;
    m_flags = flags;
    m_finalOrientation = orientation;
    m_destinationPoints = destinationPoints;
    if (m_destinationPoints.empty() && m_type != SPLINE_TYPE_STOP)
        m_destinationPoints.push_back(startPosition);
    m_cyclic = isCyclic;
    m_catmullrom = isCatmullrom;
    m_initialized = true;
}

void MoveSpline::WriteMove(ByteBuffer &data) const
{
    data << float(m_startPosition.x);
    data << float(m_startPosition.y);
    data << float(m_startPosition.z);
    data << uint32(m_id);
    data << uint8(m_type);
    if (m_type == SPLINE_TYPE_STOP)
        return;
    else if (m_type == SPLINE_TYPE_FACING_ANGLE)
        data << float(m_finalOrientation);
    data << uint32(m_flags);
    data << uint32(m_moveTimeMs);
    
    uint32 pointsCount = m_destinationPoints.size();
    data << uint32(pointsCount);
    if (pointsCount > 0)
    {
        if (m_catmullrom || pointsCount == 1)
        {
            for (auto const& itr : m_destinationPoints)
            {
                data << float(itr.x);
                data << float(itr.y);
                data << float(itr.z);
            }
        }
        else
        {
            // final destination
            uint32 finalPointIndex = pointsCount - 1;
            data << float(m_destinationPoints[finalPointIndex].x);
            data << float(m_destinationPoints[finalPointIndex].y);
            data << float(m_destinationPoints[finalPointIndex].z);

            // other points
            for (uint32 i = 0; i < (pointsCount - 1); i++)
            {
                data << float(m_destinationPoints[i].x);
                data << float(m_destinationPoints[i].y);
                data << float(m_destinationPoints[i].z);
            }
        }
    }
}

void MoveSpline::WriteCreate(ByteBuffer &data) const
{
    uint32 splineFlags = m_flags;
    if (m_type == SPLINE_TYPE_FACING_ANGLE)
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            splineFlags |= Vanilla::Final_Angle;
        else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            splineFlags |= TBC::Final_Angle;
        else
            splineFlags |= WotLK::Final_Angle;
    }
    data << uint32(splineFlags);
    if (m_type == SPLINE_TYPE_FACING_ANGLE)
        data << float(m_finalOrientation);
    data << uint32(1 + sReplayMgr.GetCurrentSniffTimeMs() - m_startTimeMs);
    data << uint32(m_moveTimeMs);
    data << uint32(m_id);

    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_1_0)
    {
        data << float(1.0f); // Spline Duration Multiplier
        data << float(1.0f); // Spline Duration Multiplier Next
        data << float(1.0f); // Spline Vertical Acceleration
        data << uint32(m_startTimeMs); // Spline Start Time
    }

    assert(!m_destinationPoints.empty());

    uint32 pointsCount = std::max<uint32>(4, m_destinationPoints.size());
    data << uint32(pointsCount);
    for (auto const& itr : m_destinationPoints)
    {
        data << float(itr.x);
        data << float(itr.y);
        data << float(itr.z);
    }
    if (m_destinationPoints.size() < 4)
    {
        for (uint32 i = 0; i < (4 - m_destinationPoints.size()); i++)
        {
            data << float(m_destinationPoints[0].x);
            data << float(m_destinationPoints[0].y);
            data << float(m_destinationPoints[0].z);
        }
    }

    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_8)
        data << uint8(m_catmullrom ? 1 : 0); // Spline Mode

    uint32 finalPointIndex = m_destinationPoints.size() - 1;
    data << float(m_destinationPoints[finalPointIndex].x);
    data << float(m_destinationPoints[finalPointIndex].y);
    data << float(m_destinationPoints[finalPointIndex].z);
}

void MoveSpline::Update(Unit* pUnit)
{
    if (!m_initialized || m_cyclic || !m_moveTimeMs)
        return;

    if (sReplayMgr.GetCurrentSniffTimeMs() < m_startTimeMs)
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            pUnit->RemoveUnitMovementFlag(Vanilla::MOVEFLAG_MASK_MOVING_OR_TURN | Vanilla::MOVEFLAG_SPLINE_ENABLED);
        else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            pUnit->RemoveUnitMovementFlag(TBC::MOVEFLAG_MASK_MOVING_OR_TURN | TBC::MOVEFLAG_SPLINE_ENABLED);
        else
            pUnit->RemoveUnitMovementFlag(WotLK::MOVEFLAG_MASK_MOVING_OR_TURN | WotLK::MOVEFLAG_SPLINE_ENABLED);

        Reset();
        return;
    }

    uint64 elapsedTime = sReplayMgr.GetCurrentSniffTimeMs() - m_startTimeMs;
    if (!elapsedTime)
        return;

    if (elapsedTime >= m_moveTimeMs)
    {
        if (m_finalOrientation != 100)
            pUnit->Relocate(m_destinationPoints[0].x, m_destinationPoints[0].y, m_destinationPoints[0].z, m_finalOrientation);
        else
            pUnit->Relocate(m_destinationPoints[0].x, m_destinationPoints[0].y, m_destinationPoints[0].z);

        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            pUnit->RemoveUnitMovementFlag(Vanilla::MOVEFLAG_MASK_MOVING_OR_TURN | Vanilla::MOVEFLAG_SPLINE_ENABLED);
        else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            pUnit->RemoveUnitMovementFlag(TBC::MOVEFLAG_MASK_MOVING_OR_TURN | TBC::MOVEFLAG_SPLINE_ENABLED);
        else
            pUnit->RemoveUnitMovementFlag(WotLK::MOVEFLAG_MASK_MOVING_OR_TURN | WotLK::MOVEFLAG_SPLINE_ENABLED);

        Reset();
        return;
    }

    if (m_destinationPoints.size() > 1)
    {
        float percentDone = float(elapsedTime) / float(m_moveTimeMs);
        uint32 reachedPoint = m_destinationPoints.size() * percentDone;
        if (reachedPoint > 1)
            pUnit->Relocate(m_destinationPoints[reachedPoint].x, m_destinationPoints[reachedPoint].y, m_destinationPoints[reachedPoint].z);
    }
}

Unit::Unit(CreatureData const& unitData) : WorldObject(unitData.guid)
{
    m_objectType |= TYPEMASK_UNIT;
    m_objectTypeId = TYPEID_UNIT;
    m_updateFlags = (UPDATEFLAG_LIVING | UPDATEFLAG_HAS_POSITION);
    InitializeMoveSpeeds();

    m_valuesCount = sWorld.GetUpdateField("UNIT_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    SetUInt32Value(OBJECT_FIELD_TYPE, m_objectType);
    InitializePlaceholderUnitFields();
    unitData.InitializeCreature(this);
    m_uint32Values_mirror = new uint32[m_valuesCount];
    memcpy(m_uint32Values_mirror, m_uint32Values, sizeof(uint32) * m_valuesCount);
}

void Unit::InitializePlaceholderUnitFields()
{
    SetUInt32Value("UNIT_FIELD_MAXPOWER2", 1000);
    SetUInt32Value("UNIT_FIELD_MAXPOWER3", 100);
    SetUInt32Value("UNIT_FIELD_MAXPOWER4", 100);
    SetUInt32Value("UNIT_FIELD_MAXPOWER6", 8);
    SetUInt32Value("UNIT_FIELD_MAXPOWER7", 1000);
    SetFloatValue("UNIT_FIELD_HOVERHEIGHT", 1.0f);
    SetUInt32Value("UNIT_FIELD_FLAGS_2", 2048);
    SetFloatValue("UNIT_MOD_CAST_SPEED", 1);
    SetFloatValue("UNIT_FIELD_MINDAMAGE", 5);
    SetFloatValue("UNIT_FIELD_MAXDAMAGE", 10);
    SetFloatValue("UNIT_FIELD_MINRANGEDDAMAGE", 5);
    SetFloatValue("UNIT_FIELD_MAXRANGEDDAMAGE", 10);
    SetUInt32Value("UNIT_FIELD_STAT0", 50);
    SetUInt32Value("UNIT_FIELD_STAT1", 50);
    SetUInt32Value("UNIT_FIELD_STAT2", 50);
    SetUInt32Value("UNIT_FIELD_STAT3", 50);
    SetUInt32Value("UNIT_FIELD_STAT4", 50);
    SetUInt32Value("UNIT_FIELD_RESISTANCES", 100);
    SetUInt32Value("UNIT_FIELD_ATTACK_POWER", 100);
    SetFloatValue("UNIT_FIELD_ATTACK_POWER_MULTIPLIER", 1);
    SetFloatValue("UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER", 1);
    SetFloatValue("UNIT_FIELD_POWER_COST_MULTIPLIER", 1);
}

void Unit::InitializeMoveSpeeds()
{
    for (int i = 0; i < MAX_MOVE_TYPE_WOTLK; i++)
        m_speedRate[i] = 1.0f;
}

void Unit::SetVirtualItem(uint8 slot, uint32 item_id)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        uint16 const UNIT_VIRTUAL_ITEM_SLOT_DISPLAY = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_SLOT_DISPLAY");
        uint16 const UNIT_VIRTUAL_ITEM_INFO = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_INFO");
        assert(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY);
        assert(UNIT_VIRTUAL_ITEM_INFO);

        if (item_id == 0)
        {
            SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + slot, 0);
            SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, 0);
            SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, 0);
            return;
        }

        ItemPrototype const* proto = sGameDataMgr.GetItemPrototype(item_id);
        if (!proto)
        {
            printf("Not listed in 'item_template' item (ID:%u) used as virtual item for %s\n", item_id, GetGuidStr().c_str());
            return;
        }

        SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + slot, proto->DisplayInfoID);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, Vanilla::VIRTUAL_ITEM_INFO_0_OFFSET_CLASS, proto->Class);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, Vanilla::VIRTUAL_ITEM_INFO_0_OFFSET_SUBCLASS, proto->SubClass);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, Vanilla::VIRTUAL_ITEM_INFO_0_OFFSET_MATERIAL, proto->Material);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, Vanilla::VIRTUAL_ITEM_INFO_0_OFFSET_INVENTORYTYPE, proto->InventoryType);

        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, Vanilla::VIRTUAL_ITEM_INFO_1_OFFSET_SHEATH, proto->Sheath);
    }
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        uint16 const UNIT_VIRTUAL_ITEM_SLOT_DISPLAY = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_SLOT_DISPLAY");
        uint16 const UNIT_VIRTUAL_ITEM_INFO = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_INFO");
        assert(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY);
        assert(UNIT_VIRTUAL_ITEM_INFO);

        if (item_id == 0)
        {
            SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + slot, 0);
            SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, 0);
            SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, 0);
            return;
        }

        ItemPrototype const* proto = sGameDataMgr.GetItemPrototype(item_id);
        if (!proto)
        {
            printf("Not listed in 'item_template' item (ID:%u) used as virtual item for %s\n", item_id, GetGuidStr().c_str());
            return;
        }

        SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + slot, proto->DisplayInfoID);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, TBC::VIRTUAL_ITEM_INFO_0_OFFSET_CLASS, proto->Class);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, TBC::VIRTUAL_ITEM_INFO_0_OFFSET_SUBCLASS, proto->SubClass);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, TBC::VIRTUAL_ITEM_INFO_0_OFFSET_UNK0, proto->SoundOverrideSubclass);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, TBC::VIRTUAL_ITEM_INFO_0_OFFSET_MATERIAL, proto->Material);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, TBC::VIRTUAL_ITEM_INFO_1_OFFSET_INVENTORYTYPE, proto->InventoryType);

        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, TBC::VIRTUAL_ITEM_INFO_1_OFFSET_SHEATH, proto->Sheath);
    }
    else if (uint16 uf = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_SLOT_ID"))
        SetUInt32Value(uf + slot, item_id);
}

uint32 Unit::GetAttackTime(WeaponAttackType att) const
{
    if (uint16 uf = sWorld.GetUpdateField("UNIT_FIELD_BASEATTACKTIME"))
        return GetUInt32Value(uf + att);
    return 0;
}

void Unit::SetAttackTime(WeaponAttackType att, uint32 val)
{
    if (uint16 uf = sWorld.GetUpdateField("UNIT_FIELD_BASEATTACKTIME"))
        return SetUInt32Value(uf + att, val);
}

Unit* Unit::GetTarget() const
{
    ObjectGuid guid =GetGuidValue("UNIT_FIELD_TARGET");
    if (guid.IsEmpty())
        return nullptr;

    if (guid == sWorld.GetClientPlayer()->GetObjectGuid())
        return sWorld.GetClientPlayer();

    return sWorld.FindUnit(guid);
}

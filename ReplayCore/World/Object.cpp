#include "Object.h"
#include "WorldServer.h"
#include "ReplayMgr.h"
#include "UpdateData.h"
#include "UpdateMask.h"
#include "Player.h"
#include "GameDataMgr.h"
#include "../Defines/ClientVersions.h"

void MovementInfo::Read(ByteBuffer &data)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        data >> moveFlags;
        data >> ctime;
        data >> pos.x;
        data >> pos.y;
        data >> pos.z;
        data >> pos.o;

        if (HasMovementFlag(Vanilla::MOVEFLAG_ONTRANSPORT))
        {
            data >> t_guid;
            data >> t_pos.x;
            data >> t_pos.y;
            data >> t_pos.z;
            data >> t_pos.o;
        }
        if (HasMovementFlag(Vanilla::MOVEFLAG_SWIMMING))
            data >> s_pitch;

        data >> fallTime;

        if (HasMovementFlag(Vanilla::MOVEFLAG_JUMPING))
        {
            data >> jump.velocity;
            data >> jump.cosAngle;
            data >> jump.sinAngle;
            data >> jump.xyspeed;
            if (!jump.startClientTime)
            {
                jump.startClientTime = ctime;
                jump.start = pos;
            }
        }
        else
            jump.startClientTime = 0;

        if (HasMovementFlag(Vanilla::MOVEFLAG_SPLINE_ELEVATION))
        {
            data >> splineElevation;                                     // unknown
        }
    }
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        data >> moveFlags;
        data >> moveFlags2;
        data >> time;
        data >> pos.x;
        data >> pos.y;
        data >> pos.z;
        data >> pos.o;

        if (HasMovementFlag(TBC::MOVEFLAG_ONTRANSPORT))
        {
            data >> t_guid;
            data >> t_pos.x;
            data >> t_pos.y;
            data >> t_pos.z;
            data >> t_pos.o;
            data >> t_time;
        }
        if (HasMovementFlag(TBC::MOVEFLAG_SWIMMING | TBC::MOVEFLAG_FLYING2))
        {
            data >> s_pitch;
        }

        data >> fallTime;

        if (HasMovementFlag(TBC::MOVEFLAG_FALLING))
        {
            data >> jump.velocity;
            data >> jump.sinAngle;
            data >> jump.cosAngle;
            data >> jump.xyspeed;
        }

        if (HasMovementFlag(TBC::MOVEFLAG_SPLINE_ELEVATION))
        {
            data >> splineElevation;
        }
    }
    else
    {
        data >> moveFlags;
        data >> moveFlags2;
        data >> time;
        data >> pos.x;
        data >> pos.y;
        data >> pos.z;
        data >> pos.o;

        if (HasMovementFlag(WotLK::MOVEFLAG_ONTRANSPORT))
        {
            data >> t_guid.ReadAsPacked();
            data >> t_pos.x;
            data >> t_pos.y;
            data >> t_pos.z;
            data >> t_pos.o;
            data >> t_time;
            data >> t_seat;

            if (moveFlags2 & WotLK::MOVEFLAG2_INTERP_MOVEMENT)
            {
                data >> t_time2;
            }
        }

        if ((HasMovementFlag(WotLK::MOVEFLAG_SWIMMING | WotLK::MOVEFLAG_FLYING)) || (moveFlags2 & WotLK::MOVEFLAG2_ALLOW_PITCHING))
        {
            data >> s_pitch;
        }

        data >> fallTime;

        if (HasMovementFlag(WotLK::MOVEFLAG_FALLING))
        {
            data >> jump.velocity;
            data >> jump.sinAngle;
            data >> jump.cosAngle;
            data >> jump.xyspeed;
        }

        if (HasMovementFlag(WotLK::MOVEFLAG_SPLINE_ELEVATION))
        {
            data >> splineElevation;
        }
    }
}

void MovementInfo::CorrectData(Unit* mover)
{

}

void MovementInfo::Write(ByteBuffer &data) const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        data << moveFlags;
        data << time;
        data << pos.x;
        data << pos.y;
        data << pos.z;
        data << pos.o;

        if (HasMovementFlag(Vanilla::MOVEFLAG_ONTRANSPORT))
        {
            data << t_guid;
            data << t_pos.x;
            data << t_pos.y;
            data << t_pos.z;
            data << t_pos.o;
        }
        if (HasMovementFlag(Vanilla::MOVEFLAG_SWIMMING))
            data << s_pitch;

        data << fallTime;

        if (HasMovementFlag(Vanilla::MOVEFLAG_JUMPING))
        {
            data << jump.velocity;
            data << jump.cosAngle;
            data << jump.sinAngle;
            data << jump.xyspeed;
        }

        if (HasMovementFlag(Vanilla::MOVEFLAG_SPLINE_ELEVATION))
        {
            data << splineElevation;
        }
    }
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        data << moveFlags;
        data << moveFlags2;
        data << time;
        data << pos.x;
        data << pos.y;
        data << pos.z;
        data << pos.o;

        if (HasMovementFlag(TBC::MOVEFLAG_ONTRANSPORT))
        {
            data << t_guid;
            data << t_pos.x;
            data << t_pos.y;
            data << t_pos.z;
            data << t_pos.o;
            data << t_time;
        }
        if (HasMovementFlag(TBC::MOVEFLAG_SWIMMING | TBC::MOVEFLAG_FLYING2))
        {
            data << s_pitch;
        }

        data << fallTime;

        if (HasMovementFlag(TBC::MOVEFLAG_FALLING))
        {
            data << jump.velocity;
            data << jump.sinAngle;
            data << jump.cosAngle;
            data << jump.xyspeed;
        }

        if (HasMovementFlag(TBC::MOVEFLAG_SPLINE_ELEVATION))
        {
            data << splineElevation;
        }
    }
    else
    {
        data << moveFlags;
        data << moveFlags2;
        data << time;
        data << pos.x;
        data << pos.y;
        data << pos.z;
        data << pos.o;

        if (HasMovementFlag(WotLK::MOVEFLAG_ONTRANSPORT))
        {
            data << t_guid.WriteAsPacked();
            data << t_pos.x;
            data << t_pos.y;
            data << t_pos.z;
            data << t_pos.o;
            data << t_time;
            data << t_seat;

            if (moveFlags2 & WotLK::MOVEFLAG2_INTERP_MOVEMENT)
            {
                data << t_time2;
            }
        }

        if ((HasMovementFlag(WotLK::MOVEFLAG_SWIMMING | WotLK::MOVEFLAG_FLYING)) || (moveFlags2 & WotLK::MOVEFLAG2_ALLOW_PITCHING))
        {
            data << s_pitch;
        }

        data << fallTime;

        if (HasMovementFlag(WotLK::MOVEFLAG_FALLING))
        {
            data << jump.velocity;
            data << jump.sinAngle;
            data << jump.cosAngle;
            data << jump.xyspeed;
        }

        if (HasMovementFlag(WotLK::MOVEFLAG_SPLINE_ELEVATION))
        {
            data << splineElevation;
        }
    }
}

Object::Object(ObjectData const& objectData)
{
    m_guid = objectData.guid;
    m_packGuid.Set(m_guid);
    m_valuesCount = sWorld.GetUpdateField("OBJECT_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    objectData.InitializeObject(this);
    m_uint32Values_mirror = new uint32[m_valuesCount];
    memcpy(m_uint32Values_mirror, m_uint32Values, sizeof(uint32) * m_valuesCount);
}

WorldObject::WorldObject(WorldObjectData const& worldObjectData) : Object(worldObjectData.guid)
{
    m_valuesCount = sWorld.GetUpdateField("OBJECT_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    worldObjectData.InitializeWorldObject(this);
    m_uint32Values_mirror = new uint32[m_valuesCount];
    memcpy(m_uint32Values_mirror, m_uint32Values, sizeof(uint32) * m_valuesCount);
}

void Object::MarkForClientUpdate()
{
    if (!m_isVisible)
        return;

    m_objectUpdated = true;
}

int32 Object::GetInt32Value(const char* index) const
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        return GetInt32Value(uf);
    return 0;
}

uint32 Object::GetUInt32Value(const char* index) const
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        return GetUInt32Value(uf);
    return 0;
}

uint64 Object::GetUInt64Value(const char* index) const
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        return GetUInt64Value(uf);
    return 0;
}

float Object::GetFloatValue(const char* index) const
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        return GetFloatValue(uf);
    return 0.0f;
}

uint8 Object::GetByteValue(const char* index, uint8 offset) const
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        return GetByteValue(uf, offset);
    return 0;
}

uint16 Object::GetUInt16Value(const char* index, uint8 offset) const
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        return GetUInt16Value(uf, offset);
    return 0;
}

void Object::SetInt32Value(const char* index, int32  value)
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        SetInt32Value(uf, value);
}

void Object::SetUInt32Value(const char* index, uint32  value)
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        SetUInt32Value(uf, value);
}

void Object::SetUInt64Value(const char* index, uint64 const& value)
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        SetUInt64Value(uf, value);
}

void Object::SetFloatValue(const char* index, float   value)
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        SetFloatValue(uf, value);
}

void Object::SetByteValue(const char* index, uint8 offset, uint8 value)
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        SetByteValue(uf, offset, value);
}

void Object::SetUInt16Value(const char* index, uint8 offset, uint16 value)
{
    if (uint16 uf = sWorld.GetUpdateField(index))
        SetUInt16Value(uf, offset, value);
}

bool Object::PrintIndexError(uint32 index, bool set) const
{
    printf("%s nonexistent value field: %u (count: %u) for object typeid: %u type mask: %u\n",
        (set ? "set value to" : "get value from"), index, m_valuesCount, GetTypeId(), m_objectType);

    // ASSERT must fail after function call
    return false;
}

void Object::SetInt32Value(uint16 index, int32 value)
{
    assert(index < m_valuesCount || PrintIndexError(index, true));

    if (m_int32Values[index] != value)
    {
        m_int32Values[index] = value;
        MarkForClientUpdate();
    }
}

void Object::SetUInt32Value(uint16 index, uint32 value)
{
    assert(index < m_valuesCount || PrintIndexError(index, true));

    if (m_uint32Values[index] != value)
    {
        m_uint32Values[index] = value;
        MarkForClientUpdate();
    }
}

void Object::SetUInt64Value(uint16 index, uint64 const& value)
{
    assert(index + 1 < m_valuesCount || PrintIndexError(index, true));
    if (*((uint64*) & (m_uint32Values[index])) != value)
    {
        uint32 first = m_uint32Values[index] = *((uint32*)&value);
        uint32 second = m_uint32Values[index + 1] = *(((uint32*)&value) + 1);

        // Force an update at both mirrored values, even if only one index was changed
        // If we don't update the second index, it may become perpetually stuck and
        // lead to weird client behaviour such as not displaying a target (only the
        // first part is networked). This is typically only an issue for units which
        // have these values set at create time, as the client will ignore unpacked
        // 64bit values that arent fully networked in the create stage, yet accept
        // them in the update stage (presumably it defaults to 0 for both bytes if
        // not present, making it "OK" if we only send one in the future).
        // Note that this behaviour is inconsistent as well, sometimes it works
        // with only one part whereas other times it does not. It appears to be
        // related to the number of (player) units in the vicinity.
        // The first update will correct any malformed 64bit data.
        if (m_uint32Values_mirror)
        {
            m_uint32Values_mirror[index] = first + 1;
            m_uint32Values_mirror[index + 1] = second + 1;
            MarkForClientUpdate();
        }
    }
}

void Object::SetFloatValue(uint16 index, float value)
{
    assert(index < m_valuesCount || PrintIndexError(index, true));

    if (m_floatValues[index] != value)
    {
        m_floatValues[index] = value;
        MarkForClientUpdate();
    }
}

void Object::SetByteValue(uint16 index, uint8 offset, uint8 value)
{
    assert(index < m_valuesCount || PrintIndexError(index, true));

    if (offset > 4)
    {
        printf("Object::SetByteValue: wrong offset %u\n", offset);
        return;
    }

    if (uint8(m_uint32Values[index] >> (offset * 8)) != value)
    {
        m_uint32Values[index] &= ~uint32(uint32(0xFF) << (offset * 8));
        m_uint32Values[index] |= uint32(uint32(value) << (offset * 8));
        MarkForClientUpdate();
    }
}

void Object::SetUInt16Value(uint16 index, uint8 offset, uint16 value)
{
    assert(index < m_valuesCount || PrintIndexError(index, true));

    if (offset > 2)
    {
        printf("Object::SetUInt16Value: wrong offset %u\n", offset);
        return;
    }

    if (uint16(m_uint32Values[index] >> (offset * 16)) != value)
    {
        m_uint32Values[index] &= ~uint32(uint32(0xFFFF) << (offset * 16));
        m_uint32Values[index] |= uint32(uint32(value) << (offset * 16));
        MarkForClientUpdate();
    }
}

void Object::_SetUpdateBits(UpdateMask* updateMask, Player* /*target*/) const
{
    for (uint16 index = 0; index < m_valuesCount; ++index)
    {
        if (m_uint32Values_mirror[index] != m_uint32Values[index])
            updateMask->SetBit(index);
    }
}

void Object::_SetCreateBits(UpdateMask* updateMask, Player* /*target*/) const
{
    for (uint16 index = 0; index < m_valuesCount; ++index)
    {
        if (GetUInt32Value(index) != 0)
            updateMask->SetBit(index);
    }
}

void Object::SendCreateUpdateToPlayer(Player* player)
{
    // send create update to player
    UpdateData upd;

    BuildCreateUpdateBlockForPlayer(&upd, player);
    upd.Send();
    m_isNewObject = false;
}

void Object::BuildCreateUpdateBlockForPlayer(UpdateData* data, Player* target) const
{
    if (!target)
        return;

    uint8 updatetype = UPDATETYPE_CREATE_OBJECT;
    uint8 updateFlags = m_updateFlags;

    if (target == this)                                     // building packet for yourself
        updateFlags |= UPDATEFLAG_SELF;

    if (m_isNewObject)
        updatetype = UPDATETYPE_CREATE_OBJECT2;


    printf("BuildCreateUpdate: update-type: %u, object-type: %u got updateFlags: %X\n", updatetype, m_objectTypeId, updateFlags);

    ByteBuffer buf(500);
    buf << (uint8)updatetype;
    buf << GetPackGUID();
    buf << uint8(m_objectTypeId);
    BuildMovementUpdate(&buf, updateFlags);

    UpdateMask updateMask;
    updateMask.SetCount(m_valuesCount);
    _SetCreateBits(&updateMask, target);
    BuildValuesUpdate(updatetype, &buf, &updateMask, target);
    data->AddUpdateBlock(buf);
}

void Object::BuildMovementUpdate(ByteBuffer* data, uint8 updateFlags) const
{
    *data << uint8(updateFlags);                            // update flags

    if (updateFlags & UPDATEFLAG_LIVING)
    {
        Unit const* unit = ToUnit();
        ASSERT(unit);
        MovementInfo m = unit->m_movementInfo;
        if (!m.ctime)
        {
            m.time = sWorld.GetServerTimeMs() + 1000;
            m.ChangePosition(unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), unit->GetOrientation());
        }
        *data << m;


        if (unit)
        {
            for (int i = 0; i < sGameDataMgr.GetMoveSpeedsCount(); ++i)
                *data << float(unit->GetSpeed(UnitMoveType(i)));
            
            // Send current movement informations
            //if (unit->m_movementInfo.moveFlags & MOVEFLAG_SPLINE_ENABLED)
            //    Movement::PacketBuilder::WriteCreate(*(unit->movespline), *data);
        }
        else
            for (int i = 0; i < sGameDataMgr.GetMoveSpeedsCount(); ++i)
                *data << float(1.0f);
    }
    else
    {
        if (updateFlags & UPDATEFLAG_HAS_POSITION)                     // 0x40
        {
            WorldObject* object = ((WorldObject*)this);

            *data << float(object->GetPositionX());
            *data << float(object->GetPositionY());
            *data << float(object->GetPositionZ());
            *data << float(object->GetOrientation());
        }
    }
    if (updateFlags & UPDATEFLAG_HIGHGUID)
    {
        // unk uint32.
        *data << uint32(0);
    }

    if (updateFlags & UPDATEFLAG_ALL)                       // 0x10
    {
        // unk uint32.
        *data << uint32(1);
    }

    if (updateFlags & UPDATEFLAG_FULLGUID)
    {
        if (Unit const* me = ToUnit())
        {
            *data << me->GetMeleeVictimGuid().WriteAsPacked();
        }
        else
            *data << uint8(0); // Empty pack guid
    }
    // 0x2
    if (updateFlags & UPDATEFLAG_TRANSPORT)
    {
        // transport progress or mstime.
        *data << uint32(sWorld.GetServerTimeMs());
    }
}

void Object::BuildValuesUpdate(uint8 updatetype, ByteBuffer* data, UpdateMask* updateMask, Player* target) const
{
    if (!target)
        return;

    assert(updateMask && updateMask->GetCount() == m_valuesCount);

    *data << (uint8)updateMask->GetBlockCount();
    data->append(updateMask->GetMask(), updateMask->GetLength());

    for (uint16 index = 0; index < m_valuesCount; ++index)
    {
        if (updateMask->GetBit(index))
        {
            // send in current format (float as float, uint32 as uint32)
            *data << m_uint32Values[index];
        }
    }
}
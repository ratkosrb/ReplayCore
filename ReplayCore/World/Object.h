#ifndef __OBJECT_H
#define __OBJECT_H

#include "../Defines/Common.h"
#include "ObjectGuid.h"
#include "ObjectDefines.h"
#include "Geometry.h"
#include "UpdateData.h"

struct ObjectData;
struct WorldObjectData;
class UpdateMask;
class Player;
class Unit;

class Object
{
public:
    Object() = default;
    Object(ObjectGuid guid) : m_guid(guid)
    {
        m_packGuid.Set(guid);
    }
    Object(ObjectData const& objectData);

    uint8 GetTypeId() const { return m_objectTypeId; }
    bool IsType(TypeMask mask) const { return (mask & m_objectType) != 0; }
    /*
    uint32 GetEntry() const { return m_objectData.entry; }
    void SetEntry(uint32 entry) { m_objectData.entry = entry; }
    float GetObjectScale() const { return m_objectData.scale; }
    void SetObjectScale(float scale) { m_objectData.scale = scale; }
    */

    void MarkForClientUpdate();

    int32 const& GetInt32Value(const char* index) const;

    uint32 const& GetUInt32Value(const char* index) const;

    uint64 const& GetUInt64Value(const char* index) const;

    float const& GetFloatValue(const char* index) const;

    uint8 GetByteValue(const char* index, uint8 offset) const;

    uint16 GetUInt16Value(const char* index, uint8 offset) const;

    ObjectGuid const& GetGuidValue(const char* index) const { return *reinterpret_cast<ObjectGuid const*>(&GetUInt64Value(index)); }
    std::string GetGuidStr() const { return GetObjectGuid().GetString(); }
    ObjectGuid const& GetObjectGuid() const { return m_guid; }
    PackedGuid const& GetPackGUID() const { return m_packGuid; }

    void SetInt32Value(const char* index, int32  value);
    void SetUInt32Value(const char* index, uint32  value);
    void SetUInt64Value(const char* index, uint64 const& value);
    void SetFloatValue(const char* index, float   value);
    void SetByteValue(const char* index, uint8 offset, uint8 value);
    void SetUInt16Value(const char* index, uint8 offset, uint16 value);
    void SetInt16Value(const char* index, uint8 offset, int16 value) { SetUInt16Value(index, offset, (uint16)value); }
    void SetGuidValue(const char* index, ObjectGuid const& value) { SetUInt64Value(index, value.GetRawValue()); }

    void _SetUpdateBits(UpdateMask* updateMask, Player* target) const;
    void _SetCreateBits(UpdateMask* updateMask, Player* target) const;
    void SendCreateUpdateToPlayer(Player* player);
    void BuildCreateUpdateBlockForPlayer(UpdateData* data, Player* target) const;
    void BuildValuesUpdate(uint8 updatetype, ByteBuffer* data, UpdateMask* updateMask, Player* target) const;
    void BuildMovementUpdate(ByteBuffer* data, uint8 updateFlags) const;
    
    inline bool IsWorldObject() const { return IsType(TYPEMASK_WORLDOBJECT); }
    WorldObject* ToWorldObject() { if (IsWorldObject()) return reinterpret_cast<WorldObject*>(this); else return nullptr; }
    WorldObject const* ToWorldObject() const { if (IsWorldObject()) return reinterpret_cast<WorldObject const*>(this); else return nullptr; }

    inline bool IsPlayer() const { return GetTypeId() == TYPEID_PLAYER; }
    Player* ToPlayer() { if (IsPlayer()) return reinterpret_cast<Player*>(this); else return nullptr; }
    Player const* ToPlayer() const { if (IsPlayer()) return reinterpret_cast<Player const*>(this); else return nullptr; }

    inline bool IsCreature() const { return GetTypeId() == TYPEID_UNIT; }

    inline bool IsUnit() const { return IsType(TYPEMASK_UNIT); }
    Unit* ToUnit() { if (IsUnit()) return reinterpret_cast<Unit*>(this); else return nullptr; }
    Unit const* ToUnit() const { if (IsUnit()) return reinterpret_cast<Unit const*>(this); else return nullptr; }

protected:
    bool m_isVisible = false;
    bool m_isNewObject = true;
    bool m_objectUpdated = false;
    ObjectGuid m_guid;
    PackedGuid m_packGuid;
    uint8 m_objectTypeId = TYPEID_OBJECT;
    uint16 m_objectType = TYPEMASK_OBJECT;
    uint8 m_updateFlags = 0;
    union
    {
        int32* m_int32Values = nullptr;
        uint32* m_uint32Values;
        float* m_floatValues;
    };
    uint32* m_uint32Values_mirror = nullptr;;
    uint16 m_valuesCount = 0;

    int32 const& GetInt32Value(uint16 index) const
    {
        assert(index < m_valuesCount || PrintIndexError(index, false));
        return m_int32Values[index];
    }

    uint32 const& GetUInt32Value(uint16 index) const
    {
        assert(index < m_valuesCount || PrintIndexError(index, false));
        return m_uint32Values[index];
    }

    uint64 const& GetUInt64Value(uint16 index) const
    {
        assert(index + 1 < m_valuesCount || PrintIndexError(index, false));
        return *((uint64*)&(m_uint32Values[index]));
    }

    float const& GetFloatValue(uint16 index) const
    {
        assert(index < m_valuesCount || PrintIndexError(index, false));
        return m_floatValues[index];
    }

    uint8 GetByteValue(uint16 index, uint8 offset) const
    {
        assert(index < m_valuesCount || PrintIndexError(index, false));
        assert(offset < 4);
        return *(((uint8*)&m_uint32Values[index]) + offset);
    }

    uint16 GetUInt16Value(uint16 index, uint8 offset) const
    {
        assert(index < m_valuesCount || PrintIndexError(index, false));
        assert(offset < 2);
        return *(((uint16*)&m_uint32Values[index]) + offset);
    }

    ObjectGuid const& GetGuidValue(uint16 index) const { return *reinterpret_cast<ObjectGuid const*>(&GetUInt64Value(index)); }

    void SetInt32Value(uint16 index, int32  value);
    void SetUInt32Value(uint16 index, uint32  value);
    void SetUInt64Value(uint16 index, uint64 const& value);
    void SetFloatValue(uint16 index, float   value);
    void SetByteValue(uint16 index, uint8 offset, uint8 value);
    void SetUInt16Value(uint16 index, uint8 offset, uint16 value);
    void SetInt16Value(uint16 index, uint8 offset, int16 value) { SetUInt16Value(index, offset, (uint16)value); }
    void SetGuidValue(uint16 index, ObjectGuid const& value) { SetUInt64Value(index, value.GetRawValue()); }
    bool PrintIndexError(uint32 index, bool set) const;
};

class WorldObject : public Object
{
public:
    WorldObject() = default;
    WorldObject(ObjectGuid guid) : Object(guid) {}
    WorldObject(WorldObjectData const& worldObjectData);

    bool IsVisible() const { return m_isVisible; }
    void SetVisibility(bool on) { m_isVisible = on; }
    uint32 GetMapId() const { return m_location.mapId; }
    float GetPositionX() const { return m_location.x; }
    float GetPositionY() const { return m_location.y; }
    float GetPositionZ() const { return m_location.z; }
    float GetOrientation() const { return m_location.o; }
    Position& GetPosition() { return m_location; }
    Position const& GetPosition() const { return m_location; }
    WorldLocation& GetLocation() { return m_location; }
    WorldLocation const& GetLocation() const { return m_location; }
    void SetPosition(float x, float y, float z)
    {
        m_location.x = x;
        m_location.y = y;
        m_location.z = z;
    }
    void SetPosition(float x, float y, float z, float o)
    {
        m_location.x = x;
        m_location.y = y;
        m_location.z = z;
        m_location.o = o;
    }
    void SetPosition(Position const& position)
    {
        m_location.x = position.x;
        m_location.y = position.y;
        m_location.z = position.z;
        m_location.o = position.o;
    }
    void SetLocation(WorldLocation const& location)
    {
        m_location = location;
    }
    float GetDistance2D(float x, float y) const
    {
        return Geometry::GetDistance2D(m_location.x, m_location.y, x, y);
    }
    float GetDistance2D(WorldObject const* pObject) const
    {
        return Geometry::GetDistance2D(m_location, pObject->GetPosition());
    }
    float GetDistance3D(float x, float y, float z) const
    {
        return Geometry::GetDistance3D(m_location.x, m_location.y, m_location.z, x, y, z);
    }
    float GetDistance3D(WorldObject const* pObject) const
    {
        return Geometry::GetDistance3D(m_location, pObject->GetPosition());
    }
    // Return angle in range 0..2*pi
    float GetAngle(float const x, float const y) const
    {
        float dx = x - GetPositionX();
        float dy = y - GetPositionY();

        float ang = atan2(dy, dx);
        ang = (ang >= 0) ? ang : 2 * M_PI_F + ang;
        return ang;
    }
    float GetAngle(WorldObject const* pObject) const
    {
        return GetAngle(pObject->GetPositionX(), pObject->GetPositionY());
    }
protected:
    WorldLocation m_location;
    bool m_isVisible = true;
};


#endif
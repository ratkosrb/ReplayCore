#ifndef __OBJECT_H
#define __OBJECT_H

#include "../Defines/Common.h"
#include "ObjectGuid.h"
#include "ObjectDefines.h"
#include "Geometry.h"

// Only the mutable update fields.
struct ObjectData
{
    uint32 entry = 0;
    float scale = DEFAULT_OBJECT_SCALE;
};

class Object
{
public:
    Object() = default;
    Object(ObjectGuid guid, ObjectData objectData) :
        m_guid(guid), m_objectData(objectData) {}

    uint8 GetTypeId() const { return m_objectTypeId; }
    bool IsType(TypeMask mask) const { return (mask & m_objectType) != 0; }
    uint32 GetEntry() const { return m_objectData.entry; }
    void SetEntry(uint32 entry) { m_objectData.entry = entry; }
    float GetObjectScale() const { return m_objectData.scale; }
    void SetObjectScale(float scale) { m_objectData.scale = scale; }

protected:
    ObjectGuid m_guid;
    uint8 m_objectTypeId = TYPEID_OBJECT;
    uint16 m_objectType = TYPEMASK_OBJECT;
    ObjectData m_objectData;
};

class WorldObject : public Object
{
public:
    WorldObject() = default;
    WorldObject(ObjectGuid guid, ObjectData objectData, WorldLocation location) :
        Object(guid, objectData), m_location(location) {}

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
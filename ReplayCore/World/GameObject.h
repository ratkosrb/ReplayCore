#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "Object.h"

struct GameObjectData;

class GameObject : public WorldObject
{
public:
    GameObject(GameObjectData const& gameObjectData);

    void Relocate(WorldLocation const& location) final
    {
        WorldObject::Relocate(location);
        SetFloatValue("GAMEOBJECT_POS_X", location.x);
        SetFloatValue("GAMEOBJECT_POS_Y", location.y);
        SetFloatValue("GAMEOBJECT_POS_Z", location.z);
        SetFloatValue("GAMEOBJECT_FACING", location.o);
    }
    void Relocate(float x, float y, float z) final
    {
        WorldObject::Relocate(x, y, z);
        SetFloatValue("GAMEOBJECT_POS_X", x);
        SetFloatValue("GAMEOBJECT_POS_Y", y);
        SetFloatValue("GAMEOBJECT_POS_Z", z);
    }
    void Relocate(float x, float y, float z, float o) final
    {
        WorldObject::Relocate(x, y, z, o);
        SetFloatValue("GAMEOBJECT_POS_X", x);
        SetFloatValue("GAMEOBJECT_POS_Y", y);
        SetFloatValue("GAMEOBJECT_POS_Z", z);
        SetFloatValue("GAMEOBJECT_FACING", o);
    }

    void SetRotation(float const* rotation);
    void SetCreatedByGuid(ObjectGuid guid);
    void SetDisplayId(uint32 displayId);
    void SetFlags(uint32 flags);
    void SetType(uint8 type);
    uint8 GetType() const;
    void SetState(uint8 state);
    void SetArtKit(uint8 artKit);
    void SetAnimProgress(uint8 animProgress);
    void SetFactionTemplate(uint32 faction);
    void SetLevel(uint32 level);
    void SetDynamicFlags(uint16 flags);
    void SetPathProgress(uint16 pathProgress);
    uint16 GetPathProgress() const;
    void SetPathTimer(uint32 pathTimer) { m_pathTimer = pathTimer; }
    uint32 GetPathTimer() const;
    int64 GetPackedLocalRotation() const { return m_packedLocalRotation; }
    bool IsTransport() const override;
protected:
    uint32 m_pathTimer = 0;
    int64 m_packedLocalRotation = 0;
};

#endif
#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include "Object.h"

struct GameObjectData;

class GameObject : public WorldObject
{
    friend class Object;
public:
    GameObject(GameObjectData const& unitData);

    void SetRotation(float const* rotation);
    void SetType(uint8 type);
    void SetState(uint8 state);
    void SetArtKit(uint8 artKit);
    void SetAnimProgress(uint8 animProgress);
    void SetDynamicFlags(uint16 flags);
    void SetPathProgress(uint16 pathProgress);
    int64 GetPackedLocalRotation() const { return m_packedLocalRotation; }
protected:
    int64 m_packedLocalRotation = 0;
};

#endif
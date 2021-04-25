#include "GameObject.h"
#include "WorldServer.h"
#include "ReplayMgr.h"
#include "../Defines//ClientVersions.h"

GameObject::GameObject(GameObjectData const& goData) : WorldObject(goData.guid)
{
    m_objectType |= TYPEMASK_GAMEOBJECT;
    m_objectTypeId = TYPEID_GAMEOBJECT;
    m_updateFlags = (UPDATEFLAG_ALL | UPDATEFLAG_HAS_POSITION);
    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_1_0)
        m_updateFlags |= UPDATEFLAG_ROTATION;

    m_valuesCount = sWorld.GetUpdateField("GAMEOBJECT_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    SetUInt32Value(OBJECT_FIELD_TYPE, m_objectType);
    goData.InitializeGameObject(this);
    m_uint32Values_mirror = new uint32[m_valuesCount];
    memcpy(m_uint32Values_mirror, m_uint32Values, sizeof(uint32) * m_valuesCount);
}

enum
{
    PACK_COEFF_YZ = 1 << 20,
    PACK_COEFF_X = 1 << 21,
};

int64 CompressQuaternion(float rotX, float rotY, float rotZ, float rotW)
{
    int8 w_sign = (rotW >= 0 ? 1 : -1);
    int64 X = int32(rotX * PACK_COEFF_X) * w_sign & ((1 << 22) - 1);
    int64 Y = int32(rotY * PACK_COEFF_YZ) * w_sign & ((1 << 21) - 1);
    int64 Z = int32(rotZ * PACK_COEFF_YZ) * w_sign & ((1 << 21) - 1);
    return Z | (Y << 21) | (X << 42);
}

void GameObject::SetRotation(float const* rotation)
{
    if (uint16 field = sWorld.GetUpdateField("GAMEOBJECT_ROTATION"))
    {
        for (uint32 i = 0; i < 4; i++)
            SetFloatValue(field + i, rotation[i]);
    }
    else if (field = sWorld.GetUpdateField("GAMEOBJECT_PARENTROTATION"))
    {
        SetFloatValue(field + 0, 0);
        SetFloatValue(field + 1, 0);
        SetFloatValue(field + 2, 0);
        SetFloatValue(field + 3, 1);

        float multiplier = (rotation[0] * rotation[0]) + (rotation[1] * rotation[1]) + (rotation[2] * rotation[2]) + (rotation[3] * rotation[3]);
        multiplier = 1.0f / sqrtf(multiplier);
        m_packedLocalRotation = CompressQuaternion(rotation[0] * multiplier, rotation[1] * multiplier, rotation[2] * multiplier, rotation[3] * multiplier);
    }
}

void GameObject::SetState(uint8 state)
{
    if (uint16 GAMEOBJECT_STATE = sWorld.GetUpdateField("GAMEOBJECT_STATE"))
        SetUInt32Value(GAMEOBJECT_STATE, state);
    else if (uint16 GAMEOBJECT_BYTES_1 = sWorld.GetUpdateField("GAMEOBJECT_BYTES_1"))
        SetByteValue(GAMEOBJECT_BYTES_1, 0, state);
}

void GameObject::SetType(uint8 type)
{
    if (uint16 GAMEOBJECT_TYPE_ID = sWorld.GetUpdateField("GAMEOBJECT_TYPE_ID"))
        SetUInt32Value(GAMEOBJECT_TYPE_ID, type);
    else if (uint16 GAMEOBJECT_BYTES_1 = sWorld.GetUpdateField("GAMEOBJECT_BYTES_1"))
        SetByteValue(GAMEOBJECT_BYTES_1, 1, type);
}

void GameObject::SetArtKit(uint8 artKit)
{
    if (uint16 GAMEOBJECT_ARTKIT = sWorld.GetUpdateField("GAMEOBJECT_ARTKIT"))
        SetUInt32Value(GAMEOBJECT_ARTKIT, artKit);
    else if (uint16 GAMEOBJECT_BYTES_1 = sWorld.GetUpdateField("GAMEOBJECT_BYTES_1"))
        SetByteValue(GAMEOBJECT_BYTES_1, 2, artKit);
}

void GameObject::SetAnimProgress(uint8 animProgress)
{
    if (uint16 GAMEOBJECT_ANIMPROGRESS = sWorld.GetUpdateField("GAMEOBJECT_ANIMPROGRESS"))
        SetUInt32Value(GAMEOBJECT_ANIMPROGRESS, animProgress);
    else if (uint16 GAMEOBJECT_BYTES_1 = sWorld.GetUpdateField("GAMEOBJECT_BYTES_1"))
        SetByteValue(GAMEOBJECT_BYTES_1, 3, animProgress);
}

void GameObject::SetDynamicFlags(uint16 flags)
{
    if (uint16 GAMEOBJECT_DYN_FLAGS = sWorld.GetUpdateField("GAMEOBJECT_DYN_FLAGS"))
        SetUInt16Value(GAMEOBJECT_DYN_FLAGS, 0, flags);
    else if (uint16 GAMEOBJECT_DYNAMIC = sWorld.GetUpdateField("GAMEOBJECT_DYNAMIC"))
        SetUInt16Value(GAMEOBJECT_DYNAMIC, 0, flags);
}

void GameObject::SetPathProgress(uint16 pathProgress)
{
    SetUInt16Value("GAMEOBJECT_DYNAMIC", 1, pathProgress);
}
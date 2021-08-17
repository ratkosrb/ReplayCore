#ifndef __OBJECT_DEFINES_H
#define __OBJECT_DEFINES_H

#include "../Defines/Common.h"

enum TypeID
{
    TYPEID_OBJECT        = 0,
    TYPEID_ITEM          = 1,
    TYPEID_CONTAINER     = 2,
    TYPEID_UNIT          = 3,
    TYPEID_PLAYER        = 4,
    TYPEID_GAMEOBJECT    = 5,
    TYPEID_DYNAMICOBJECT = 6,
    TYPEID_CORPSE        = 7
};

#define MAX_TYPE_ID        8

enum TypeMask
{
    TYPEMASK_OBJECT         = 0x0001,
    TYPEMASK_ITEM           = 0x0002,
    TYPEMASK_CONTAINER      = 0x0004,
    TYPEMASK_UNIT           = 0x0008,                       // players also have it
    TYPEMASK_PLAYER         = 0x0010,
    TYPEMASK_GAMEOBJECT     = 0x0020,
    TYPEMASK_DYNAMICOBJECT  = 0x0040,
    TYPEMASK_CORPSE         = 0x0080,

    // used combinations in Player::GetObjectByTypeMask (TYPEMASK_UNIT case ignore players in call)
    TYPEMASK_CREATURE_OR_GAMEOBJECT = TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT,
    TYPEMASK_CREATURE_GAMEOBJECT_OR_ITEM = TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT | TYPEMASK_ITEM,
    TYPEMASK_CREATURE_GAMEOBJECT_PLAYER_OR_ITEM = TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT | TYPEMASK_ITEM | TYPEMASK_PLAYER,

    TYPEMASK_WORLDOBJECT = TYPEMASK_UNIT | TYPEMASK_PLAYER | TYPEMASK_GAMEOBJECT | TYPEMASK_DYNAMICOBJECT | TYPEMASK_CORPSE,
};

#define DEFAULT_VISIBILITY_DISTANCE 100.0f             // default visible distance on continents, used to be 90 yards
#define DEFAULT_VISIBILITY_INSTANCE 170.0f             // default visible distance in instances, used to be 120 yards
#define DEFAULT_VISIBILITY_BG       533.0f             // default visible distance in BG, used to be 180 yards
#define DEFAULT_VISIBILITY_MODIFIER 0.0f               // default visibility modifier on some units that should be seen beyond normal visibility distances
#define DEFAULT_CREATURE_SUMMON_LIMIT  100             // default maximum number of creatures an object can have summoned at once

#define VISIBILITY_DISTANCE_GIGANTIC    400.0f
#define VISIBILITY_DISTANCE_LARGE       200.0f
#define VISIBILITY_DISTANCE_NORMAL      100.0f
#define VISIBILITY_DISTANCE_SMALL       50.0f
#define VISIBILITY_DISTANCE_TINY        25.0f

#define DEFAULT_WORLD_OBJECT_SIZE   0.388999998569489f      // currently used (correctly?) for any non Unit world objects. This is actually the bounding_radius, like player/creature from creature_model_data
#define DEFAULT_OBJECT_SCALE        1.0f                    // player/item scale as default, npc/go from database, pets from dbc
#define DEFAULT_GNOME_SCALE         1.15f
#define DEFAULT_TAUREN_MALE_SCALE   1.35f                   // Tauren Male Player Scale by default
#define DEFAULT_TAUREN_FEMALE_SCALE 1.25f                   // Tauren Female Player Scale by default

struct Vector3
{
    Vector3() = default;
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    bool IsEmpty() const { return x == 0.0f && y == 0.0f && z == 0.0f; }
    inline Vector3 operator+ (const Vector3& rkVector) const
    {
        return Vector3(x + rkVector.x, y + rkVector.y, z + rkVector.z);
    }
    inline Vector3 operator- (const Vector3& rkVector) const
    {
        return Vector3(x - rkVector.x, y - rkVector.y, z - rkVector.z);
    }
    inline Vector3 operator* (const Vector3& rkVector) const
    {
        return Vector3(x * rkVector.x, y * rkVector.y, z * rkVector.z);
    }
    inline Vector3 operator*(float f) const
    {
        return Vector3(x * f, y * f, z * f);
    }
    inline Vector3 operator/ (float s) const
    {
        return *this * (1.0f / s);
    }
};
struct Position
{
    Position() = default;
    Position(float position_x, float position_y, float position_z, float orientation) : x(position_x), y(position_y), z(position_z), o(orientation) {}
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float o = 0.0f;
    bool operator!=(Position const& other) const
    {
        return !(x == other.x && y == other.y && z == other.z && o == other.o);
    }
    Vector3 ToVector3() const { return Vector3(x, y, z); }
};

struct WorldLocation : public Position
{
    uint16 mapId = 0;
    explicit WorldLocation(uint16 mapId_ = 0, float x_ = 0, float y_ = 0, float z_ = 0, float o_ = 0)
        : Position(x_, y_, z_, o_), mapId(mapId_) {}
    WorldLocation(WorldLocation const& loc)
        : Position(loc.x, loc.y, loc.z, loc.o), mapId(loc.mapId) {}
    Position ToPosition() const { return Position(x, y, z, o); }
};

#endif

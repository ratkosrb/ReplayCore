#ifndef __MOVEMENT_DEFINES_H
#define __MOVEMENT_DEFINES_H

#include "../Defines/Common.h"

enum SplineType
{
    SPLINE_TYPE_NORMAL        = 0,
    SPLINE_TYPE_STOP          = 1,
    SPLINE_TYPE_FACING_SPOT   = 2,
    SPLINE_TYPE_FACING_TARGET = 3,
    SPLINE_TYPE_FACING_ANGLE  = 4
};

namespace Vanilla
{
    enum MovementFlags
    {
        MOVEFLAG_NONE               = 0x00000000,
        MOVEFLAG_FORWARD            = 0x00000001,
        MOVEFLAG_BACKWARD           = 0x00000002,
        MOVEFLAG_STRAFE_LEFT        = 0x00000004,
        MOVEFLAG_STRAFE_RIGHT       = 0x00000008,
        MOVEFLAG_TURN_LEFT          = 0x00000010,
        MOVEFLAG_TURN_RIGHT         = 0x00000020,
        MOVEFLAG_PITCH_UP           = 0x00000040,
        MOVEFLAG_PITCH_DOWN         = 0x00000080,
        MOVEFLAG_WALK_MODE          = 0x00000100,               // Walking
        //MOVEFLAG_ONTRANSPORT        = 0x00000200, // ??
        MOVEFLAG_LEVITATING         = 0x00000400, // ?? Semble ne pas fonctionner
        MOVEFLAG_FIXED_Z            = 0x00000800, // Hauteur fixee. Sauter => Defiler sur toute la map
        MOVEFLAG_ROOT               = 0x00001000, // Fix Nostalrius
        MOVEFLAG_JUMPING            = 0x00002000,
        MOVEFLAG_FALLINGFAR         = 0x00004000,
        // Fin TC
        MOVEFLAG_SWIMMING           = 0x00200000, // Ok
        MOVEFLAG_SPLINE_ENABLED     = 0x00400000, // Ok
        // 0x00800000 = 'MOVEMENTFLAG_DESCENDING' pour TrinityCore
        MOVEFLAG_CAN_FLY            = 0x00800000,               // [-ZERO] is it really need and correct value
        MOVEFLAG_FLYING             = 0x01000000,               // [-ZERO] is it really need and correct value

        MOVEFLAG_ONTRANSPORT        = 0x02000000,               // Used for flying on some creatures
        MOVEFLAG_SPLINE_ELEVATION   = 0x04000000,               // used for flight paths

        MOVEFLAG_WATERWALKING       = 0x10000000,               // prevent unit from falling through water
        MOVEFLAG_SAFE_FALL          = 0x20000000,               // active rogue safe fall spell (passive)
        MOVEFLAG_HOVER              = 0x40000000,
        MOVEFLAG_INTERNAL           = 0x80000000,

        // Can not be present with MOVEFLAG_ROOT (otherwise client freeze)
        MOVEFLAG_MASK_RUNNING = MOVEFLAG_FORWARD | MOVEFLAG_BACKWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT,
        MOVEFLAG_MASK_MOVING =
            MOVEFLAG_FORWARD | MOVEFLAG_BACKWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT |
            MOVEFLAG_PITCH_UP | MOVEFLAG_PITCH_DOWN | MOVEFLAG_JUMPING | MOVEFLAG_FALLINGFAR |
            MOVEFLAG_SPLINE_ELEVATION,
        MOVEFLAG_MASK_TURNING = MOVEFLAG_TURN_LEFT | MOVEFLAG_TURN_RIGHT | MOVEFLAG_PITCH_UP | MOVEFLAG_PITCH_DOWN,
        MOVEFLAG_MASK_MOVING_OR_TURN = MOVEFLAG_MASK_MOVING | MOVEFLAG_TURN_LEFT | MOVEFLAG_TURN_RIGHT,

        // MovementFlags mask that only contains flags for x/z translations
        // this is to avoid that a jumping character that stands still triggers melee-leeway
        MOVEFLAG_MASK_XZ = MOVEFLAG_FORWARD | MOVEFLAG_BACKWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT
    };

    enum SplineFlags
    {
        None         = 0x00000000,
        Done         = 0x00000001,
        Falling      = 0x00000002,           // Affects elevation computation
        Unknown3     = 0x00000004,
        Unknown4     = 0x00000008,
        Unknown5     = 0x00000010,
        Unknown6     = 0x00000020,
        Unknown7     = 0x00000040,
        Unknown8     = 0x00000080,
        Runmode      = 0x00000100,
        Flying       = 0x00000200,           // Smooth movement(Catmullrom interpolation mode), flying animation
        No_Spline    = 0x00000400,
        Unknown12    = 0x00000800,
        Unknown13    = 0x00001000,
        Unknown14    = 0x00002000,
        Unknown15    = 0x00004000,
        Unknown16    = 0x00008000,
        Final_Point  = 0x00010000,
        Final_Target = 0x00020000,
        Final_Angle  = 0x00040000,
        Unknown19    = 0x00080000,           // exists, but unknown what it does
        Cyclic       = 0x00100000,           // Movement by cycled spline
        Enter_Cycle  = 0x00200000,           // Everytimes appears with cyclic flag in monster move packet, erases first spline vertex after first cycle done
        Frozen       = 0x00400000,           // Will never arrive
        Unknown23    = 0x00800000,
        Unknown24    = 0x01000000,
        Unknown25    = 0x02000000,          // exists, but unknown what it does
        Unknown26    = 0x04000000,
        Unknown27    = 0x08000000,
        Unknown28    = 0x10000000,
        Unknown29    = 0x20000000,
        Unknown30    = 0x40000000,
        Unknown31    = 0x80000000,

        // Masks
        Mask_Final_Facing = Final_Point | Final_Target | Final_Angle,
        // flags that shouldn't be appended into SMSG_MONSTER_MOVE\SMSG_MONSTER_MOVE_TRANSPORT packet, should be more probably
        Mask_No_Monster_Move = Mask_Final_Facing | Done,
        // CatmullRom interpolation mode used
        Mask_CatmullRom = Flying,
    };
}

namespace TBC
{
    enum MovementFlags
    {
        MOVEFLAG_NONE               = 0x00000000,
        MOVEFLAG_FORWARD            = 0x00000001,
        MOVEFLAG_BACKWARD           = 0x00000002,
        MOVEFLAG_STRAFE_LEFT        = 0x00000004,
        MOVEFLAG_STRAFE_RIGHT       = 0x00000008,
        MOVEFLAG_TURN_LEFT          = 0x00000010,
        MOVEFLAG_TURN_RIGHT         = 0x00000020,
        MOVEFLAG_PITCH_UP           = 0x00000040,
        MOVEFLAG_PITCH_DOWN         = 0x00000080,
        MOVEFLAG_WALK_MODE          = 0x00000100,               // Walking
        MOVEFLAG_ONTRANSPORT        = 0x00000200,               // Used for flying on some creatures
        MOVEFLAG_LEVITATING         = 0x00000400,
        MOVEFLAG_ROOT               = 0x00000800,
        MOVEFLAG_FALLING            = 0x00001000,
        MOVEFLAG_JUMPING            = 0x00002000,   // XXX CHECK THIS!
        MOVEFLAG_FALLINGFAR         = 0x00004000,
        MOVEFLAG_SWIMMING           = 0x00200000,               // appears with fly flag also
        MOVEFLAG_ASCENDING          = 0x00400000,               // swim up also
        MOVEFLAG_CAN_FLY            = 0x00800000,
        MOVEFLAG_FLYING             = 0x01000000,
        MOVEFLAG_FLYING2            = 0x02000000,               // Actual flying mode
        MOVEFLAG_SPLINE_ELEVATION   = 0x04000000,               // used for flight paths
        MOVEFLAG_SPLINE_ENABLED     = 0x08000000,               // used for flight paths
        MOVEFLAG_WATERWALKING       = 0x10000000,               // prevent unit from falling through water
        MOVEFLAG_SAFE_FALL          = 0x20000000,               // active rogue safe fall spell (passive)
        MOVEFLAG_HOVER              = 0x40000000,

        // Can not be present with MOVEFLAG_ROOT (otherwise client freeze)
        MOVEFLAG_MASK_MOVING        =
            MOVEFLAG_FORWARD | MOVEFLAG_BACKWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT |
            MOVEFLAG_PITCH_UP | MOVEFLAG_PITCH_DOWN | MOVEFLAG_JUMPING | MOVEFLAG_FALLINGFAR |
            MOVEFLAG_SPLINE_ELEVATION,
        MOVEFLAG_MASK_MOVING_OR_TURN = MOVEFLAG_MASK_MOVING | MOVEFLAG_TURN_LEFT | MOVEFLAG_TURN_RIGHT,
        MOVEFLAG_MASK_MOVING_FORWARD = MOVEFLAG_FORWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT | MOVEFLAG_FALLING,
        MOVEFLAG_MASK_XY = MOVEFLAG_FORWARD | MOVEFLAG_BACKWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT
    };

    enum SplineFlags
    {
        None         = 0x00000000,
        Done         = 0x00000001,
        Falling      = 0x00000002,           // Affects elevation computation
        Unknown3     = 0x00000004,
        Unknown4     = 0x00000008,
        Unknown5     = 0x00000010,
        Unknown6     = 0x00000020,
        Unknown7     = 0x00000040,
        Unknown8     = 0x00000080,
        Runmode      = 0x00000100,
        Flying       = 0x00000200,           // Smooth movement(Catmullrom interpolation mode), flying animation
        No_Spline    = 0x00000400,
        Unknown12    = 0x00000800,
        Unknown13    = 0x00001000,
        Unknown14    = 0x00002000,
        Unknown15    = 0x00004000,
        Unknown16    = 0x00008000,
        Final_Point  = 0x00010000,
        Final_Target = 0x00020000,
        Final_Angle  = 0x00040000,
        Unknown19    = 0x00080000,           // exists, but unknown what it does
        Cyclic       = 0x00100000,           // Movement by cycled spline
        Enter_Cycle  = 0x00200000,           // Everytimes appears with cyclic flag in monster move packet, erases first spline vertex after first cycle done
        Frozen       = 0x00400000,           // Will never arrive
        Unknown23    = 0x00800000,
        Unknown24    = 0x01000000,
        Unknown25    = 0x02000000,          // exists, but unknown what it does
        Unknown26    = 0x04000000,
        Unknown27    = 0x08000000,
        Unknown28    = 0x10000000,
        Unknown29    = 0x20000000,
        Unknown30    = 0x40000000,
        Unknown31    = 0x80000000,

        // Masks
        Mask_Final_Facing = Final_Point | Final_Target | Final_Angle,
        // flags that shouldn't be appended into SMSG_MONSTER_MOVE\SMSG_MONSTER_MOVE_TRANSPORT packet, should be more probably
        Mask_No_Monster_Move = Mask_Final_Facing | Done,
        // CatmullRom interpolation mode used
        Mask_CatmullRom = Flying,
    };
}

namespace WotLK
{
    enum MovementFlags
    {
        MOVEFLAG_NONE               = 0x00000000,
        MOVEFLAG_FORWARD            = 0x00000001,
        MOVEFLAG_BACKWARD           = 0x00000002,
        MOVEFLAG_STRAFE_LEFT        = 0x00000004,
        MOVEFLAG_STRAFE_RIGHT       = 0x00000008,
        MOVEFLAG_TURN_LEFT          = 0x00000010,
        MOVEFLAG_TURN_RIGHT         = 0x00000020,
        MOVEFLAG_PITCH_UP           = 0x00000040,
        MOVEFLAG_PITCH_DOWN         = 0x00000080,
        MOVEFLAG_WALK_MODE          = 0x00000100,               // Walking
        MOVEFLAG_ONTRANSPORT        = 0x00000200,
        MOVEFLAG_LEVITATING         = 0x00000400,
        MOVEFLAG_ROOT               = 0x00000800,
        MOVEFLAG_FALLING            = 0x00001000,
        MOVEFLAG_FALLINGFAR         = 0x00002000,
        MOVEFLAG_PENDINGSTOP        = 0x00004000,
        MOVEFLAG_PENDINGSTRAFESTOP  = 0x00008000,
        MOVEFLAG_PENDINGFORWARD     = 0x00010000,
        MOVEFLAG_PENDINGBACKWARD    = 0x00020000,
        MOVEFLAG_PENDINGSTRAFELEFT  = 0x00040000,
        MOVEFLAG_PENDINGSTRAFERIGHT = 0x00080000,
        MOVEFLAG_PENDINGROOT        = 0x00100000,
        MOVEFLAG_SWIMMING           = 0x00200000,               // appears with fly flag also
        MOVEFLAG_ASCENDING          = 0x00400000,               // swim up also
        MOVEFLAG_DESCENDING         = 0x00800000,               // swim down also
        MOVEFLAG_CAN_FLY            = 0x01000000,               // can fly in 3.3?
        MOVEFLAG_FLYING             = 0x02000000,               // Actual flying mode
        MOVEFLAG_SPLINE_ELEVATION   = 0x04000000,               // used for flight paths
        MOVEFLAG_SPLINE_ENABLED     = 0x08000000,               // used for flight paths
        MOVEFLAG_WATERWALKING       = 0x10000000,               // prevent unit from falling through water
        MOVEFLAG_SAFE_FALL          = 0x20000000,               // active rogue safe fall spell (passive)
        MOVEFLAG_HOVER              = 0x40000000,

        MOVEFLAG_MASK_MOVING =
        MOVEFLAG_FORWARD | MOVEFLAG_BACKWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT |
        MOVEFLAG_PITCH_UP | MOVEFLAG_PITCH_DOWN | MOVEFLAG_FALLING | MOVEFLAG_FALLINGFAR |
        MOVEFLAG_SPLINE_ELEVATION,
        MOVEFLAG_MASK_MOVING_OR_TURN = MOVEFLAG_MASK_MOVING | MOVEFLAG_TURN_LEFT | MOVEFLAG_TURN_RIGHT,
        MOVEFLAG_MASK_MOVING_FORWARD = MOVEFLAG_FORWARD | MOVEFLAG_STRAFE_LEFT | MOVEFLAG_STRAFE_RIGHT | MOVEFLAG_FALLING,
    };

    enum MovementFlags2
    {
        MOVEFLAG2_NONE              = 0x0000,
        MOVEFLAG2_NO_STRAFE         = 0x0001,
        MOVEFLAG2_NO_JUMPING        = 0x0002,
        MOVEFLAG2_UNK3              = 0x0004,
        MOVEFLAG2_FULLSPEEDTURNING  = 0x0008,
        MOVEFLAG2_FULLSPEEDPITCHING = 0x0010,
        MOVEFLAG2_ALLOW_PITCHING    = 0x0020,
        MOVEFLAG2_UNK4              = 0x0040,
        MOVEFLAG2_UNK5              = 0x0080,
        MOVEFLAG2_UNK6              = 0x0100,                   // transport related
        MOVEFLAG2_UNK7              = 0x0200,
        MOVEFLAG2_INTERP_MOVEMENT   = 0x0400,
        MOVEFLAG2_INTERP_TURNING    = 0x0800,
        MOVEFLAG2_INTERP_PITCHING   = 0x1000,
        MOVEFLAG2_UNK8              = 0x2000,
        MOVEFLAG2_UNK9              = 0x4000,
        MOVEFLAG2_UNK10             = 0x8000,
        MOVEFLAG2_INTERP_MASK       = MOVEFLAG2_INTERP_MOVEMENT | MOVEFLAG2_INTERP_TURNING | MOVEFLAG2_INTERP_PITCHING
    };

    enum SplineFlags
    {
        None         = 0x00000000,
        // x00-xFF(first byte) used as animation Ids storage in pair with Animation flag
        Done         = 0x00000100,
        Falling      = 0x00000200,           // Affects elevation computation, can't be combined with Parabolic flag
        No_Spline    = 0x00000400,
        Parabolic    = 0x00000800,           // Affects elevation computation, can't be combined with Falling flag
        Walkmode     = 0x00001000,
        Flying       = 0x00002000,           // Smooth movement(Catmullrom interpolation mode), flying animation
        OrientationFixed = 0x00004000,       // Model orientation fixed
        Final_Point  = 0x00008000,
        Final_Target = 0x00010000,
        Final_Angle  = 0x00020000,
        Catmullrom   = 0x00040000,           // Used Catmullrom interpolation mode
        Cyclic       = 0x00080000,           // Movement by cycled spline
        Enter_Cycle  = 0x00100000,           // Everytimes appears with cyclic flag in monster move packet, erases first spline vertex after first cycle done
        Animation    = 0x00200000,           // Plays animation after some time passed
        Frozen       = 0x00400000,           // Will never arrive
        BoardVehicle = 0x00800000,
        ExitVehicle  = 0x01000000,
        Unknown7     = 0x02000000,
        Unknown8     = 0x04000000,
        OrientationInversed = 0x08000000,
        Unknown10    = 0x10000000,
        Unknown11    = 0x20000000,
        Unknown12    = 0x40000000,
        Unknown13    = 0x80000000,

        // Masks
        Mask_Final_Facing = Final_Point | Final_Target | Final_Angle,
        // animation ids stored here, see AnimType enum, used with Animation flag
        Mask_Animations = 0xFF,
        // flags that shouldn't be appended into SMSG_MONSTER_MOVE\SMSG_MONSTER_MOVE_TRANSPORT packet, should be more probably
        Mask_No_Monster_Move = Mask_Final_Facing | Mask_Animations | Done,
        // CatmullRom interpolation mode used
        Mask_CatmullRom = Flying | Catmullrom,
        // Unused, not suported flags
        Mask_Unused = No_Spline | Enter_Cycle | Frozen | Unknown7 | Unknown8 | Unknown10 | Unknown11 | Unknown12 | Unknown13,
    };
}

namespace Classic
{
    enum MovementFlags
    {
        MOVEFLAG_NONE               = 0x00000000,
        MOVEFLAG_FORWARD            = 0x00000001,
        MOVEFLAG_BACKWARD           = 0x00000002,
        MOVEFLAG_STRAFE_LEFT        = 0x00000004,
        MOVEFLAG_STRAFE_RIGHT       = 0x00000008,
        MOVEFLAG_TURN_LEFT          = 0x00000010,
        MOVEFLAG_TURN_RIGHT         = 0x00000020,
        MOVEFLAG_PITCH_UP           = 0x00000040,
        MOVEFLAG_PITCH_DOWN         = 0x00000080,
        MOVEFLAG_WALK_MODE          = 0x00000100,
        MOVEFLAG_DISABLE_GRAVITY    = 0x00000200,
        MOVEFLAG_ROOT               = 0x00000400,
        MOVEFLAG_FALLING            = 0x00000800,
        MOVEFLAG_FALLINGFAR         = 0x00001000,
        MOVEFLAG_PENDINGSTOP        = 0x00002000,
        MOVEFLAG_PENDINGSTRAFESTOP  = 0x00004000,
        MOVEFLAG_PENDINGFORWARD     = 0x00008000,
        MOVEFLAG_PENDINGBACKWARD    = 0x00010000,
        MOVEFLAG_PENDINGSTRAFELEFT  = 0x00020000,
        MOVEFLAG_PENDINGSTRAFERIGHT = 0x00040000,
        MOVEFLAG_PENDINGROOT        = 0x00080000,
        MOVEFLAG_SWIMMING           = 0x00100000,
        MOVEFLAG_ASCENDING          = 0x00200000,
        MOVEFLAG_DESCENDING         = 0x00400000,
        MOVEFLAG_CAN_FLY            = 0x00800000,
        MOVEFLAG_FLYING             = 0x01000000,
        MOVEFLAG_SPLINE_ELEVATION   = 0x02000000,
        MOVEFLAG_WATERWALKING       = 0x04000000,
        MOVEFLAG_SAFE_FALL          = 0x08000000,
        MOVEFLAG_HOVER              = 0x10000000,
        MOVEFLAG_DISABLE_COLLISION  = 0x20000000,
    };

    enum SplineFlags
    {
        None = 0x00000000,
        AnimTierSwim = 0x00000001,
        AnimTierHover = 0x00000002,
        AnimTierFly = 0x00000003,
        AnimTierSubmerged = 0x00000004,
        Unknown0 = 0x00000008,
        FallingSlow = 0x00000010,
        Done = 0x00000020,
        Falling = 0x00000040,
        NoSpline = 0x00000080,
        Unknown1 = 0x00000100,
        Flying = 0x00000200,
        OrientationFixed = 0x00000400,
        Catmullrom = 0x00000800,
        Cyclic = 0x00001000,
        EnterCycle = 0x00002000,
        Frozen = 0x00004000,
        TransportEnter = 0x00008000,
        TransportExit = 0x00010000,
        Unknown2 = 0x00020000,
        Unknown3 = 0x00040000,
        Backward = 0x00080000,
        SmoothGroundPath = 0x00100000,
        CanSwim = 0x00200000,
        UncompressedPath = 0x00400000,
        Unknown4 = 0x00800000,
        Unknown5 = 0x01000000,
        Animation = 0x02000000,
        Parabolic = 0x04000000,
        FadeObject = 0x08000000,
        Steering = 0x10000000,
        Unknown8 = 0x20000000,
        Unknown9 = 0x40000000,
        Unknown10 = 0x80000000,
    };
}

#endif
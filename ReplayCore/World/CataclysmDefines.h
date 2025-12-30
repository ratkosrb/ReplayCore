/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MANGOS_H_CATACLYSMDEFINES
#define MANGOS_H_CATACLYSMDEFINES

#include "../Defines/Common.h"
#include "UnitDefines.h"
#include "MovementDefines.h"
#include "ChatDefines.h"
#include "SpellDefines.h"
#include <string>

inline uint32 ConvertCataclysmMovementFlagsToVanilla(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Cataclysm::MOVEFLAG_FORWARD)
        newFlags |= Vanilla::MOVEFLAG_FORWARD;
    if (flags & Cataclysm::MOVEFLAG_BACKWARD)
        newFlags |= Vanilla::MOVEFLAG_BACKWARD;
    if (flags & Cataclysm::MOVEFLAG_STRAFE_LEFT)
        newFlags |= Vanilla::MOVEFLAG_STRAFE_LEFT;
    if (flags & Cataclysm::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= Vanilla::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Cataclysm::MOVEFLAG_TURN_LEFT)
        newFlags |= Vanilla::MOVEFLAG_TURN_LEFT;
    if (flags & Cataclysm::MOVEFLAG_TURN_RIGHT)
        newFlags |= Vanilla::MOVEFLAG_TURN_RIGHT;
    if (flags & Cataclysm::MOVEFLAG_PITCH_UP)
        newFlags |= Vanilla::MOVEFLAG_PITCH_UP;
    if (flags & Cataclysm::MOVEFLAG_PITCH_DOWN)
        newFlags |= Vanilla::MOVEFLAG_PITCH_DOWN;
    if (flags & Cataclysm::MOVEFLAG_WALK_MODE)
        newFlags |= Vanilla::MOVEFLAG_WALK_MODE;
    if (flags & Cataclysm::MOVEFLAG_ROOT)
        newFlags |= Vanilla::MOVEFLAG_ROOT;
    if (flags & Cataclysm::MOVEFLAG_FALLING)
        newFlags |= Vanilla::MOVEFLAG_JUMPING;
    if (flags & Cataclysm::MOVEFLAG_FALLINGFAR)
        newFlags |= Vanilla::MOVEFLAG_FALLINGFAR;
    if (flags & Cataclysm::MOVEFLAG_SWIMMING)
        newFlags |= Vanilla::MOVEFLAG_SWIMMING;
    if (flags & Cataclysm::MOVEFLAG_CAN_FLY)
        newFlags |= Vanilla::MOVEFLAG_CAN_FLY;
    if (flags & Cataclysm::MOVEFLAG_FLYING)
        newFlags |= Vanilla::MOVEFLAG_FLYING;
    if (flags & Cataclysm::MOVEFLAG_WATERWALKING)
        newFlags |= Vanilla::MOVEFLAG_WATERWALKING;
    if (flags & Cataclysm::MOVEFLAG_SAFE_FALL)
        newFlags |= Vanilla::MOVEFLAG_SAFE_FALL;
    if (flags & Cataclysm::MOVEFLAG_HOVER)
        newFlags |= Vanilla::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertCataclysmMovementFlagsToTBC(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Cataclysm::MOVEFLAG_FORWARD)
        newFlags |= TBC::MOVEFLAG_FORWARD;
    if (flags & Cataclysm::MOVEFLAG_BACKWARD)
        newFlags |= TBC::MOVEFLAG_BACKWARD;
    if (flags & Cataclysm::MOVEFLAG_STRAFE_LEFT)
        newFlags |= TBC::MOVEFLAG_STRAFE_LEFT;
    if (flags & Cataclysm::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= TBC::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Cataclysm::MOVEFLAG_TURN_LEFT)
        newFlags |= TBC::MOVEFLAG_TURN_LEFT;
    if (flags & Cataclysm::MOVEFLAG_TURN_RIGHT)
        newFlags |= TBC::MOVEFLAG_TURN_RIGHT;
    if (flags & Cataclysm::MOVEFLAG_PITCH_UP)
        newFlags |= TBC::MOVEFLAG_PITCH_UP;
    if (flags & Cataclysm::MOVEFLAG_PITCH_DOWN)
        newFlags |= TBC::MOVEFLAG_PITCH_DOWN;
    if (flags & Cataclysm::MOVEFLAG_WALK_MODE)
        newFlags |= TBC::MOVEFLAG_WALK_MODE;
    if (flags & Cataclysm::MOVEFLAG_ROOT)
        newFlags |= TBC::MOVEFLAG_ROOT;
    if (flags & Cataclysm::MOVEFLAG_FALLING)
        newFlags |= TBC::MOVEFLAG_JUMPING;
    if (flags & Cataclysm::MOVEFLAG_FALLINGFAR)
        newFlags |= TBC::MOVEFLAG_FALLINGFAR;
    if (flags & Cataclysm::MOVEFLAG_SWIMMING)
        newFlags |= TBC::MOVEFLAG_SWIMMING;
    if (flags & Cataclysm::MOVEFLAG_ASCENDING)
        newFlags |= TBC::MOVEFLAG_ASCENDING;
    if (flags & Cataclysm::MOVEFLAG_CAN_FLY)
        newFlags |= TBC::MOVEFLAG_CAN_FLY;
    if (flags & Cataclysm::MOVEFLAG_FLYING)
        newFlags |= TBC::MOVEFLAG_FLYING;
    if (flags & Cataclysm::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= TBC::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & Cataclysm::MOVEFLAG_WATERWALKING)
        newFlags |= TBC::MOVEFLAG_WATERWALKING;
    if (flags & Cataclysm::MOVEFLAG_SAFE_FALL)
        newFlags |= TBC::MOVEFLAG_SAFE_FALL;
    if (flags & Cataclysm::MOVEFLAG_HOVER)
        newFlags |= TBC::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertCataclysmMovementFlagsToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Cataclysm::MOVEFLAG_FORWARD)
        newFlags |= WotLK::MOVEFLAG_FORWARD;
    if (flags & Cataclysm::MOVEFLAG_BACKWARD)
        newFlags |= WotLK::MOVEFLAG_BACKWARD;
    if (flags & Cataclysm::MOVEFLAG_STRAFE_LEFT)
        newFlags |= WotLK::MOVEFLAG_STRAFE_LEFT;
    if (flags & Cataclysm::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= WotLK::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Cataclysm::MOVEFLAG_TURN_LEFT)
        newFlags |= WotLK::MOVEFLAG_TURN_LEFT;
    if (flags & Cataclysm::MOVEFLAG_TURN_RIGHT)
        newFlags |= WotLK::MOVEFLAG_TURN_RIGHT;
    if (flags & Cataclysm::MOVEFLAG_PITCH_UP)
        newFlags |= WotLK::MOVEFLAG_PITCH_UP;
    if (flags & Cataclysm::MOVEFLAG_PITCH_DOWN)
        newFlags |= WotLK::MOVEFLAG_PITCH_DOWN;
    if (flags & Cataclysm::MOVEFLAG_WALK_MODE)
        newFlags |= WotLK::MOVEFLAG_WALK_MODE;
    if (flags & Cataclysm::MOVEFLAG_DISABLE_GRAVITY)
        newFlags |= WotLK::MOVEFLAG_LEVITATING;
    if (flags & Cataclysm::MOVEFLAG_ROOT)
        newFlags |= WotLK::MOVEFLAG_ROOT;
    if (flags & Cataclysm::MOVEFLAG_FALLING)
        newFlags |= WotLK::MOVEFLAG_FALLING;
    if (flags & Cataclysm::MOVEFLAG_FALLINGFAR)
        newFlags |= WotLK::MOVEFLAG_FALLINGFAR;
    if (flags & Cataclysm::MOVEFLAG_PENDINGSTOP)
        newFlags |= WotLK::MOVEFLAG_PENDINGSTOP;
    if (flags & Cataclysm::MOVEFLAG_PENDINGSTRAFESTOP)
        newFlags |= WotLK::MOVEFLAG_PENDINGSTRAFESTOP;
    if (flags & Cataclysm::MOVEFLAG_PENDINGFORWARD)
        newFlags |= WotLK::MOVEFLAG_PENDINGFORWARD;
    if (flags & Cataclysm::MOVEFLAG_PENDINGBACKWARD)
        newFlags |= WotLK::MOVEFLAG_PENDINGBACKWARD;
    if (flags & Cataclysm::MOVEFLAG_PENDINGSTRAFELEFT)
        newFlags |= WotLK::MOVEFLAG_PENDINGSTRAFELEFT;
    if (flags & Cataclysm::MOVEFLAG_PENDINGSTRAFERIGHT)
        newFlags |= WotLK::MOVEFLAG_PENDINGSTRAFERIGHT;
    if (flags & Cataclysm::MOVEFLAG_PENDINGROOT)
        newFlags |= WotLK::MOVEFLAG_PENDINGROOT;
    if (flags & Cataclysm::MOVEFLAG_SWIMMING)
        newFlags |= WotLK::MOVEFLAG_SWIMMING;
    if (flags & Cataclysm::MOVEFLAG_ASCENDING)
        newFlags |= WotLK::MOVEFLAG_ASCENDING;
    if (flags & Cataclysm::MOVEFLAG_DESCENDING)
        newFlags |= WotLK::MOVEFLAG_DESCENDING;
    if (flags & Cataclysm::MOVEFLAG_CAN_FLY)
        newFlags |= WotLK::MOVEFLAG_CAN_FLY;
    if (flags & Cataclysm::MOVEFLAG_FLYING)
        newFlags |= WotLK::MOVEFLAG_FLYING;
    if (flags & Cataclysm::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= WotLK::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & Cataclysm::MOVEFLAG_WATERWALKING)
        newFlags |= WotLK::MOVEFLAG_WATERWALKING;
    if (flags & Cataclysm::MOVEFLAG_SAFE_FALL)
        newFlags |= WotLK::MOVEFLAG_SAFE_FALL;
    if (flags & Cataclysm::MOVEFLAG_HOVER)
        newFlags |= WotLK::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertCataclysmMovementFlags2ToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Cataclysm::MOVEFLAG2_NO_STRAFE)
        newFlags |= WotLK::MOVEFLAG2_NO_STRAFE;
    if (flags & Cataclysm::MOVEFLAG2_NO_JUMPING)
        newFlags |= WotLK::MOVEFLAG2_NO_JUMPING;
    if (flags & Cataclysm::MOVEFLAG2_FULL_SPEED_TURNING)
        newFlags |= WotLK::MOVEFLAG2_FULL_SPEED_TURNING;
    if (flags & Cataclysm::MOVEFLAG2_FULL_SPEED_PITCHING)
        newFlags |= WotLK::MOVEFLAG2_FULL_SPEED_PITCHING;
    if (flags & Cataclysm::MOVEFLAG2_ALWAYS_ALLOW_PITCHING)
        newFlags |= WotLK::MOVEFLAG2_ALWAYS_ALLOW_PITCHING;
    if (flags & Cataclysm::MOVEFLAG2_INTERPOLATED_MOVEMENT)
        newFlags |= WotLK::MOVEFLAG2_INTERPOLATED_MOVEMENT;
    if (flags & Cataclysm::MOVEFLAG2_INTERPOLATED_TURNING)
        newFlags |= WotLK::MOVEFLAG2_INTERPOLATED_TURNING;
    if (flags & Cataclysm::MOVEFLAG2_INTERPOLATED_PITCHING)
        newFlags |= WotLK::MOVEFLAG2_INTERPOLATED_PITCHING;

    return newFlags;
}

#endif
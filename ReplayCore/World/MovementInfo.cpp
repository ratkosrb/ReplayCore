#include "MovementInfo.h"
#include "MovementDefines.h"
#include "WorldServer.h"
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
            data >> jump.zspeed;
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
        data >> moveFlags2TBC;
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
            data >> jump.zspeed;
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
        data >> moveFlags2WotLK;
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

            if (moveFlags2WotLK & WotLK::MOVEFLAG2_INTERP_MOVEMENT)
            {
                data >> t_time2;
            }
        }

        if ((HasMovementFlag(WotLK::MOVEFLAG_SWIMMING | WotLK::MOVEFLAG_FLYING)) || (moveFlags2WotLK & WotLK::MOVEFLAG2_ALLOW_PITCHING))
        {
            data >> s_pitch;
        }

        data >> fallTime;

        if (HasMovementFlag(WotLK::MOVEFLAG_FALLING))
        {
            data >> jump.zspeed;
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
            data << jump.zspeed;
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
        data << moveFlags2TBC;
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
            data << jump.zspeed;
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
        data << moveFlags2WotLK;
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

            if (moveFlags2WotLK & WotLK::MOVEFLAG2_INTERP_MOVEMENT)
            {
                data << t_time2;
            }
        }

        if ((HasMovementFlag(WotLK::MOVEFLAG_SWIMMING | WotLK::MOVEFLAG_FLYING)) || (moveFlags2WotLK & WotLK::MOVEFLAG2_ALLOW_PITCHING))
        {
            data << s_pitch;
        }

        data << fallTime;

        if (HasMovementFlag(WotLK::MOVEFLAG_FALLING))
        {
            data << jump.zspeed;
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
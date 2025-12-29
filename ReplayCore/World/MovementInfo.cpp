#include "MovementInfo.h"
#include "MovementDefines.h"
#include "WorldServer.h"
#include "../Defines/ClientVersions.h"

void MovementInfo::Read(ByteBuffer &data)
{
    if (sWorld.GetClientBuild() > CLIENT_BUILD_3_3_5a)
    {
        printf("[ERROR] MovementInfo::Read called for unsupported client version.");
        while (true) {};
    }

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
        }

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

            if (moveFlags2WotLK & WotLK::MOVEFLAG2_INTERPOLATED_MOVEMENT)
            {
                data >> t_time2;
            }
        }

        if ((HasMovementFlag(WotLK::MOVEFLAG_SWIMMING | WotLK::MOVEFLAG_FLYING)) || (moveFlags2WotLK & WotLK::MOVEFLAG2_ALWAYS_ALLOW_PITCHING))
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

void MovementInfo::CorrectData()
{
#define REMOVE_VIOLATING_FLAGS(check, maskToRemove) \
        if (check) \
            RemoveMovementFlag(maskToRemove);

    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        /*! This must be a packet spoofing attempt. MOVEFLAG_ROOT sent from the client is not valid
        in conjunction with any of the moving movement flags such as MOVEMENTFLAG_FORWARD.
        It will freeze clients that receive this player's movement info.
        */
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Vanilla::MOVEFLAG_ROOT) && HasMovementFlag(Vanilla::MOVEFLAG_MASK_MOVING),
            Vanilla::MOVEFLAG_ROOT);

        //! Cannot move left and right at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Vanilla::MOVEFLAG_TURN_LEFT) && HasMovementFlag(Vanilla::MOVEFLAG_TURN_RIGHT),
            Vanilla::MOVEFLAG_TURN_LEFT | Vanilla::MOVEFLAG_TURN_RIGHT);

        //! Cannot strafe left and right at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Vanilla::MOVEFLAG_STRAFE_LEFT) && HasMovementFlag(Vanilla::MOVEFLAG_STRAFE_RIGHT),
            Vanilla::MOVEFLAG_STRAFE_LEFT | Vanilla::MOVEFLAG_STRAFE_RIGHT);

        //! Cannot pitch up and down at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Vanilla::MOVEFLAG_PITCH_UP) && HasMovementFlag(Vanilla::MOVEFLAG_PITCH_DOWN),
            Vanilla::MOVEFLAG_PITCH_UP | Vanilla::MOVEFLAG_PITCH_DOWN);

        //! Cannot move forwards and backwards at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Vanilla::MOVEFLAG_FORWARD) && HasMovementFlag(Vanilla::MOVEFLAG_BACKWARD),
            Vanilla::MOVEFLAG_FORWARD | Vanilla::MOVEFLAG_BACKWARD);
    }
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        /*! This must be a packet spoofing attempt. MOVEFLAG_ROOT sent from the client is not valid
        in conjunction with any of the moving movement flags such as MOVEMENTFLAG_FORWARD.
        It will freeze clients that receive this player's movement info.
        */
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(TBC::MOVEFLAG_ROOT) && HasMovementFlag(TBC::MOVEFLAG_MASK_MOVING),
            TBC::MOVEFLAG_ROOT);

        //! Cannot move left and right at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(TBC::MOVEFLAG_TURN_LEFT) && HasMovementFlag(TBC::MOVEFLAG_TURN_RIGHT),
            TBC::MOVEFLAG_TURN_LEFT | TBC::MOVEFLAG_TURN_RIGHT);

        //! Cannot strafe left and right at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(TBC::MOVEFLAG_STRAFE_LEFT) && HasMovementFlag(TBC::MOVEFLAG_STRAFE_RIGHT),
            TBC::MOVEFLAG_STRAFE_LEFT | TBC::MOVEFLAG_STRAFE_RIGHT);

        //! Cannot pitch up and down at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(TBC::MOVEFLAG_PITCH_UP) && HasMovementFlag(TBC::MOVEFLAG_PITCH_DOWN),
            TBC::MOVEFLAG_PITCH_UP | TBC::MOVEFLAG_PITCH_DOWN);

        //! Cannot move forwards and backwards at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(TBC::MOVEFLAG_FORWARD) && HasMovementFlag(TBC::MOVEFLAG_BACKWARD),
            TBC::MOVEFLAG_FORWARD | TBC::MOVEFLAG_BACKWARD);
    }
    else if (sWorld.GetClientBuild() <= CLIENT_BUILD_3_3_5a)
    {
        /*! This must be a packet spoofing attempt. MOVEFLAG_ROOT sent from the client is not valid
        in conjunction with any of the moving movement flags such as MOVEMENTFLAG_FORWARD.
        It will freeze clients that receive this player's movement info.
        */
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(WotLK::MOVEFLAG_ROOT) && HasMovementFlag(WotLK::MOVEFLAG_MASK_MOVING),
            WotLK::MOVEFLAG_ROOT);

        //! Cannot move left and right at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(WotLK::MOVEFLAG_TURN_LEFT) && HasMovementFlag(WotLK::MOVEFLAG_TURN_RIGHT),
            WotLK::MOVEFLAG_TURN_LEFT | WotLK::MOVEFLAG_TURN_RIGHT);

        //! Cannot strafe left and right at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(WotLK::MOVEFLAG_STRAFE_LEFT) && HasMovementFlag(WotLK::MOVEFLAG_STRAFE_RIGHT),
            WotLK::MOVEFLAG_STRAFE_LEFT | WotLK::MOVEFLAG_STRAFE_RIGHT);

        //! Cannot pitch up and down at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(WotLK::MOVEFLAG_PITCH_UP) && HasMovementFlag(WotLK::MOVEFLAG_PITCH_DOWN),
            WotLK::MOVEFLAG_PITCH_UP | WotLK::MOVEFLAG_PITCH_DOWN);

        //! Cannot move forwards and backwards at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(WotLK::MOVEFLAG_FORWARD) && HasMovementFlag(WotLK::MOVEFLAG_BACKWARD),
            WotLK::MOVEFLAG_FORWARD | WotLK::MOVEFLAG_BACKWARD);
    }
    else
    {
        /*! This must be a packet spoofing attempt. MOVEFLAG_ROOT sent from the client is not valid
        in conjunction with any of the moving movement flags such as MOVEMENTFLAG_FORWARD.
        It will freeze clients that receive this player's movement info.
        */
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Cataclysm::MOVEFLAG_ROOT) && HasMovementFlag(Cataclysm::MOVEFLAG_MASK_MOVING),
            Cataclysm::MOVEFLAG_ROOT);

        //! Cannot move left and right at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Cataclysm::MOVEFLAG_TURN_LEFT) && HasMovementFlag(Cataclysm::MOVEFLAG_TURN_RIGHT),
            Cataclysm::MOVEFLAG_TURN_LEFT | Cataclysm::MOVEFLAG_TURN_RIGHT);

        //! Cannot strafe left and right at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Cataclysm::MOVEFLAG_STRAFE_LEFT) && HasMovementFlag(Cataclysm::MOVEFLAG_STRAFE_RIGHT),
            Cataclysm::MOVEFLAG_STRAFE_LEFT | Cataclysm::MOVEFLAG_STRAFE_RIGHT);

        //! Cannot pitch up and down at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Cataclysm::MOVEFLAG_PITCH_UP) && HasMovementFlag(Cataclysm::MOVEFLAG_PITCH_DOWN),
            Cataclysm::MOVEFLAG_PITCH_UP | Cataclysm::MOVEFLAG_PITCH_DOWN);

        //! Cannot move forwards and backwards at the same time
        REMOVE_VIOLATING_FLAGS(HasMovementFlag(Cataclysm::MOVEFLAG_FORWARD) && HasMovementFlag(Cataclysm::MOVEFLAG_BACKWARD),
            Cataclysm::MOVEFLAG_FORWARD | Cataclysm::MOVEFLAG_BACKWARD);
    }
#undef REMOVE_VIOLATING_FLAGS
}

void MovementInfo::Write(ByteBuffer &data) const
{
    if (sWorld.GetClientBuild() > CLIENT_BUILD_3_3_5a)
    {
        printf("[ERROR] MovementInfo::Write called for unsupported client version.");
        while (true) {};
    }

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

            if (moveFlags2WotLK & WotLK::MOVEFLAG2_INTERPOLATED_MOVEMENT)
            {
                data << t_time2;
            }
        }

        if ((HasMovementFlag(WotLK::MOVEFLAG_SWIMMING | WotLK::MOVEFLAG_FLYING)) || (moveFlags2WotLK & WotLK::MOVEFLAG2_ALWAYS_ALLOW_PITCHING))
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
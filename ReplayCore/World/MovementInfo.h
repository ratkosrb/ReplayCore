#ifndef __MOVEMENT_INFO_H
#define __MOVEMENT_INFO_H

#include "../Defines/Common.h"
#include "ObjectGuid.h"
#include "ObjectDefines.h"

class Unit;
class ByteBuffer;

struct JumpInfo
{
    JumpInfo() : zspeed(0.f), sinAngle(0.f), cosAngle(0.f), xyspeed(0.f) {}
    JumpInfo(float zspeed_, float sinAngle_, float cosAngle_, float xyspeed_) :
        zspeed(zspeed_), sinAngle(sinAngle_), cosAngle(cosAngle_), xyspeed(xyspeed_) {}
    float zspeed, sinAngle, cosAngle, xyspeed;
    bool IsEmpty() const
    {
        return !zspeed && !sinAngle && !cosAngle && !xyspeed;
    }
};

class MovementInfo
{
    public:
        MovementInfo() : moveFlags(0), moveFlags2TBC(0), moveFlags2WotLK(0), time(0), ctime(0),
            t_time(0), t_seat(0), t_time2(0), s_pitch(0.0f), fallTime(0), splineElevation(0.0f) {}

        // Read/Write methods
        void Read(ByteBuffer &data);
        void Write(ByteBuffer &data) const;
        void CorrectData();

        // Movement flags manipulations
        void AddMovementFlag(uint32 f) { moveFlags |= f; }
        void RemoveMovementFlag(uint32 f) { moveFlags &= ~f; }
        bool HasMovementFlag(uint32 f) const { return (moveFlags & f) != 0; }
        uint32 GetMovementFlags() const { return moveFlags; }
        void SetMovementFlags(uint32 f) { moveFlags = f; }

        // Position manipulations
        Position const* GetPos() const { return &pos; }
        void SetTransportData(ObjectGuid guid, float x, float y, float z, float o, uint32 time)
        {
            t_guid = guid;
            t_pos.x = x;
            t_pos.y = y;
            t_pos.z = z;
            t_pos.o = o;
            t_time = time;
        }
        void ClearTransportData()
        {
            t_guid = ObjectGuid();
            t_pos.x = 0.0f;
            t_pos.y = 0.0f;
            t_pos.z = 0.0f;
            t_pos.o = 0.0f;
            t_time = 0;
        }
        ObjectGuid const& GetTransportGuid() const { return t_guid; }
        Position const* GetTransportPos() const { return &t_pos; }
        Position* GetTransportPos() { return &t_pos; }
        uint32 GetTransportTime() const { return t_time; }
        uint32 GetFallTime() const { return fallTime; }
        void ChangeOrientation(float o) { pos.o = o; }
        void ChangePosition(float x, float y, float z, float o) { pos.x = x; pos.y = y; pos.z = z; pos.o = o; }
        void UpdateTime(uint32 _time) { time = _time; }

        JumpInfo const& GetJumpInfo() const { return jump; }
    //private:
        // common
        uint32  moveFlags;                                  // see enum MovementFlags
        uint8 moveFlags2TBC;                                // see enum MovementFlags2
        uint16  moveFlags2WotLK;                            // see enum MovementFlags2
        uint32  time;
        uint32  ctime; // Client time
        Position pos;
        // transport
        ObjectGuid t_guid;
        Position t_pos;
        uint32  t_time;
        int8     t_seat;
        uint32   t_time2;
        // swimming and unknown
        float   s_pitch;
        // last fall time
        uint32  fallTime;
        // jumping
        JumpInfo jump;
        // spline
        float splineElevation;
};

inline ByteBuffer& operator<< (ByteBuffer& buf, MovementInfo const& mi)
{
    mi.Write(buf);
    return buf;
}

inline ByteBuffer& operator >> (ByteBuffer& buf, MovementInfo& mi)
{
    mi.Read(buf);
    return buf;
}


#endif
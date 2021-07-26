#ifndef __MOVE_SPLINE_H
#define __MOVE_SPLINE_H

#include "../Defines/Common.h"
#include "../Defines/ByteBuffer.h"
#include "ObjectDefines.h"
#include "ObjectGuid.h"
#include <vector>

class Unit;

struct MoveSpline
{
    MoveSpline() = default;
    MoveSpline(const MoveSpline&) = delete;
    void Initialize(Vector3 const& startPosition, uint32 moveTime, uint8 type, uint32 flags, float orientation, std::vector<Vector3> const& destinationPoints, ObjectGuid transportGuid, bool isCyclic, bool isCatmullrom);
    void Reset()
    {
        m_initialized = false;;
        m_id = 0;
        m_startPosition = Vector3();
        m_startTimeMs = 0;
        m_type = 0;
        m_finalOrientation = 0.0f;
        m_flags = 0;
        m_moveTimeMs = 0;
        m_destinationPoints.clear();
    }
    void WriteMove(ByteBuffer &data) const;
    void WriteCreate(ByteBuffer &data) const;
    void Update(Unit* pUnit);
    bool m_initialized = false;
    static uint32 m_maxId;
    uint32 m_id = 0;
    Vector3 m_startPosition;
    uint64 m_startTimeMs = 0; // when movement started in sniff replay time
    uint8 m_type = 0;
    float m_finalOrientation = 0.0f;
    uint32 m_flags = 0;
    uint32 m_moveTimeMs = 0; // how long the movement should take
    std::vector<Vector3> m_destinationPoints;
    ObjectGuid m_transportGuid;
    bool m_cyclic = false;
    bool m_catmullrom = false;
};

#endif

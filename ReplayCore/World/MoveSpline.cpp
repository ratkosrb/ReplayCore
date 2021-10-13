#include "MoveSpline.h"
#include "MovementDefines.h"
#include "Unit.h"
#include "ReplayMgr.h"
#include "WorldServer.h"
#include "../Defines/ClientVersions.h"

uint32 MoveSpline::m_maxId = 0;

void MoveSpline::Initialize(Vector3 const& startPosition, uint32 moveTime, uint8 type, uint32 flags, float orientation, std::vector<Vector3> const& destinationPoints, ObjectGuid transportGuid, bool isCyclic, bool isCatmullrom)
{
    m_id = m_maxId++;
    m_startTimeMs = sReplayMgr.GetCurrentSniffTimeMs();
    m_startPosition = startPosition;
    m_moveTimeMs = moveTime;
    m_type = type;
    m_flags = flags;
    m_finalOrientation = orientation;
    m_destinationPoints = destinationPoints;
    if (m_destinationPoints.empty() && m_type != SPLINE_TYPE_STOP)
        m_destinationPoints.push_back(startPosition);
    m_transportGuid = transportGuid;
    m_cyclic = isCyclic;
    m_catmullrom = isCatmullrom;
    m_initialized = true;
}

void MoveSpline::WriteMove(WorldPacket& data) const
{
    data << float(m_startPosition.x);
    data << float(m_startPosition.y);
    data << float(m_startPosition.z);
    data << uint32(m_id);
    data << uint8(m_type);

    switch (m_type)
    {
        case SPLINE_TYPE_NORMAL:
            break;
        case SPLINE_TYPE_STOP:
            return;
        case SPLINE_TYPE_FACING_SPOT:
            data << float(0);
            data << float(0);
            data << float(0);
            break;
        case SPLINE_TYPE_FACING_TARGET:
            data << ObjectGuid();
            break;
        case SPLINE_TYPE_FACING_ANGLE:
            data << float(m_finalOrientation);
            break;
    }

    data << uint32(m_flags);

    if ((sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2) && (m_flags & WotLK::SplineFlags::Animation))
    {
        data << uint8(0);  // Animation State
        data << uint32(0); // Async-time in ms
    }

    data << uint32(m_moveTimeMs);

    if ((sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2) && (m_flags & WotLK::SplineFlags::Parabolic))
    {
        data << float(1.0f); // Vertical Speed
        data << uint32(0);   // Async-time in ms
    }
    
    uint32 pointsCount = m_destinationPoints.size();
    data << uint32(pointsCount);
    if (pointsCount > 0)
    {
        if (m_catmullrom || pointsCount == 1)
        {
            for (auto const& itr : m_destinationPoints)
            {
                data << float(itr.x);
                data << float(itr.y);
                data << float(itr.z);
            }
        }
        else
        {
            // final destination
            uint32 finalPointIndex = pointsCount - 1;
            Vector3 destination = m_destinationPoints[finalPointIndex];
            data << float(m_destinationPoints[finalPointIndex].x);
            data << float(m_destinationPoints[finalPointIndex].y);
            data << float(m_destinationPoints[finalPointIndex].z);

            // other points
            Vector3 offset;

            // first and last points already appended
            for (uint32 i = 0; i < finalPointIndex; ++i)
            {
                if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
                {
                    offset = destination - m_destinationPoints[i];
                    // The client freezes when it gets a zero offset.
                    if (fabs(offset.x) < 0.25 && fabs(offset.y) < 0.25 && fabs(offset.z) < 0.25)
                    {
                        if (offset.z < 0)
                            offset.z += 0.51f;
                        else
                            offset.z += 0.26f;
                    }
                }
                else
                {
                    Vector3 middle = (m_destinationPoints[0] + m_destinationPoints[finalPointIndex]) / 2.f;
                    offset = middle - m_destinationPoints[i];
                }
                
                data.appendPackXYZ(offset.x, offset.y, offset.z);
            }
        }
    }
}

void MoveSpline::WriteCreate(ByteBuffer& data) const
{
    uint32 splineFlags = m_flags;
    if (m_type == SPLINE_TYPE_FACING_ANGLE)
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            splineFlags |= Vanilla::SplineFlags::Final_Angle;
        else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            splineFlags |= TBC::SplineFlags::Final_Angle;
        else
            splineFlags |= WotLK::SplineFlags::Final_Angle;
    }
    data << uint32(splineFlags);
    if (m_type == SPLINE_TYPE_FACING_ANGLE)
        data << float(m_finalOrientation);
    data << uint32(1 + sReplayMgr.GetCurrentSniffTimeMs() - m_startTimeMs);
    data << uint32(m_moveTimeMs);
    data << uint32(m_id);

    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_1_0)
    {
        data << float(1.0f); // Spline Duration Multiplier
        data << float(1.0f); // Spline Duration Multiplier Next
        data << uint32(0);   // Spline Vertical Acceleration
        data << uint32(0);   // Spline Start Time
    }

    assert(!m_destinationPoints.empty());

    uint32 pointsCount = std::max<uint32>(4, m_destinationPoints.size());
    data << uint32(pointsCount);
    for (auto const& itr : m_destinationPoints)
    {
        data << float(itr.x);
        data << float(itr.y);
        data << float(itr.z);
    }
    if (m_destinationPoints.size() < 4)
    {
        for (uint32 i = 0; i < (4 - m_destinationPoints.size()); i++)
        {
            data << float(m_destinationPoints[0].x);
            data << float(m_destinationPoints[0].y);
            data << float(m_destinationPoints[0].z);
        }
    }

    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_8)
        data << uint8(m_catmullrom ? 1 : 0); // Spline Mode

    if (m_cyclic)
    {
        data << float(0);
        data << float(0);
        data << float(0);
    }
    else
    {
        uint32 finalPointIndex = m_destinationPoints.size() - 1;
        data << float(m_destinationPoints[finalPointIndex].x);
        data << float(m_destinationPoints[finalPointIndex].y);
        data << float(m_destinationPoints[finalPointIndex].z);
    }
}

void MoveSpline::Update(Unit* pUnit)
{
    if (!m_initialized || m_cyclic || !m_moveTimeMs)
        return;

    if ((pUnit->GetLastPositionUpdate() > (m_startTimeMs / IN_MILLISECONDS)) ||
        (sReplayMgr.GetCurrentSniffTimeMs() < m_startTimeMs) ||
        (pUnit->GetHealth() == 0))
    {
        Reset();
        return;
    }

    uint64 elapsedTime = sReplayMgr.GetCurrentSniffTimeMs() - m_startTimeMs;
    if (!elapsedTime)
        return;

    if (elapsedTime >= m_moveTimeMs)
    {
        if (m_transportGuid.IsEmpty())
        {
            if (m_finalOrientation != 100)
                pUnit->Relocate(m_destinationPoints[0].x, m_destinationPoints[0].y, m_destinationPoints[0].z, m_finalOrientation);
            else
                pUnit->Relocate(m_destinationPoints[0].x, m_destinationPoints[0].y, m_destinationPoints[0].z);
        }
        else
        {
            pUnit->GetMovementInfo().t_pos.x = m_destinationPoints[0].x;
            pUnit->GetMovementInfo().t_pos.y = m_destinationPoints[0].y;
            pUnit->GetMovementInfo().t_pos.z = m_destinationPoints[0].z;
        }
        
        Reset();
        return;
    }

    if (m_destinationPoints.size() > 1)
    {
        float percentDone = float(elapsedTime) / float(m_moveTimeMs);
        uint32 reachedPoint = m_destinationPoints.size() * percentDone;
        if (reachedPoint > 1)
        {
            if (m_transportGuid.IsEmpty())
                pUnit->Relocate(m_destinationPoints[reachedPoint].x, m_destinationPoints[reachedPoint].y, m_destinationPoints[reachedPoint].z);
            else
            {
                pUnit->GetMovementInfo().t_pos.x = m_destinationPoints[reachedPoint].x;
                pUnit->GetMovementInfo().t_pos.y = m_destinationPoints[reachedPoint].y;
                pUnit->GetMovementInfo().t_pos.z = m_destinationPoints[reachedPoint].z;
            }
        }   
    }
}

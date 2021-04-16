/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 * Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
 * Copyright (C) 2016-2017 Elysium Project <https://github.com/elysium-project>
 *
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

#include "../Defines/Common.h"
#include "UpdateData.h"
#include "../Defines/ByteBuffer.h"
#include "../Defines/WorldPacket.h"
#include "Opcodes.h"
#include "WorldServer.h"
#include "ObjectGuid.h"

#define MAX_UNCOMPRESSED_PACKET_SIZE 0x8000 // 32ko

UpdateData::UpdateData()
{
}

UpdateData::~UpdateData()
{
    Clear();
}

void UpdateData::AddOutOfRangeGUID(ObjectGuidSet& guids)
{
    m_outOfRangeGUIDs.insert(guids.begin(), guids.end());
}

void UpdateData::AddOutOfRangeGUID(ObjectGuid const& guid)
{
    m_outOfRangeGUIDs.insert(guid);
}

void UpdateData::AddUpdateBlock(ByteBuffer const& block)
{
    if (m_datas.empty())
        m_datas.push_back(UpdatePacket());
    std::list<UpdatePacket>::iterator it = m_datas.end();
    --it;
    if (it->data.wpos() > MAX_UNCOMPRESSED_PACKET_SIZE)
    {
        m_datas.push_back(UpdatePacket());
        it = m_datas.end();
        --it;
    }
    it->data.append(block);
    ++it->blockCount;
}

bool UpdateData::BuildPacket(WorldPacket* packet, bool hasTransport)
{
    if (m_datas.empty())
        return BuildPacket(packet, nullptr, hasTransport);
    return BuildPacket(packet, &(m_datas.front()), hasTransport);
}

bool UpdateData::BuildPacket(WorldPacket* packet, UpdatePacket const* updPacket, bool hasTransport)
{
    assert(packet->empty());                         // shouldn't happen

    ByteBuffer buf(4 + 1 + (m_outOfRangeGUIDs.empty() ? 0 : 1 + 4 + 9 * m_outOfRangeGUIDs.size()) + (updPacket ? updPacket->data.wpos() : 0));

    uint32 blockCount = updPacket ? updPacket->blockCount : 0;
    buf << (uint32)(!m_outOfRangeGUIDs.empty() ? blockCount + 1 : blockCount);
    buf << (uint8)(hasTransport ? 1 : 0);

    if (!m_outOfRangeGUIDs.empty())
    {
        buf << (uint8) UPDATETYPE_OUT_OF_RANGE_OBJECTS;
        buf << (uint32) m_outOfRangeGUIDs.size();

#if SUPPORTED_CLIENT_BUILD > CLIENT_BUILD_1_8_4
        for (const auto& guid : m_outOfRangeGUIDs)
            buf << guid.WriteAsPacked();
#else
        for (const auto& guid : m_outOfRangeGUIDs)
            buf << guid;
#endif
    }

    if (updPacket)
        buf.append(updPacket->data);

    size_t pSize = buf.wpos();                              // use real used data size

    if (pSize >= MAX_UNCOMPRESSED_PACKET_SIZE)
    {
        printf("[CRASH-CLIENT] Too large packet: %u\n", pSize);
        return false;
    } 
    else
    {
        packet->append(buf);
        packet->SetOpcode(sWorld.GetOpcode("SMSG_UPDATE_OBJECT"));
    }

    return true;
}

void UpdateData::Send(bool hasTransport)
{
    WorldPacket data;
    if (m_datas.empty() && !m_outOfRangeGUIDs.empty())
    {
        if (BuildPacket(&data, nullptr, hasTransport))
            sWorld.SendPacket(data);
        m_outOfRangeGUIDs.clear();
        return;
    }
    for (const auto& itr : m_datas)
    {
        if (BuildPacket(&data, &itr, hasTransport))
            sWorld.SendPacket(data);
        data.clear();
        m_outOfRangeGUIDs.clear();
    }
}

void UpdateData::Clear()
{
    m_datas.clear();
    m_outOfRangeGUIDs.clear();
}


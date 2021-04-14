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

#ifndef MANGOSSERVER_WORLDPACKET_H
#define MANGOSSERVER_WORLDPACKET_H

#include "Common.h"
#include "ByteBuffer.h"

// Note: m_opcode and size stored in platfom dependent format
// ignore endianess until send, and converted at receive
class WorldPacket : public ByteBuffer
{
    public:
                                                            // just container for later use
        WorldPacket()                                       : ByteBuffer(0), m_opcode(0), m_recvdTime(0)
        {
        }
        explicit WorldPacket(uint16 opcode, size_t res=200) : ByteBuffer(res), m_opcode(opcode), m_recvdTime(0) { }
                                                            // copy constructor
        WorldPacket(WorldPacket const& packet)              : ByteBuffer(packet), m_opcode(packet.m_opcode), m_recvdTime(0)
        {
        }

        WorldPacket(WorldPacket&& packet) : ByteBuffer(std::move(packet)), m_opcode(packet.m_opcode), m_recvdTime(packet.m_recvdTime)
        {
        }

        WorldPacket& operator=(WorldPacket&& rhs)
        {
            m_opcode = rhs.m_opcode;
            m_recvdTime = rhs.m_recvdTime;
            ByteBuffer::operator=(std::move(rhs));
            return *this;
        }

        void Initialize(uint16 opcode, size_t newres=200)
        {
            clear();
            _storage.reserve(newres);
            m_opcode = opcode;
        }

        uint16 GetOpcode() const { return m_opcode; }
        void SetOpcode(uint16 opcode) { m_opcode = opcode; }

        uint32 GetPacketTime() const { return m_recvdTime; }
        void FillPacketTime(uint32 t) { m_recvdTime = t; }

    protected:
        uint16 m_opcode;
        uint32 m_recvdTime;
};

#if defined(__GNUC__)
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

struct ServerPktHeader
{
    uint16 size;
    uint16 cmd;
};

struct ServerPktHeaderWotlk
{
    /*
    * size is the length of the payload _plus_ the length of the opcode
    */
    ServerPktHeaderWotlk(uint32 size, uint16 cmd) : size(size)
    {
        uint8 headerIndex = 0;
        if (isLargePacket())
        {
            printf("initializing large server to client packet. Size: %u, cmd: %u\n", size, cmd);
            header[headerIndex++] = 0x80 | (0xFF & (size >> 16));
        }
        header[headerIndex++] = 0xFF & (size >> 8);
        header[headerIndex++] = 0xFF & size;

        header[headerIndex++] = 0xFF & cmd;
        header[headerIndex++] = 0xFF & (cmd >> 8);
    }

    uint8 getHeaderLength()
    {
        // cmd = 2 bytes, size= 2||3bytes
        return 2 + (isLargePacket() ? 3 : 2);
    }

    bool isLargePacket()
    {
        return size > 0x7FFF;
    }

    const uint32 size;
    uint8 header[5];
};

struct ClientPktHeader
{
    uint16 size;
    uint32 cmd;
};

#if defined(__GNUC__)
#pragma pack()
#else
#pragma pack(pop)
#endif

#endif

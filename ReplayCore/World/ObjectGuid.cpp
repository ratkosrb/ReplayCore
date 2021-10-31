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

#include "ObjectGuid.h"
#include "GameDataMgr.h"
#include "WorldServer.h"
#include "ReplayMgr.h"
#include <sstream>

char const* ObjectGuid::GetTypeName(HighGuid high)
{
    switch (high)
    {
        case HIGHGUID_ITEM:
            return "Item";
        case HIGHGUID_PLAYER:
            return "Player";
        case HIGHGUID_GAMEOBJECT:
            return "GameObject";
        case HIGHGUID_TRANSPORT:
            return "Transport";
        case HIGHGUID_UNIT:
            return "Creature";
        case HIGHGUID_PET:
            return "Pet";
        case HIGHGUID_DYNAMICOBJECT:
            return "DynObject";
        case HIGHGUID_CORPSE:
            return "Corpse";
        case HIGHGUID_MO_TRANSPORT:
            return "MoTransport";
        default:
            return "<unknown>";
    }
}

std::string ObjectGuid::GetString(bool includeName) const
{
    std::ostringstream str;
    str << GetTypeName();

    if (includeName)
    {
        std::string name = GetName();
        if (!name.empty())
            str << " " << name;
    }

    str << " (";
    if (HasEntry())
        str << "Entry: " << GetEntry() << " ";
    str << "Guid: " << GetCounter() << ")";
    return str.str();
}

std::string ObjectGuid::GetName() const
{
    if (IsEmpty())
        return std::string();

    switch (GetHigh())
    {
        case HIGHGUID_UNIT:
        {
            if (CreatureTemplate const* pTemplate = sGameDataMgr.GetCreatureTemplate(GetEntry()))
                return pTemplate->name;
            break;
        }
        case HIGHGUID_PET:
        {
            if (CreatureData const* pSpawnData = sReplayMgr.GetCreatureSpawnData(GetCounter()))
                return sGameDataMgr.GetCreatureName(pSpawnData->entry);
            break;
        }
        case HIGHGUID_PLAYER:
        {
            return sWorld.GetPlayerName(*this);
        }
        case HIGHGUID_GAMEOBJECT:
        case HIGHGUID_MO_TRANSPORT:
        {
            if (GameObjectTemplate const* pTemplate = sGameDataMgr.GetGameObjectTemplate(GetEntry()))
                return pTemplate->name;
            break;
        }
        case HIGHGUID_DYNAMICOBJECT:
        {
            if (DynamicObjectData const* pData = sReplayMgr.GetDynamicObjectSpawnData(GetCounter()))
                return sGameDataMgr.GetSpellName(pData->spellId);
        }
        default:
        {
            printf("Error: Unsupported object type %u in ObjectGuid::GetName!\n", GetTypeId());
            break;
        }
    }

    return std::string();
}

void ObjectGuid::Set(uint64 const& guid)
{
    m_guid = guid;
}

template<HighGuid high>
uint32 ObjectGuidGenerator<high>::Generate()
{
    if (!m_freedGuids.empty())
    {
        uint32 g = m_freedGuids.front();
        m_freedGuids.pop();
        return g;
    }
    if (m_nextGuid >= ObjectGuid::GetMaxCounter(high) - 1)
    {
        printf("%s guid overflow!!", ObjectGuid::GetTypeName(high));
        //World::StopNow(ERROR_EXIT_CODE);
    }
    return m_nextGuid++;
}

template<HighGuid high>
void ObjectGuidGenerator<high>::GenerateRange(uint32& first, uint32& last)
{
    const static int GENERATE_RANGE_SIZE = 100;
    if (m_nextGuid >= ObjectGuid::GetMaxCounter(high) - GENERATE_RANGE_SIZE)
    {
        printf("%s guid overflow!!", ObjectGuid::GetTypeName(high));
        //World::StopNow(ERROR_EXIT_CODE);
    }
    first = m_nextGuid;
    m_nextGuid += GENERATE_RANGE_SIZE;
    last = m_nextGuid;
}

ByteBuffer& operator<< (ByteBuffer& buf, ObjectGuid const& guid)
{
    buf << uint64(guid.GetRawValue());
    return buf;
}

ByteBuffer &operator>>(ByteBuffer& buf, ObjectGuid& guid)
{
    uint64 value = buf.read<uint64>();
    ObjectGuid::ClampPlayerGuid(value);
    guid.Set(value);
    return buf;
}

ByteBuffer& operator<< (ByteBuffer& buf, PackedGuid const& guid)
{
    buf.append(guid.m_packedGuid);
    return buf;
}

ByteBuffer &operator>>(ByteBuffer& buf, PackedGuidReader const& guid)
{
    uint64 value = buf.readPackGUID();
    ObjectGuid::ClampPlayerGuid(value);
    guid.m_guidPtr->Set(value);
    return buf;
}

// If the GUID is a player GUID, clamp it to the low guid or we open
// ourselves to packet manipulation where a player can send their low
// guid with a mutple of 0xFFFFFFFF+1 added to it, causing hashing to
// fail but some other functionality to succeed
void ObjectGuid::ClampPlayerGuid(uint64& value)
{
    if (ObjectGuid::GetHigh(value) == HIGHGUID_PLAYER)
    {
        value = static_cast<uint64>(GetCounter(value, HasEntry(HIGHGUID_PLAYER)));
    }
}

template class ObjectGuidGenerator<HIGHGUID_ITEM>;
template class ObjectGuidGenerator<HIGHGUID_PLAYER>;
template class ObjectGuidGenerator<HIGHGUID_GAMEOBJECT>;
template class ObjectGuidGenerator<HIGHGUID_TRANSPORT>;
template class ObjectGuidGenerator<HIGHGUID_UNIT>;
template class ObjectGuidGenerator<HIGHGUID_PET>;
template class ObjectGuidGenerator<HIGHGUID_DYNAMICOBJECT>;
template class ObjectGuidGenerator<HIGHGUID_CORPSE>;

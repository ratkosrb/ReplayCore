#include "WorldServer.h"
#include "../Defines/WorldPacket.h"
#include "GameDataMgr.h"
#include "GameDataDefines.h"
#include "../Defines/ClientVersions.h"
#include "../Defines/Utility.h"
#include "ReplayMgr.h"
#include "ChatDefines.h"
#include "SpellCastTargets.h"
#include "SpellDefines.h"
#include "Aura.h"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

void WorldServer::SendAuthChallenge()
{
    if (m_sessionData.build >= CLIENT_BUILD_3_3_5a)
    {
        WorldPacket packet(GetOpcode("SMSG_AUTH_CHALLENGE"), 40);
        packet << uint32(1);
        packet << m_sessionData.seed;
        BigNumber seed1;
        seed1.SetRand(16 * 8);
        packet.append(seed1.AsByteArray(16).data(), 16);               // new encryption seeds
        BigNumber seed2;
        seed2.SetRand(16 * 8);
        packet.append(seed2.AsByteArray(16).data(), 16);               // new encryption seeds
        SendPacket(packet);
    }
    else
    {
        WorldPacket packet(GetOpcode("SMSG_AUTH_CHALLENGE"), 4);
        packet << m_sessionData.seed;
        SendPacket(packet);
    }
}

void WorldServer::SendAddonInfo(std::vector<ClientAddonData> const& clientAddons)
{
    WorldPacket data(GetOpcode("SMSG_ADDON_INFO"));

    unsigned char tdata[256] =
    {
        0xC3, 0x5B, 0x50, 0x84, 0xB9, 0x3E, 0x32, 0x42, 0x8C, 0xD0, 0xC7, 0x48, 0xFA, 0x0E, 0x5D, 0x54,
        0x5A, 0xA3, 0x0E, 0x14, 0xBA, 0x9E, 0x0D, 0xB9, 0x5D, 0x8B, 0xEE, 0xB6, 0x84, 0x93, 0x45, 0x75,
        0xFF, 0x31, 0xFE, 0x2F, 0x64, 0x3F, 0x3D, 0x6D, 0x07, 0xD9, 0x44, 0x9B, 0x40, 0x85, 0x59, 0x34,
        0x4E, 0x10, 0xE1, 0xE7, 0x43, 0x69, 0xEF, 0x7C, 0x16, 0xFC, 0xB4, 0xED, 0x1B, 0x95, 0x28, 0xA8,
        0x23, 0x76, 0x51, 0x31, 0x57, 0x30, 0x2B, 0x79, 0x08, 0x50, 0x10, 0x1C, 0x4A, 0x1A, 0x2C, 0xC8,
        0x8B, 0x8F, 0x05, 0x2D, 0x22, 0x3D, 0xDB, 0x5A, 0x24, 0x7A, 0x0F, 0x13, 0x50, 0x37, 0x8F, 0x5A,
        0xCC, 0x9E, 0x04, 0x44, 0x0E, 0x87, 0x01, 0xD4, 0xA3, 0x15, 0x94, 0x16, 0x34, 0xC6, 0xC2, 0xC3,
        0xFB, 0x49, 0xFE, 0xE1, 0xF9, 0xDA, 0x8C, 0x50, 0x3C, 0xBE, 0x2C, 0xBB, 0x57, 0xED, 0x46, 0xB9,
        0xAD, 0x8B, 0xC6, 0xDF, 0x0E, 0xD6, 0x0F, 0xBE, 0x80, 0xB3, 0x8B, 0x1E, 0x77, 0xCF, 0xAD, 0x22,
        0xCF, 0xB7, 0x4B, 0xCF, 0xFB, 0xF0, 0x6B, 0x11, 0x45, 0x2D, 0x7A, 0x81, 0x18, 0xF2, 0x92, 0x7E,
        0x98, 0x56, 0x5D, 0x5E, 0x69, 0x72, 0x0A, 0x0D, 0x03, 0x0A, 0x85, 0xA2, 0x85, 0x9C, 0xCB, 0xFB,
        0x56, 0x6E, 0x8F, 0x44, 0xBB, 0x8F, 0x02, 0x22, 0x68, 0x63, 0x97, 0xBC, 0x85, 0xBA, 0xA8, 0xF7,
        0xB5, 0x40, 0x68, 0x3C, 0x77, 0x86, 0x6F, 0x4B, 0xD7, 0x88, 0xCA, 0x8A, 0xD7, 0xCE, 0x36, 0xF0,
        0x45, 0x6E, 0xD5, 0x64, 0x79, 0x0F, 0x17, 0xFC, 0x64, 0xDD, 0x10, 0x6F, 0xF3, 0xF5, 0xE0, 0xA6,
        0xC3, 0xFB, 0x1B, 0x8C, 0x29, 0xEF, 0x8E, 0xE5, 0x34, 0xCB, 0xD1, 0x2A, 0xCE, 0x79, 0xC3, 0x9A,
        0x0D, 0x36, 0xEA, 0x01, 0xE0, 0xAA, 0x91, 0x20, 0x54, 0xF0, 0x72, 0xD8, 0x1E, 0xC7, 0x89, 0xD2
    };

    uint64 standardCRC = GetClientBuild() < CLIENT_BUILD_3_0_2 ? UINT64_C(0x1c776d01) : UINT64_C(0x4c1c776d);

    for (auto const& itr : clientAddons)
    {
        data << (uint8)2;

        uint8 unk1 = 1;
        data << (uint8)unk1;
        if (unk1)
        {
            uint8 unk2 = itr.modulusCRC != standardCRC; // If addon is Standard addon CRC
            data << (uint8)unk2;
            if (unk2)
                data.append(tdata, sizeof(tdata));

            data << (uint32)0;
        }

        uint8 unk3 = 0;
        data << (uint8)unk3;
        if (unk3)
        {
            // String, 256
            data << uint8(0);
        }
    }

    SendPacket(data);
}

void WorldServer::SendCharEnum(std::vector<CharEnumData> const& characters)
{
    uint8 count = std::min(uint32(characters.size()), uint32(10));

    WorldPacket data(GetOpcode("SMSG_CHAR_ENUM"));
    data << uint8(count);

    for (auto const& character : characters)
    {
        if (count <= 0)
            break;

        data << character.guid;
        data << character.name;
        data << uint8(character.raceId);
        data << uint8(character.classId);
        data << uint8(character.gender);
        data << uint8(character.skinColor);
        data << uint8(character.face);
        data << uint8(character.hairStyle);
        data << uint8(character.hairColor);
        data << uint8(character.facialHair);
        data << uint8(character.level);

        data << uint32(character.zoneId);
        data << uint32(character.mapid);
        data << float(character.positionX);
        data << float(character.positionY);
        data << float(character.positionZ);

        data << uint32(character.guildId);
        data << uint32(character.characterFlags);

        if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
            data << uint32(character.customizationFlags);

        data << uint8(character.firstLogin);
        data << uint32(character.petDisplayId);
        data << uint32(character.petLevel);
        data << uint32(character.petFamily);

        for (int i = 0; i < EQUIPMENT_SLOT_END; i++)
        {
            if (ItemPrototype const* pItem = sGameDataMgr.GetItemPrototype(character.equipmentItemId[i]))
            {
                data << uint32(pItem->DisplayInfoID);
                data << uint8(pItem->InventoryType);
                if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
                    data << uint32(character.equipmentEnchantId[i]);
            }
            else
            {
                data << uint32(0); // display id
                data << uint8(0); // inventory type;
                if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
                    data << uint32(0); // enchant id
            }
        }

        int bagCount = (GetClientBuild() >= CLIENT_BUILD_3_3_3) ? 4 : 1;
        for (int j = 0; j < bagCount; j++)
        {
            data << uint32(0); // display id
            data << uint8(0); // inventory type;
            if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
                data << uint32(0); // enchant id
        }

        count--;
    }
    SendPacket(data);
}

void WorldServer::SendCharCreate(uint8 result)
{
    WorldPacket data(GetOpcode("SMSG_CHAR_CREATE"), 1);
    data << uint8(result);
    SendPacket(data);
}

void WorldServer::SendLoginVerifyWorld(WorldLocation const& location)
{
    WorldPacket data(GetOpcode("SMSG_LOGIN_VERIFY_WORLD"), 20);
    data << uint32(location.mapId);
    data << float(location.x);
    data << float(location.y);
    data << float(location.z);
    data << float(location.o);
    SendPacket(data);
}

#define GLOBAL_CACHE_MASK           0x15
#define PER_CHARACTER_CACHE_MASK    0xEA
#define NUM_ACCOUNT_DATA_TYPES 8

void WorldServer::SendAccountDataTimes()
{
    WorldPacket data;
    if (GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        SendAccountDataTimesVanilla();
    }
    else
    {
        SendAccountDataTimesWotLK(GLOBAL_CACHE_MASK);
        SendAccountDataTimesWotLK(PER_CHARACTER_CACHE_MASK);
    }
}

void WorldServer::SendAccountDataTimesVanilla()
{
    WorldPacket data(GetOpcode("SMSG_ACCOUNT_DATA_TIMES"), 128);
    for (int i = 0; i < 32; ++i)
        data << uint32(0);
    SendPacket(data);
}

void WorldServer::SendAccountDataTimesWotLK(uint32 mask)
{
    WorldPacket data(GetOpcode("SMSG_ACCOUNT_DATA_TIMES"), 4 + 1 + 4 + 8 * 4);
    data << uint32(time(nullptr));                             // unix time of something
    data << uint8(1);

    if (GetClientBuild() >= CLIENT_BUILD_3_2_0)
    {
        data << uint32(mask);                                   // type mask
        for (uint32 i = 0; i < NUM_ACCOUNT_DATA_TYPES; ++i)
        {
            if (mask & (1 << i))
            {
                data << uint32(0);// also unix time
            }
        }
    }

    SendPacket(data);
}

void WorldServer::SendUpdateAccountDataComplete(uint32 type)
{
    WorldPacket data(GetOpcode("SMSG_UPDATE_ACCOUNT_DATA_COMPLETE"), 4 + 4);
    data << uint32(type);
    data << uint32(0);
    SendPacket(data);
}

void WorldServer::SendFeatureSystemStatus(bool enableComplaintChat, bool enableVoiceChat)
{
    WorldPacket data(GetOpcode("SMSG_FEATURE_SYSTEM_STATUS"), 2);
    data << uint8(enableComplaintChat);
    data << uint8(enableVoiceChat);
    SendPacket(data);
}

void WorldServer::SendLoginSetTimeSpeed()
{
    WorldPacket data(GetOpcode("SMSG_LOGIN_SETTIMESPEED"), 4 + 4);
    data << uint32(secsToTimeBitFields(time(nullptr)));
    data << (float)0.01666667f;                             // game speed
    if (GetClientBuild() >= CLIENT_BUILD_3_1_2)
        data << uint32(0);
    SendPacket(data);
}

void WorldServer::SendSetRestStart(uint32 restStateTime)
{
    WorldPacket data(GetOpcode("SMSG_SET_REST_START"), 4);
    data << uint32(restStateTime);  // rest state time
    SendPacket(data);
}

void WorldServer::SendBindPointUpdate(WorldLocation const& location, uint32 zoneId)
{
    WorldPacket data(GetOpcode("SMSG_BINDPOINTUPDATE"), 5 * 4);
    data << float(location.x);
    data << float(location.y);
    data << float(location.z);
    data << uint32(location.mapId);
    data << uint32(zoneId);
    SendPacket(data);
}

void WorldServer::SendTutorialFlags()
{
    WorldPacket data(GetOpcode("SMSG_TUTORIAL_FLAGS"), 4 * 8);
    for (int i = 0; i < 32; i++)
        data << uint8(255);
    SendPacket(data);
}

void WorldServer::SendInitialSpells(uint8 raceId, uint8 classId)
{
    WorldPacket data(GetOpcode("SMSG_INITIAL_SPELLS"));
    data << uint8(0);

    PlayerInfo const* pInfo = sGameDataMgr.GetPlayerInfo(raceId, classId);
    if (!pInfo)
    {
        printf("[WORLD] SendInitialSpells: No data for race %u and class %u.\n", raceId, classId);
        
        // spells count
        data << uint16(0);
    }
    else
    {
        // spells count
        data << uint16(pInfo->spell.size());

        for (auto const& spell : pInfo->spell)
        {
            if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
                data << uint32(spell);
            else
                data << uint16(spell);

            data << uint16(0); // it's not slot id
        }
    }

    // cooldowns count
    data << uint16(0);

    SendPacket(data);
}

void WorldServer::SendActionButtons(uint8 raceId, uint8 classId)
{
    uint16 maxActionButtons;
    if (GetClientBuild() < CLIENT_BUILD_2_3_0)
        maxActionButtons = MAX_ACTION_BUTTONS_VANILLA;
    else if (GetClientBuild() < CLIENT_BUILD_3_2_0)
        maxActionButtons = MAX_ACTION_BUTTONS_TBC;
    else
        maxActionButtons = MAX_ACTION_BUTTONS_WOTLK;

    WorldPacket data(GetOpcode("SMSG_ACTION_BUTTONS"), (maxActionButtons * 4));

    if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
        data << uint8(0); // packet type

    PlayerInfo const* pInfo = sGameDataMgr.GetPlayerInfo(raceId, classId);
    if (!pInfo)
    {
        printf("[WORLD] SendActionButtons: No data for race %u and class %u.\n", raceId, classId);
        for (uint8 button = 0; button < maxActionButtons; ++button)
            data << uint32(0);
    }
    else
    {
        std::map<uint8, ActionButton> actionButtons;
        for (auto const& action_itr : pInfo->action)
        {
            uint8 button = action_itr.button;
            uint32 action = action_itr.action;
            uint8 type = action_itr.type;

            ActionButton& ab = actionButtons[button];
            ab.SetActionAndType(action, ActionButtonType(type));
        }

        for (uint8 button = 0; button < maxActionButtons; ++button)
        {
            std::map<uint8, ActionButton>::const_iterator itr = actionButtons.find(button);
            if (itr != actionButtons.end())
                data << uint32(itr->second.packedData);
            else
                data << uint32(0);
        }
    }

    SendPacket(data);
}

void WorldServer::SendPlayerNameQueryResponse(ObjectGuid guid, char const* name, uint32 raceId, uint32 gender, uint32 classId)
{
    WorldPacket data(GetOpcode("SMSG_NAME_QUERY_RESPONSE"), (8 + 25 + 1 + 4 + 4 + 4));   // guess size

    if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
    {
        data << guid.WriteAsPacked();
        data << uint8(0); // has result
    }
    else
        data << guid;

    data << name;                                           // CString(48): played name
    data << uint8(0);                                       // CString(256): realm name for cross realm BG usage

    if (GetClientBuild() > CLIENT_BUILD_3_1_0)
    {
        data << uint8(raceId);
        data << uint8(gender);
        data << uint8(classId);
    }
    else
    {
        data << uint32(raceId);
        data << uint32(gender);
        data << uint32(classId);
    }

    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << uint8(0); // name declined

    SendPacket(data);
}

void WorldServer::SendPetNameQueryResponse(uint32 petNumber, char const* name, uint32 timestamp)
{
    WorldPacket data(GetOpcode("SMSG_PET_NAME_QUERY_RESPONSE"));
    data << uint32(petNumber);
    data << name;
    data << uint32(timestamp);
    SendPacket(data);
}

void WorldServer::SendFriendList()
{
    std::set<ObjectGuid> const& activePlayers = sReplayMgr.GetActivePlayers();

    WorldPacket data;

    // unk flag (0x1, 0x2, 0x4), 0x7 if it include ignore list
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
    {
        data.Initialize(GetOpcode("SMSG_CONTACT_LIST"));
        data << uint32(7);
    }
    else
        data.Initialize(GetOpcode("SMSG_FRIEND_LIST"));

    // friends count
    size_t countPos = data.wpos();
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << uint32(activePlayers.size());
    else
        data << uint8(activePlayers.size());

    uint32 count = 0;
    for (auto const& guid : activePlayers)
    {
        if (count >= 255)
            break;

        if (Player const* pPlayer = FindPlayer(guid))
        {
            data << pPlayer->GetObjectGuid();                  // player guid

            if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
            {
                uint32 flags = 1;
                data << uint32(flags);                         // player flag (0x1-friend?, 0x2-ignored?, 0x4-muted?)
                data << "";                                    // string note
                if (flags)                                     // if IsFriend()
                {
                    data << uint8(pPlayer->IsVisible());       // online/offline/etc?
                    data << uint32(pPlayer->GetAreaId());      // player area
                    data << uint32(pPlayer->GetLevel());       // player level
                    data << uint32(pPlayer->GetClass());       // player class
                }
            }
            else
            {
                data << uint8(pPlayer->IsVisible());           // online/offline/etc?
                if (pPlayer->IsVisible())                      // if online
                {
                    data << uint32(pPlayer->GetAreaId());      // player area
                    data << uint32(pPlayer->GetLevel());       // player level
                    data << uint32(pPlayer->GetClass());       // player class
                }
            }
            count++;
        }
    }

    if (count != activePlayers.size())
    {
        if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
            data.put<uint32>(countPos, count);
        else
            data.put<uint8>(countPos, count);
    }    

    SendPacket(data);
}

void WorldServer::SendIgnoreList()
{
    WorldPacket data(GetOpcode("SMSG_IGNORE_LIST"), (1 + 0 * 8));
    data << uint8(0); // count
    SendPacket(data);
}

void WorldServer::SendWhoList(uint32 levelMin, uint32 levelMax, uint32 raceMask, uint32 classMask, std::string playerName, std::string guildName, std::vector<uint32> zones, std::vector<std::string> names)
{
    uint32 clientcount = 0;
    WorldPacket data(GetOpcode("SMSG_WHO"), 50);
    data << uint32(clientcount);                            // clientcount place holder, listed count
    data << uint32(clientcount);                            // clientcount place holder, online count

    for (auto const& itr : m_players)
    {
        Player const* pPlayer = &itr.second;

        // do not process players which are not in world
        //if (!pPlayer->IsVisible())
        //    continue;

        // check if target's level is in level range
        uint32 lvl = pPlayer->GetLevel();
        if (lvl < levelMin || lvl > levelMax)
            continue;

        // check if class matches classmask
        uint32 class_ = pPlayer->GetClass();
        if (!(classMask & (1 << class_)))
            continue;

        // check if race matches racemask
        uint32 race = pPlayer->GetRace();
        if (!(raceMask & (1 << race)))
            continue;

        std::string pname = pPlayer->GetName();

        if (!(playerName.empty() || pname.find(playerName) != std::string::npos))
            continue;

        //std::string gname = sGuildMgr.GetGuildNameById(pPlayer->GetGuildId());
        //if (!(guildName.empty() || gname.find(guildName) != std::wstring::npos))
        //    continue;

        uint32 pzoneid = pPlayer->GetZoneId();

        bool z_show = true;
        for (uint32 i = 0; i < zones.size(); ++i)
        {
            if (zones[i] == pzoneid)
            {
                z_show = true;
                break;
            }

            z_show = false;
        }
        if (!z_show)
            continue;

        std::string aname;
        if (AreaTableEntry const* pAreaEntry = sGameDataMgr.GetAreaTableEntry(pzoneid))
            aname = pAreaEntry->name;

        bool s_show = true;
        for (uint32 i = 0; i < names.size(); ++i)
        {
            if (!names[i].empty())
            {
                if (
                    //wgname.find(str[i]) != std::wstring::npos ||
                    pname.find(names[i]) != std::string::npos ||
                    aname.find(names[i]) != std::string::npos)
                {
                    s_show = true;
                    break;
                }
                s_show = false;
            }
        }
        if (!s_show)
            continue;

        data << pname;                                      // player name
        data << "";                                         // guild name
        data << uint32(lvl);                                // player level
        data << uint32(class_);                             // player class
        data << uint32(race);                               // player race
        if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
            data << uint8(pPlayer->GetGender());            // player gender
        data << uint32(pzoneid);                            // player zone id

        // 50 is maximum player count sent to client
        if ((++clientcount) == 49)
            break;
    }

    uint32 count = m_players.size();
    data.put(0, clientcount);                               // insert right count, listed count
    data.put(4, count > 49 ? count : clientcount);          // insert right count, online count

    SendPacket(data);
}

void WorldServer::SendLogoutResponse(uint32 reason, bool instant)
{
    WorldPacket data(GetOpcode("SMSG_LOGOUT_RESPONSE"), 1 + 4);
    data << uint32(reason);
    data << uint8(instant);
    SendPacket(data);
}

void WorldServer::SendLogoutComplete()
{
    WorldPacket data(GetOpcode("SMSG_LOGOUT_COMPLETE"), 0);
    SendPacket(data);
}

void WorldServer::SendJoinedChannelNotify(std::string channelName, uint32 channelId)
{
    uint32 flags = 0;
    if (channelName.find("General - ") != std::string::npos)
        flags = CHANNEL_FLAG_NOT_LFG | CHANNEL_FLAG_GENERAL;
    else if (channelName.find("Trade - ") != std::string::npos)
        flags = CHANNEL_FLAG_TRADE | CHANNEL_FLAG_NOT_LFG | CHANNEL_FLAG_GENERAL | CHANNEL_FLAG_CITY;
    else if (channelName.find("LocalDefense - ") != std::string::npos)
        flags = CHANNEL_FLAG_NOT_LFG | CHANNEL_FLAG_GENERAL;
    else if (channelName.find("GuildRecruitment -") != std::string::npos)
        flags = CHANNEL_FLAG_NOT_LFG | CHANNEL_FLAG_GENERAL | CHANNEL_FLAG_CITY;
    else if (channelName == "LookingForGroup")
        flags = CHANNEL_FLAG_GENERAL | CHANNEL_FLAG_LFG;

    WorldPacket data(GetOpcode("SMSG_CHANNEL_NOTIFY"), 1 + channelName.size() + 1 + 4 + 4 + 1);
    data << uint8(CHAT_YOU_JOINED_NOTICE);
    data << channelName;
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        data << uint32(flags);
        data << uint32(channelId);                             // the non-zero number will be appended to the channel name
        //data << uint8(0);                                    // CString max length 512, conditional read
    }
    else
    {
        data << uint8(flags);
        data << uint32(channelId);                             // the non-zero number will be appended to the channel name
        data << uint32(0);                                     // unknown
    }
    SendPacket(data);
}

void WorldServer::SendMotd()
{
    static std::string motd = std::string("Sniff Replay Core v1: Compiled ") + std::string(__DATE__);
    WorldPacket data(GetOpcode("SMSG_MOTD"), 50);
    data << uint32(1); // line count
    data << motd;
    SendPacket(data);
}

void WorldServer::SendTimeSyncRequest()
{
    WorldPacket data(GetOpcode("SMSG_TIME_SYNC_REQ"), 4);
    data << uint32(0); // couner
    SendPacket(data);
}

void WorldServer::SendItemQuerySingleResponse(uint32 entry)
{
    ItemPrototype const* pProto = sGameDataMgr.GetItemPrototype(entry);
    if (!pProto)
    {
        WorldPacket data(GetOpcode("SMSG_ITEM_QUERY_SINGLE_RESPONSE"), 4);
        data << uint32(entry | 0x80000000);
        SendPacket(data);
        printf("Client requested info about unknown item id %u!\n", entry);
        return;
    }

    WorldPacket data(GetOpcode("SMSG_ITEM_QUERY_SINGLE_RESPONSE"), 600);
    data << pProto->ItemId;
    data << pProto->Class;
    data << pProto->SubClass;
    if (GetClientBuild() >= CLIENT_BUILD_2_0_3)
        data << pProto->SoundOverrideSubclass;
    data << pProto->Name1;                              // max length of any of 4 names: 256 bytes
    data << uint8(0x00);                                //pProto->Name2; // blizz not send name there, just uint8(0x00); <-- \0 = empty string = empty name...
    data << uint8(0x00);                                //pProto->Name3; // blizz not send name there, just uint8(0x00);
    data << uint8(0x00);                                //pProto->Name4; // blizz not send name there, just uint8(0x00);
    data << pProto->DisplayInfoID;
    data << pProto->Quality;
    data << pProto->Flags;
    if (GetClientBuild() >= CLIENT_BUILD_3_2_0)
        data << pProto->Flags2;
    data << pProto->BuyPrice;
    data << pProto->SellPrice;
    data << pProto->InventoryType;
    data << pProto->AllowableClass;
    data << pProto->AllowableRace;
    data << pProto->ItemLevel;
    data << pProto->RequiredLevel;
    data << pProto->RequiredSkill;
    data << pProto->RequiredSkillRank;
    data << pProto->RequiredSpell;
    data << pProto->RequiredHonorRank;
    data << pProto->RequiredCityRank;
    data << pProto->RequiredReputationFaction;
    data << (pProto->RequiredReputationFaction > 0 ? pProto->RequiredReputationRank : 0);   // send value only if reputation faction id setted (needed for some items)
    data << pProto->MaxCount;
    data << pProto->Stackable;
    data << pProto->ContainerSlots;

    uint32 statFieldsCount = MAX_ITEM_PROTO_STATS;
    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
    {
        data << pProto->StatsCount;
        statFieldsCount = pProto->StatsCount;
    }

    for (uint32 i = 0; i < statFieldsCount; ++i)
    {
        data << pProto->ItemStat[i].ItemStatType;
        data << pProto->ItemStat[i].ItemStatValue;
    }

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
    {
        data << pProto->ScalingStatDistribution;
        data << pProto->ScalingStatValue;
    }

    uint32 damageFieldsCount = (GetClientBuild() >= CLIENT_BUILD_3_1_0)  ? MAX_ITEM_PROTO_DAMAGES_WOTLK : MAX_ITEM_PROTO_DAMAGES_VANILLA;
    for (uint32 i = 0; i < damageFieldsCount; ++i)
    {
        data << pProto->Damage[i].DamageMin;
        data << pProto->Damage[i].DamageMax;
        data << pProto->Damage[i].DamageType;
    }

    // resistances (7)
    data << pProto->Armor;
    data << pProto->HolyRes;
    data << pProto->FireRes;
    data << pProto->NatureRes;
    data << pProto->FrostRes;
    data << pProto->ShadowRes;
    data << pProto->ArcaneRes;

    data << pProto->Delay;
    data << pProto->AmmoType;
    data << pProto->RangedModRange;

    for (auto const& itr : pProto->Spells)
    {
        data << itr.SpellId;
        data << itr.SpellTrigger;
        data << itr.SpellCharges;

        data << uint32(itr.SpellCooldown);
        data << uint32(itr.SpellCategory);
        data << uint32(itr.SpellCategoryCooldown);
    }
    data << pProto->Bonding;
    data << pProto->Description;
    data << pProto->PageText;
    data << pProto->LanguageID;
    data << pProto->PageMaterial;
    data << pProto->StartQuest;
    data << pProto->LockID;
    data << pProto->Material;
    data << pProto->Sheath;
    data << pProto->RandomProperty;

    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << pProto->RandomSuffix;

    data << pProto->Block;
    data << pProto->ItemSet;
    data << pProto->MaxDurability;
    data << pProto->Area;
    data << pProto->Map;
    data << pProto->BagFamily;

    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
    {
        data << pProto->TotemCategory;
        for (int s = 0; s < MAX_ITEM_PROTO_SOCKETS; ++s)
        {
            data << pProto->Socket[s].Color;
            data << pProto->Socket[s].Content;
        }
        data << uint32(pProto->socketBonus);
        data << uint32(pProto->GemProperties);
        data << int32(pProto->RequiredDisenchantSkill);
        data << float(pProto->ArmorDamageModifier);
    }

    if (GetClientBuild() >= CLIENT_BUILD_2_4_2)
        data << uint32(pProto->Duration);

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        data << pProto->ItemLimitCategory;

    if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
        data << pProto->HolidayId;

    SendPacket(data);
}

void WorldServer::SendItemNameQueryResponse(uint32 entry)
{
    ItemPrototype const* pProto = sGameDataMgr.GetItemPrototype(entry);
    if (!pProto)
    {
        printf("Client requested info about unknown item id %u!\n", entry);
        return;
    }

    WorldPacket data(GetOpcode("SMSG_ITEM_NAME_QUERY_RESPONSE"), (4 + 10));
    data << uint32(pProto->ItemId);
    data << pProto->Name1;
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << uint32(pProto->InventoryType);
    SendPacket(data);
}

void WorldServer::SendInspect(ObjectGuid guid)
{
    WorldPacket data(GetOpcode("SMSG_INSPECT"), 8);
    data << ObjectGuid(guid);
    SendPacket(data);
}

void WorldServer::SendInspectTalent(ObjectGuid guid)
{
    if (GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        uint32 talentPointsCount = 0;
        WorldPacket data(GetOpcode("SMSG_INSPECT_TALENT"), 4 + talentPointsCount);
        data << guid.WriteAsPacked();
        data << uint32(talentPointsCount);
        for (uint32 i = 0; i < talentPointsCount; ++i)
            data << uint8(0);
        SendPacket(data);
    }
    else
    {
        WorldPacket data(GetOpcode("SMSG_INSPECT_TALENT"), 50);
        data << guid.WriteAsPacked();
        data << uint32(0); // unspentTalentPoints
        data << uint8(0); // talentGroupCount
        data << uint8(0); // talentGroupIndex

        uint32 slotUsedMask = 0;
        size_t slotUsedMaskPos = data.wpos();
        data << uint32(slotUsedMask); // slotUsedMask < 0x80000

        if (Player const* pPlayer = FindPlayer(guid))
        {
            for (uint32 i = 0; i < EQUIPMENT_SLOT_END; ++i)
            {
                uint32 itemId = pPlayer->GetVisibleItemId(i);
                if (!itemId)
                    continue;

                slotUsedMask |= (1 << i);

                data << uint32(itemId);

                uint32 enchantId = pPlayer->GetVisibleItemEnchant(i);
                uint16 enchantmentMask = enchantId ? (1 << WotLK::PERM_ENCHANTMENT_SLOT) : 0;
                data << uint16(enchantmentMask);

                if (enchantId)
                    data << uint16(enchantId);

                data << uint16(0); // random property id
                data << ObjectGuid().WriteAsPacked(); // creator
                data << uint32(0); // suffix factor
            }

            data.put<uint32>(slotUsedMaskPos, slotUsedMask);
        }

        SendPacket(data);
    }
}

void WorldServer::TeleportClient(uint32 mapId, float x, float y, float z, float o)
{
    WorldLocation location(mapId, x, y, z, o);
    TeleportClient(location);
}

void WorldServer::TeleportClient(WorldLocation const& location)
{
    if (!m_clientPlayer)
    {
        printf("[TeleportClient] Error: Attempt to teleport client but he is not in world!\n");
        return;
    }

    m_sessionData.isTeleportPending = true;
    m_sessionData.pendingTeleportLocation = location;

    if (m_clientPlayer->GetMapId() != location.mapId)
    {
        SendTransferPending(location.mapId);
        SendNewWorld(location);
    }
    else
    {
        SendMoveTeleportAck(location.x, location.y, location.z, location.o);
    }
}

void WorldServer::SendTransferPending(uint32 mapId)
{
    WorldPacket data(GetOpcode("SMSG_TRANSFER_PENDING"), 4);
    data << uint32(mapId);
    SendPacket(data);
}

void WorldServer::SendNewWorld(WorldLocation const& location)
{
    WorldPacket data(GetOpcode("SMSG_NEW_WORLD"), 20);
    data << uint32(location.mapId);
    data << float(location.x);
    data << float(location.y);
    data << float(location.z);
    data << float(location.o);
    SendPacket(data);
}

void WorldServer::SendMoveTeleportAck(float x, float y, float z, float o)
{
    if (!m_clientPlayer)
    {
        printf("[SendMoveTeleportAck] Error: Attempt to teleport client but he is not in world!\n");
        return;
    }

    MovementInfo mi = m_clientPlayer->GetMovementInfo();
    mi.UpdateTime(sWorld.GetServerTimeMs());
    mi.ChangePosition(x, y, z, o);

    WorldPacket data(GetOpcode("MSG_MOVE_TELEPORT_ACK"), 41);
    data << m_clientPlayer->GetPackGUID();
    data << m_sessionData.movementCounter;
    data << mi;
    SendPacket(data);
}

void WorldServer::SendPacketsBeforeAddToMap(Player const* pPlayer)
{
    if (GetClientBuild() < CLIENT_BUILD_3_0_2)
        SendSetRestStart(0);
    SendBindPointUpdate(pPlayer->GetLocation(), pPlayer->GetZoneId());
    SendTutorialFlags();
    SendInitialSpells(pPlayer->GetRace(), pPlayer->GetClass());
    SendLoginSetTimeSpeed();
    SendActionButtons(pPlayer->GetRace(), pPlayer->GetClass());
}

void WorldServer::SendPacketsAfterAddToMap()
{
    m_clientPlayer->SendCreateUpdateToPlayer(m_clientPlayer.get());

    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
    {
        SendTimeSyncRequest();
        SendInitialWorldStates(sReplayMgr.GetInitialWorldStatesForCurrentTime());
    }
}

void WorldServer::SendChatPacket(uint32 msgtype, char const* message, uint32 language /*= LANG_UNIVERSAL*/, uint32 chatTag /*= CHAT_TAG_NONE*/,
                                  ObjectGuid const& senderGuid /*= ObjectGuid()*/, char const* senderName /*= nullptr*/,
                                  ObjectGuid const& targetGuid /*= ObjectGuid()*/, char const* targetName /*= nullptr*/,
                                  char const* channelName /*= nullptr*/, uint8 playerRank /*= 0*/)
{
    WorldPacket data;
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        data.Initialize(GetOpcode("SMSG_MESSAGECHAT"));
        data << uint8(msgtype);
        data << uint32(language);

        switch (msgtype)
        {
            case Vanilla::CHAT_MSG_MONSTER_WHISPER:
            //case CHAT_MSG_RAID_BOSS_WHISPER:
            case Vanilla::CHAT_MSG_RAID_BOSS_EMOTE:
            case Vanilla::CHAT_MSG_MONSTER_EMOTE:
                assert(senderName);
                data << uint32(strlen(senderName) + 1);
                data << senderName;
                data << ObjectGuid(targetGuid);
                break;

            case Vanilla::CHAT_MSG_SAY:
            case Vanilla::CHAT_MSG_PARTY:
            case Vanilla::CHAT_MSG_YELL:
                data << ObjectGuid(senderGuid);
                data << ObjectGuid(senderGuid);
                break;

            case Vanilla::CHAT_MSG_MONSTER_SAY:
            case Vanilla::CHAT_MSG_MONSTER_YELL:
                assert(senderName);
                data << ObjectGuid(senderGuid);
                data << uint32(strlen(senderName) + 1);
                data << senderName;
                data << ObjectGuid(targetGuid);
                break;

            case Vanilla::CHAT_MSG_CHANNEL:
                assert(channelName);
                data << channelName;
                data << uint32(playerRank);
                data << ObjectGuid(senderGuid);
                break;

            default:
                data << ObjectGuid(senderGuid);
                break;
        }

        assert(message);
        data << uint32(strlen(message) + 1);
        data << message;
        data << uint8(chatTag);
    }
    else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        const bool isGM = false;

        data.Initialize(isGM ? GetOpcode("SMSG_GM_MESSAGECHAT") : GetOpcode("SMSG_MESSAGECHAT"));
        data << uint8(msgtype);
        data << uint32(language);
        data << ObjectGuid(senderGuid);
        data << uint32(0);                                              // 2.1.0

        switch (msgtype)
        {
            case TBC::CHAT_MSG_MONSTER_SAY:
            case TBC::CHAT_MSG_MONSTER_PARTY:
            case TBC::CHAT_MSG_MONSTER_YELL:
            case TBC::CHAT_MSG_MONSTER_WHISPER:
            case TBC::CHAT_MSG_MONSTER_EMOTE:
            case TBC::CHAT_MSG_RAID_BOSS_WHISPER:
            case TBC::CHAT_MSG_RAID_BOSS_EMOTE:
            case TBC::CHAT_MSG_WHISPER_FOREIGN:
                assert(senderName);
                data << uint32(strlen(senderName) + 1);
                data << senderName;
                data << ObjectGuid(targetGuid);                         // Unit Target
                if (targetGuid && !targetGuid.IsPlayer() && !targetGuid.IsPet() && (msgtype != TBC::CHAT_MSG_WHISPER_FOREIGN))
                {
                    data << uint32(strlen(targetName) + 1);             // target name length
                    data << targetName;                                 // target name
                }
                assert(message);
                data << uint32(strlen(message) + 1);
                data << message;
                data << uint8(chatTag);
                break;
            case TBC::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            case TBC::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            case TBC::CHAT_MSG_BG_SYSTEM_HORDE:
                data << ObjectGuid(targetGuid);                         // Unit Target
                if (targetGuid && !targetGuid.IsPlayer())
                {
                    assert(targetName);
                    data << uint32(strlen(targetName) + 1);             // target name length
                    data << targetName;                                 // target name
                }
                assert(message);
                data << uint32(strlen(message) + 1);
                data << message;
                data << uint8(chatTag);
                break;
            default:
                if (msgtype == TBC::CHAT_MSG_CHANNEL)
                {
                    assert(channelName);
                    data << channelName;
                }
                data << ObjectGuid(targetGuid);
                assert(message);
                data << uint32(strlen(message) + 1);
                data << message;
                data << uint8(chatTag);
                if (isGM)
                {
                    assert(senderName);
                    data << uint32(strlen(senderName) + 1);
                    data << senderName;
                }
                break;
        }
    }
    else
    {
        const bool isGM = false;
        bool isAchievement = false;
        uint32 achievementId = 0;

        data.Initialize(isGM ? GetOpcode("SMSG_GM_MESSAGECHAT") : GetOpcode("SMSG_MESSAGECHAT"));
        data << uint8(msgtype);
        data << uint32(language);
        data << ObjectGuid(senderGuid);
        data << uint32(0);                                              // 2.1.0

        switch (msgtype)
        {
            case WotLK::CHAT_MSG_MONSTER_SAY:
            case WotLK::CHAT_MSG_MONSTER_PARTY:
            case WotLK::CHAT_MSG_MONSTER_YELL:
            case WotLK::CHAT_MSG_MONSTER_WHISPER:
            case WotLK::CHAT_MSG_MONSTER_EMOTE:
            case WotLK::CHAT_MSG_RAID_BOSS_WHISPER:
            case WotLK::CHAT_MSG_RAID_BOSS_EMOTE:
            case WotLK::CHAT_MSG_BNET:
            case WotLK::CHAT_MSG_WHISPER_FOREIGN:
                assert(senderName);
                data << uint32(strlen(senderName) + 1);
                data << senderName;
                data << ObjectGuid(targetGuid);                         // Unit Target
                if (targetGuid && !targetGuid.IsPlayer() && !targetGuid.IsPet() && (msgtype != WotLK::CHAT_MSG_WHISPER_FOREIGN))
                {
                    data << uint32(strlen(targetName) + 1);             // target name length
                    data << targetName;                                 // target name
                }
                break;
            case WotLK::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            case WotLK::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            case WotLK::CHAT_MSG_BG_SYSTEM_HORDE:
                data << ObjectGuid(targetGuid);                         // Unit Target
                if (targetGuid && !targetGuid.IsPlayer())
                {
                    assert(targetName);
                    data << uint32(strlen(targetName) + 1);             // target name length
                    data << targetName;                                 // target name
                }
                break;
            case WotLK::CHAT_MSG_ACHIEVEMENT:
            case WotLK::CHAT_MSG_GUILD_ACHIEVEMENT:
                data << ObjectGuid(targetGuid);                         // Unit Target
                isAchievement = true;
                break;
            default:
                if (isGM)
                {
                    assert(senderName);
                    data << uint32(strlen(senderName) + 1);
                    data << senderName;
                }

                if (msgtype == WotLK::CHAT_MSG_CHANNEL)
                {
                    assert(channelName);
                    data << channelName;
                }
                data << ObjectGuid(targetGuid);
                break;
        }
        assert(message);
        data << uint32(strlen(message) + 1);
        data << message;
        data << uint8(chatTag);

        if (isAchievement)
            data << uint32(achievementId);
    }
    SendPacket(data);
}

void WorldServer::PSendSysMessage(char const* format, ...)
{
    va_list ap;
    char str[2048];
    va_start(ap, format);
    vsnprintf(str, 2048, format, ap);
    va_end(ap);
    SendSysMessage(str);
}

void WorldServer::SendSysMessage(char const* str)
{
    if (!m_sessionData.isInWorld)
        return;

    uint32 msgType;
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        msgType = Vanilla::CHAT_MSG_SYSTEM;
    else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
        msgType = TBC::CHAT_MSG_SYSTEM;
    else
        msgType = WotLK::CHAT_MSG_SYSTEM;

    SendChatPacket(msgType, str);
}

void WorldServer::SendQuestQueryResponse(uint32 entry)
{
    Quest const* pQuest = sGameDataMgr.GetQuestTemplate(entry);
    if (!pQuest)
    {
        printf("Client requested info about unknown quest id %u!\n", entry);
        return;
    }

    WorldPacket data(GetOpcode("SMSG_QUEST_QUERY_RESPONSE"), 100);       // guess size

    data << uint32(pQuest->GetQuestId());                   // quest id
    data << uint32(pQuest->GetQuestMethod());               // Accepted values: 0, 1 or 2. 0==IsAutoComplete() (skip objectives/details)
    data << uint32(pQuest->GetQuestLevel());                // may be 0, static data, in other cases must be used dynamic level: Player::GetQuestLevelForPlayer
    if (GetClientBuild() > CLIENT_BUILD_3_0_2)
        data << uint32(pQuest->GetMinLevel());              // min required level to obtain (added for 3.3). Assumed allowed (database) range is -1 to 255 (still using uint32, since negative value would not be of any known use for client)
    data << uint32(pQuest->GetZoneOrSort());                // zone or sort to display in quest log

    data << uint32(pQuest->GetType());
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << uint32(pQuest->GetSuggestedPlayers());

    data << uint32(pQuest->GetRepObjectiveFaction());       // shown in quest log as part of quest objective
    data << uint32(pQuest->GetRepObjectiveValue());         // shown in quest log as part of quest objective

    data << uint32(0);                                      // RequiredOpositeRepFaction
    data << uint32(0);                                      // RequiredOpositeRepValue, required faction value with another (oposite) faction (objective)

    data << uint32(pQuest->GetNextQuestInChain());          // client will request this quest from NPC, if not 0
    if (GetClientBuild() > CLIENT_BUILD_3_0_2)
        data << uint32(pQuest->GetRewXPId());               // column index in QuestXP.dbc (row based on quest level)

    if (pQuest->HasQuestFlag(QUEST_FLAGS_HIDDEN_REWARDS))
        data << uint32(0);                                  // Hide money rewarded
    else
        data << uint32(pQuest->GetRewOrReqMoney());


    data << uint32(pQuest->GetRewMoneyMaxLevel());          // used in XP calculation at client

    data << uint32(pQuest->GetRewSpell());                  // reward spell, this spell will display (icon) (casted if RewSpellCast==0)
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
    {
        data << uint32(pQuest->GetRewSpellCast());          // casted spell
        data << uint32(pQuest->GetRewHonorableKills());
    }

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        data << float(pQuest->GetRewHonorMultiplier());     // new reward honor (multiplied by ~62 at client side)
    
    data << uint32(pQuest->GetSrcItemId());                 // source item id
    data << uint32(pQuest->GetQuestFlags());                // quest flags
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << uint32(pQuest->GetCharTitleId());           // CharTitleId, new 2.4.0, player gets this title (id from CharTitles)

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
    {
        data << uint32(pQuest->GetPlayersSlain());          // players slain
        data << uint32(pQuest->GetBonusTalents());          // bonus talents
        data << uint32(0);                                  // bonus arena points
        data << uint32(0);                                  // rew rep show mask?
    }

    int iI;

    if (pQuest->HasQuestFlag(QUEST_FLAGS_HIDDEN_REWARDS))
    {
        for (iI = 0; iI < QUEST_REWARDS_COUNT; ++iI)
            data << uint32(0) << uint32(0);
        for (iI = 0; iI < QUEST_REWARD_CHOICES_COUNT; ++iI)
            data << uint32(0) << uint32(0);
    }
    else
    {
        for (iI = 0; iI < QUEST_REWARDS_COUNT; ++iI)
        {
            data << uint32(pQuest->RewItemId[iI]);
            data << uint32(pQuest->RewItemCount[iI]);
        }
        for (iI = 0; iI < QUEST_REWARD_CHOICES_COUNT; ++iI)
        {
            data << uint32(pQuest->RewChoiceItemId[iI]);
            data << uint32(pQuest->RewChoiceItemCount[iI]);
        }
    }

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
    {
        for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)   // reward factions ids
        {
            data << uint32(pQuest->RewRepFaction[i]);
        }

        for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)   // columnid in QuestFactionReward.dbc (if negative, from second row)
        {
            data << int32(pQuest->RewRepValueId[i]);
        }

        for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)   // reward reputation override. No bonus is expected given
        {
            data << int32(0);
        }
    }

    data << pQuest->GetPointMapId();
    data << pQuest->GetPointX();
    data << pQuest->GetPointY();
    data << pQuest->GetPointOpt();

    data << pQuest->GetTitle();
    data << pQuest->GetObjectives();
    data << pQuest->GetDetails();
    data << pQuest->GetEndText();
    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        data << pQuest->GetCompletedText();                 // display in quest objectives window once all objectives are completed

    for (iI = 0; iI < QUEST_OBJECTIVES_COUNT; ++iI)
    {
        if (pQuest->ReqCreatureOrGOId[iI] < 0)
        {
            // client expected gameobject template id in form (id|0x80000000)
            data << uint32((pQuest->ReqCreatureOrGOId[iI] * (-1)) | 0x80000000);
        }
        else
            data << uint32(pQuest->ReqCreatureOrGOId[iI]);
        data << uint32(pQuest->ReqCreatureOrGOCount[iI]);

        if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        {
            data << uint32(pQuest->ReqSourceId[iI]);
            data << uint32(0);                              // req source count?
        }

        data << uint32(pQuest->ReqItemId[iI]);
        data << uint32(pQuest->ReqItemCount[iI]);
    }

    for (iI = 0; iI < QUEST_OBJECTIVES_COUNT; ++iI)
        data << pQuest->ObjectiveText[iI];

    SendPacket(data);
}

void WorldServer::SendCreatureQueryResponse(uint32 entry)
{
    CreatureTemplate const* pCreature = sGameDataMgr.GetCreatureTemplate(entry);
    if (!pCreature)
    {
        WorldPacket data(GetOpcode("SMSG_CREATURE_QUERY_RESPONSE"), 4);
        data << uint32(entry | 0x80000000);
        SendPacket(data);
        printf("Client requested info about unknown creature id %u!\n", entry);
        return;
    }

    WorldPacket data(GetOpcode("SMSG_CREATURE_QUERY_RESPONSE"), 100);
    data << uint32(pCreature->entry);
    data << pCreature->name;
    data << uint8(0) << uint8(0) << uint8(0); // name2, name3, name4, always empty
    data << pCreature->subName;
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << pCreature->iconName;
    data << uint32(pCreature->typeFlags);
    data << uint32(pCreature->type);
    data << uint32(pCreature->family);
    data << uint32(pCreature->rank);

    if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
    {
        data << uint32(pCreature->killCredit[0]);
        data << uint32(pCreature->killCredit[1]);
    }
    else
    {
        if (GetClientBuild() < CLIENT_BUILD_3_0_2)
            data << uint32(0); // unknown
        data << uint32(pCreature->petSpellDataId);
    }

    uint32 displayIdCount = (GetClientBuild() >= CLIENT_BUILD_2_0_1) ? MAX_CREATURE_MODEL : 1;
    for (uint32 i = 0; i < displayIdCount; ++i)
    {
        data << uint32(pCreature->displayId[i]);
    }

    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
    {
        data << float(pCreature->healthMultiplier);
        data << float(pCreature->powerMultiplier);
    }
    else
        data << uint8(pCreature->civilian);

    data << uint8(pCreature->racialLeader);

    if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
    {
        uint32 questItemsCount = GetClientBuild() >= CLIENT_BUILD_3_2_0 ? 6 : 4;
        for (uint32 i = 0; i < questItemsCount; ++i)
        {
            data << uint32(pCreature->questItem[i]);
        }
        data << uint32(pCreature->movementTemplateId);
    }

    SendPacket(data);
}

void WorldServer::SendGameObjectQueryResponse(uint32 entry)
{
    GameObjectTemplate const* pGo = sGameDataMgr.GetGameObjectTemplate(entry);
    if (!pGo)
    {
        WorldPacket data(GetOpcode("SMSG_GAMEOBJECT_QUERY_RESPONSE"), 4);
        data << uint32(entry | 0x80000000);
        SendPacket(data);
        printf("Client requested info about unknown gameobject id %u!\n", entry);
        return;
    }

    WorldPacket data(GetOpcode("SMSG_GAMEOBJECT_QUERY_RESPONSE"), 150);
    data << uint32(pGo->entry);
    data << uint32(pGo->type);
    data << uint32(pGo->displayId);
    data << pGo->name;
    data << uint8(0) << uint8(0) << uint8(0);   // name2, name3, name4
    if (GetClientBuild() >= CLIENT_BUILD_2_0_3)
    {
        data << pGo->iconName;
        data << pGo->castBarCaption;
    }
    data << pGo->unkString;                     // one more name, client handles it a bit differently
    data.append(pGo->data, 24);                 // these are read as int32

    if (GetClientBuild() >= CLIENT_BUILD_2_4_3)
        data << float(pGo->scale);

    if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
    {
        uint32 questItemsCount = (GetClientBuild() >= CLIENT_BUILD_3_2_0) ? MAX_GAMEOBJECT_QUEST_ITEMS : 4;
        for (uint32 i = 0; i < questItemsCount; ++i)
        {
            data << uint32(pGo->questItems[i]);
        }
    }
    
    SendPacket(data);
}

static char const* const moveTypeToSetSpeedOpcode[MAX_MOVE_TYPE_WOTLK] =
{
    "MSG_MOVE_SET_WALK_SPEED",
    "MSG_MOVE_SET_RUN_SPEED",
    "MSG_MOVE_SET_RUN_BACK_SPEED",
    "MSG_MOVE_SET_SWIM_SPEED",
    "MSG_MOVE_SET_SWIM_BACK_SPEED",
    "MSG_MOVE_SET_TURN_RATE",
    "MSG_MOVE_SET_FLIGHT_SPEED",
    "MSG_MOVE_SET_FLIGHT_BACK_SPEED",
    "MSG_MOVE_SET_PITCH_RATE",
};

void WorldServer::SendSetSpeed(Unit const* pUnit, uint32 moveType, float speed)
{
    if (moveType >= MAX_MOVE_TYPE_WOTLK)
    {
        printf("[SendSplineSetSpeed] Wrong speed type %u used!\n", moveType);
        return;
    }

    if (uint16 opcode = GetOpcode(moveTypeToSetSpeedOpcode[moveType]))
    {
        WorldPacket data(opcode, 8 + 4);
        data << pUnit->GetPackGUID();
        data << pUnit->GetMovementInfo();
        data << float(speed);
        SendPacket(data);
    }
}

static char const* const moveTypeToSplineSetSpeedOpcode[MAX_MOVE_TYPE_WOTLK] =
{
    "SMSG_SPLINE_SET_WALK_SPEED",
    "SMSG_SPLINE_SET_RUN_SPEED",
    "SMSG_SPLINE_SET_RUN_BACK_SPEED",
    "SMSG_SPLINE_SET_SWIM_SPEED",
    "SMSG_SPLINE_SET_SWIM_BACK_SPEED",
    "SMSG_SPLINE_SET_TURN_RATE",
    "SMSG_SPLINE_SET_FLIGHT_SPEED",
    "SMSG_SPLINE_SET_FLIGHT_BACK_SPEED",
    "SMSG_SPLINE_SET_PITCH_RATE",
};

void WorldServer::SendSplineSetSpeed(ObjectGuid guid, uint32 moveType, float speed)
{
    if (moveType >= MAX_MOVE_TYPE_WOTLK)
    {
        printf("[SendSplineSetSpeed] Wrong speed type %u used!\n", moveType);
        return;
    }

    if (uint16 opcode = GetOpcode(moveTypeToSplineSetSpeedOpcode[moveType]))
    {
        WorldPacket data(opcode, 8 + 4);
        data << guid.WriteAsPacked();
        data << float(speed);
        SendPacket(data);
    }
}

void WorldServer::SendMovementPacket(Unit* pUnit, uint16 opcode)
{
    WorldPacket data(opcode);
    data << pUnit->GetPackGUID();
    data << pUnit->GetMovementInfo();
    SendPacket(data);
}

void WorldServer::SendMoveSetCanFly(Unit* pUnit)
{
    WorldPacket data(GetOpcode("SMSG_MOVE_SET_CAN_FLY"), 12);
    data << pUnit->GetPackGUID();
    data << uint32(0); // movement counter
    SendPacket(data);
}

void WorldServer::SendMoveUnsetCanFly(Unit* pUnit)
{
    WorldPacket data(GetOpcode("SMSG_MOVE_UNSET_CAN_FLY"), 12);
    data << pUnit->GetPackGUID();
    data << uint32(0); // movement counter
    SendPacket(data);
}

void WorldServer::SendQuestGiverStatus(ObjectGuid guid, uint32 dialogStatus)
{
    WorldPacket data(GetOpcode("SMSG_QUESTGIVER_STATUS"), 8 + 4);
    data << ObjectGuid(guid);
    data << uint32(dialogStatus);
    SendPacket(data);
}

void WorldServer::SendRaidInstanceInfo()
{
    WorldPacket data(GetOpcode("SMSG_RAID_INSTANCE_INFO"), 4);
    data << uint32(0); // count
    SendPacket(data);
}

void WorldServer::SendQueryNextMailTimeResponse()
{
    WorldPacket data(GetOpcode("MSG_QUERY_NEXT_MAIL_TIME"), 8);
    data << uint32(0xC7A8C000);
    if (GetClientBuild() >= CLIENT_BUILD_2_3_0)
        data << uint32(0x00000000);
    SendPacket(data);
}

void WorldServer::SendLfgPlayerInfo()
{
    WorldPacket data(GetOpcode("SMSG_LFG_PLAYER_INFO"), 8);
    data << uint8(0); // dungeon count
    data << uint32(0); // locked count
    SendPacket(data);
}

void WorldServer::SendSpellCastStart(uint32 spellId, uint32 castTime, uint32 castFlags, ObjectGuid casterGuid, ObjectGuid unitCasterGuid, WorldObject const* pTarget, uint32 ammoDisplayId, uint32 ammoInventoryType)
{
    SpellCastTargets targets;
    if (Unit const* pUnitTarget = pTarget->ToUnit())
        targets.setUnitTarget(pUnitTarget);
    else if (GameObject const* pGoTarget = pTarget->ToGameObject())
        targets.setGOTarget(pGoTarget);

    SendSpellCastStart(spellId, castTime, castFlags, casterGuid, unitCasterGuid, targets, ammoDisplayId, ammoInventoryType);
}

void WorldServer::SendSpellCastStart(uint32 spellId, uint32 castTime, uint32 castFlags, ObjectGuid casterGuid, ObjectGuid unitCasterGuid, SpellCastTargets const& targets, uint32 ammoDisplayId, uint32 ammoInventoryType)
{
    WorldPacket data(GetOpcode("SMSG_SPELL_START"), (8 + 8 + 4 + 2 + 4));
    data << casterGuid.WriteAsPacked();
    data << unitCasterGuid.WriteAsPacked();

    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        data << uint32(spellId);
        data << uint16(castFlags);
    }
    else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        data << uint32(spellId);
        data << uint8(0); // cast count
        data << uint16(castFlags);
    }
    else
    {
        data << uint8(0); // cast count
        data << uint32(spellId);
        data << uint32(castFlags);
    }

    data << uint32(castTime);
    data << targets;

    if (castFlags & CAST_FLAG_AMMO)                         // projectile info
    {
        data << uint32(ammoDisplayId);
        data << uint32(ammoInventoryType);
    }

    SendPacket(data);
}

void WorldServer::SendCastResult(uint32 spellId, uint32 result, uint32 reason)
{
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        WorldPacket data(GetOpcode("SMSG_CAST_RESULT"), (4 + 1 + 1));
        data << uint32(spellId);
        data << uint8(result);
        if (result == 2)
            data << uint8(reason);

        SendPacket(data);
    }
    else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        if (result == 0)
            return;

        WorldPacket data(GetOpcode("SMSG_CAST_RESULT"), (4 + 1 + 2));                              // single cast or multi 2.3 (0/1)
        data << uint32(spellId);
        data << uint8(reason);
        data << uint8(0); // single cast or multi 2.3 (0/1)
        switch (reason)
        {
            case TBC::SPELL_FAILED_REQUIRES_SPELL_FOCUS:
                data << uint32(1);
                break;
            case TBC::SPELL_FAILED_REQUIRES_AREA:
                // hardcode areas limitation case
                switch (spellId)
                {
                    case 41617:                                 // Cenarion Mana Salve
                    case 41619:                                 // Cenarion Healing Salve
                        data << uint32(3905);
                        break;
                    case 41618:                                 // Bottled Nethergon Energy
                    case 41620:                                 // Bottled Nethergon Vapor
                        data << uint32(3842);
                        break;
                    case 45373:                                 // Bloodberry Elixir
                        data << uint32(4075);
                        break;
                    default:                                    // default case
                        data << uint32(0);
                        break;
                }
                break;
            case TBC::SPELL_FAILED_TOTEMS:
                /*
                for (uint32 i : spellInfo->Totem)
                    if (i)
                        data << uint32(i);
                        */
                break;
            case TBC::SPELL_FAILED_TOTEM_CATEGORY:
                /*
                for (uint32 i : spellInfo->TotemCategory)
                    if (i)
                        data << uint32(i);;
                        */
                break;
            case TBC::SPELL_FAILED_EQUIPPED_ITEM_CLASS:
                data << uint32(0); // EquippedItemClass
                data << uint32(0); // EquippedItemSubClassMask
                data << uint32(0); // EquippedItemInventoryTypeMask
                break;
            default:
                break;
        }
        SendPacket(data);
    }
    else
    {
        if (result == 0)
            return;

        WorldPacket data(GetOpcode("SMSG_CAST_RESULT"), (4 + 1 + 2));
        data << uint8(0); // single cast or multi 2.3 (0/1)
        data << uint32(spellId);
        data << uint8(reason);
        switch (reason)
        {
            case WotLK::SPELL_FAILED_NOT_READY:
                data << uint32(0);                              // unknown, value 1 seen for 14177 (update cooldowns on client flag)
                break;
            case WotLK::SPELL_FAILED_REQUIRES_SPELL_FOCUS:
                data << uint32(1);                              // SpellFocusObject.dbc id
                break;
            case WotLK::SPELL_FAILED_REQUIRES_AREA:             // AreaTable.dbc id
                // hardcode areas limitation case
                switch (spellId)
                {
                    case 41617:                                 // Cenarion Mana Salve
                    case 41619:                                 // Cenarion Healing Salve
                        data << uint32(3905);
                        break;
                    case 41618:                                 // Bottled Nethergon Energy
                    case 41620:                                 // Bottled Nethergon Vapor
                        data << uint32(3842);
                        break;
                    case 45373:                                 // Bloodberry Elixir
                        data << uint32(4075);
                        break;
                    default:                                    // default case (don't must be)
                        data << uint32(0);
                        break;
                }
                break;
            case WotLK::SPELL_FAILED_TOTEMS:
                /*
                for (unsigned int i : spellInfo->Totem)
                    if (i)
                        data << uint32(i);    // client needs only one id, not 2...
                */
                break;
            case WotLK::SPELL_FAILED_TOTEM_CATEGORY:
                /*
                for (unsigned int i : spellInfo->TotemCategory)
                    if (i)
                        data << uint32(i);// client needs only one id, not 2...
                */
                break;
            case WotLK::SPELL_FAILED_EQUIPPED_ITEM_CLASS:
            case WotLK::SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND:
            case WotLK::SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND:
                data << uint32(0); // EquippedItemClass
                data << uint32(0); // EquippedItemSubClassMask
                break;
            case WotLK::SPELL_FAILED_PREVENTED_BY_MECHANIC:
                data << uint32(0);                              // SpellMechanic.dbc id
                break;
            case WotLK::SPELL_FAILED_CUSTOM_ERROR:
                data << uint32(0);                              // custom error id (see enum SpellCastResultCustom)
                break;
            case WotLK::SPELL_FAILED_NEED_EXOTIC_AMMO:
                data << uint32(0);                              // EquippedItemSubClassMask
                break;
            case WotLK::SPELL_FAILED_REAGENTS:
                data << uint32(0);                              // item id
                break;
            case WotLK::SPELL_FAILED_NEED_MORE_ITEMS:
                data << uint32(0);                              // item id
                data << uint32(0);                              // item count?
                break;
            case WotLK::SPELL_FAILED_MIN_SKILL:
                data << uint32(0);                              // SkillLine.dbc id
                data << uint32(0);                              // required skill value
                break;
            case WotLK::SPELL_FAILED_TOO_MANY_OF_ITEM:
                data << uint32(0);                              // ItemLimitCategory.dbc id
                break;
            case WotLK::SPELL_FAILED_FISHING_TOO_LOW:
                data << uint32(0);                              // required fishing skill
                break;
            default:
                break;
        }
        SendPacket(data);
    }
}

void WorldServer::SendSpellCastGo(uint32 spellId, uint32 castFlags, ObjectGuid casterGuid, ObjectGuid unitCasterGuid, SpellCastTargets const& targets, std::vector<std::pair<ObjectGuid, uint8>> const& vHitTargets, std::vector<std::pair<ObjectGuid, uint8>> const& vMissTargets, uint32 ammoDisplayId, uint32 ammoInventoryType)
{
    WorldPacket data(GetOpcode("SMSG_SPELL_GO"), 53);
    data << casterGuid.WriteAsPacked();
    data << unitCasterGuid.WriteAsPacked();

    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        data << uint32(spellId);
        data << uint16(castFlags);
    }
    else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        data << uint32(spellId);
        data << uint16(castFlags);
        data << uint32(GetServerTimeMs());
    }
    else
    {
        data << uint8(0); // cast count
        data << uint32(spellId);
        data << uint32(castFlags);
        data << uint32(GetServerTimeMs());
    }

    data << uint8(vHitTargets.size());
    for (auto const& itr : vHitTargets)
    {
        data << itr.first;
    }

    data << uint8(vMissTargets.size());
    for (auto const& itr : vMissTargets)
    {
        data << itr.first;
        data << uint8(itr.second);
    }

    data << targets;

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
    {
        if (castFlags & CAST_FLAG_PREDICTED_POWER)              // predicted power
            data << uint32(0);

        if (castFlags & CAST_FLAG_PREDICTED_RUNES)              // predicted runes
        {
            uint8 runeMaskInitial = 0;
            uint8 runeMaskAfterCast = 0;
            data << uint8(runeMaskInitial);                     // runes state before
            data << uint8(runeMaskAfterCast);                   // runes state after
            for (uint8 i = 0; i < 6; ++i)
            {
                uint8 mask = (1 << i);
                if (mask & runeMaskInitial && (!(mask & runeMaskAfterCast)))
                {
                    data << uint8(0);
                }
            }
        }

        if (castFlags & CAST_FLAG_ADJUST_MISSILE)               // adjust missile trajectory duration
        {
            data << float(0);
            data << uint32(0);
        }
    }

    if (castFlags & CAST_FLAG_AMMO)                         // projectile info
    {
        data << uint32(ammoDisplayId);
        data << uint32(ammoInventoryType);
    }

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
    {
        if (castFlags & CAST_FLAG_VISUAL_CHAIN)                 // spell visual chain effect
        {
            data << uint32(0);                                  // SpellVisual.dbc id?
            data << uint32(0);                                  // overrides previous field if > 0 and violencelevel client cvar < 2
        }

        bool sendDestLoc = false;
        uint32 destLocCounter = 0;
        if (targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        {
            data << uint8(0); // The value increase for each time, can remind of a cast count for the spell
        }

        if (targets.m_targetMask & TARGET_FLAG_VISUAL_CHAIN)  // probably used (or can be used) with CAST_FLAG_VISUAL_CHAIN flag
        {
            data << uint32(0);                                  // count

            // for(int = 0; i < count; ++i)
            //{
            //    // position and guid?
            //    data << float(0) << float(0) << float(0) << uint64(0);
            //}
        }
    }

    SendPacket(data);
}

void WorldServer::SendAttackStart(ObjectGuid attackerGuid, ObjectGuid victimGuid)
{
    WorldPacket data(GetOpcode("SMSG_ATTACKSTART"), 8 + 8);
    data << attackerGuid;
    data << victimGuid;
    SendPacket(data);
}

void WorldServer::SendAttackStop(ObjectGuid attackerGuid, ObjectGuid victimGuid)
{
    WorldPacket data(GetOpcode("SMSG_ATTACKSTOP"), (8 + 8 + 4));
    data << attackerGuid.WriteAsPacked();
    data << victimGuid.WriteAsPacked();
    data << uint32(0);
    SendPacket(data);
}

void WorldServer::SendAttackerStateUpdate(uint32 hitInfo, ObjectGuid attackerGuid, ObjectGuid victimGuid, int32 damage, int32 overkillDamage, uint32 damageSchoolMask, int32 absorbedDamage, int32 resistedDamage, uint32 victimState, int32 attackerState, uint32 spellId, int32 blockedDamage)
{
    WorldPacket data(GetOpcode("SMSG_ATTACKERSTATEUPDATE"), (16 + 45));
    data << uint32(hitInfo);
    data << attackerGuid.WriteAsPacked();
    data << victimGuid.WriteAsPacked();
    data << int32(damage);

    if (GetClientBuild() >= CLIENT_BUILD_3_0_3)
        data << int32(overkillDamage);

    uint8 subDamageCount = 1;
    data << uint8(subDamageCount);
    for (uint8 i = 0; i < subDamageCount; i++)
    {
        if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
            data << uint32(damageSchoolMask);
        else
            data << uint32(GetFirstSchoolInMask(SpellSchoolMask(damageSchoolMask)));

        // Float coefficient of sub damage
        data << float(damage);
        data << int32(damage);

        if ((GetClientBuild() < CLIENT_BUILD_3_0_3) || (hitInfo & (WotLK::HITINFO_FULL_ABSORB | WotLK::HITINFO_PARTIAL_ABSORB)))
            data << int32(absorbedDamage);
        if ((GetClientBuild() < CLIENT_BUILD_3_0_3) || (hitInfo & (WotLK::HITINFO_FULL_RESIST | WotLK::HITINFO_PARTIAL_RESIST)))
            data << int32(resistedDamage);
    }

    if (GetClientBuild() < CLIENT_BUILD_3_0_3)
        data << uint32(victimState);
    else
        data << uint8(victimState);

    data << int32(attackerState);
    data << uint32(spellId);

    if ((GetClientBuild() < CLIENT_BUILD_3_0_3) || (hitInfo & (WotLK::HITINFO_BLOCK)))
        data << int32(blockedDamage);

    if ((GetClientBuild() >= CLIENT_BUILD_3_0_2) && (hitInfo & WotLK::HITINFO_RAGE_GAIN))
        data << uint32(0);

    if ((GetClientBuild() >= CLIENT_BUILD_3_0_2) && (hitInfo & WotLK::HITINFO_UNK0))
    {
        data << uint32(0);
        data << float(0);
        data << float(0);
        data << float(0);
        data << float(0);
        data << float(0);
        data << float(0);
        data << float(0);
        data << float(0);
        data << float(0);
        data << float(0);
        data << uint32(0);
        data << uint32(0);
        data << uint32(0);
    }

    SendPacket(data);
}

void WorldServer::SendEmote(ObjectGuid guid, uint32 emoteId)
{
    WorldPacket data(GetOpcode("SMSG_EMOTE"), 4 + 8);
    data << uint32(emoteId);
    data << guid;
    SendPacket(data);
}

void WorldServer::SendWeather(uint32 type, float grade, uint32 soundId, bool instant)
{
    WorldPacket data(GetOpcode("SMSG_WEATHER"), 4 + 4 + 4 + 1);
    data << uint32(type);
    data << float(grade);
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        data << uint32(soundId);
    data << uint8(instant); // 1 = instant change, 0 = smooth change
    SendPacket(data);
}

void WorldServer::SendWeatherForCurrentZone()
{
    if (!m_sessionData.isInWorld || !m_clientPlayer)
        return;

    uint32 mapId = m_clientPlayer->GetMapId();
    uint32 zoneId = m_clientPlayer->GetZoneId();

    auto itr1 = m_weather.find(mapId);
    if (itr1 == m_weather.end())
        return;

    auto itr2 = itr1->second.find(zoneId);
    if (itr2 == itr1->second.end())
        return;

    SendWeather(itr2->second.type, itr2->second.grade, itr2->second.soundId, true);
}

void WorldServer::SendInitialWorldStates(std::map<uint32, uint32> worldStates)
{
    if (worldStates.empty())
        return;

    if (!m_clientPlayer)
    {
        printf("[SendInitialWorldStates] Error: Attempt to send initial world states while client is not in world!\n");
        return;
    }

    WorldPacket data(GetOpcode("SMSG_INIT_WORLD_STATES"), (4 + 4 + 2 + 6));
    data << uint32(m_clientPlayer->GetMapId());
    data << uint32(m_clientPlayer->GetZoneId());
    if (GetClientBuild() >= CLIENT_BUILD_2_1_0)
        data << uint32(m_clientPlayer->GetAreaId());
    data << uint16(worldStates.size());
    for (auto itr : worldStates)
    {
        data << uint32(itr.first);
        data << uint32(itr.second);
    }
    data << uint32(0) << uint32(0);     // [-ZERO] Add terminator to prevent repeating audio bug.
    SendPacket(data);
}

void WorldServer::SendWorldStateUpdate(uint32 variable, uint32 value)
{
    WorldPacket data(GetOpcode("SMSG_UPDATE_WORLD_STATE"), 4 + 4);
    data << uint32(variable);
    data << uint32(value);
    SendPacket(data);
}

void WorldServer::SendMonsterMove(Unit* pUnit)
{
    WorldPacket data(GetOpcode(pUnit->m_moveSpline.m_transportGuid.IsEmpty() ? "SMSG_MONSTER_MOVE" : "SMSG_MONSTER_MOVE_TRANSPORT"));
    data << pUnit->GetPackGUID();

    if (!pUnit->m_moveSpline.m_transportGuid.IsEmpty())
    {
        data << pUnit->m_moveSpline.m_transportGuid.WriteAsPacked();

        if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
            data << int8(pUnit->m_moveSpline.m_transportSeat); // Transport Seat
    }

    if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
        data << uint8(0); // Toggle AnimTierInTrans
    pUnit->m_moveSpline.WriteMove(data);
    SendPacket(data);
}

void WorldServer::SendAuraUpdate(ObjectGuid targetGuid, uint8 slot, Aura const& aura)
{
    WorldPacket data(GetOpcode("SMSG_AURA_UPDATE"));
    data << targetGuid.WriteAsPacked();
    if (aura.spellId)
    {
        data << uint8(slot);
        data << aura;
    }
    else
    {
        data << uint8(slot);
        data << uint32(0);
    }
    SendPacket(data);
}

void WorldServer::SendAllAurasUpdate(ObjectGuid targetGuid, std::vector<Aura> const& auras)
{
    WorldPacket data(GetOpcode("SMSG_AURA_UPDATE_ALL"));
    data << targetGuid.WriteAsPacked();
    for (uint8 i = 0; i < auras.size(); i++)
    {
        if (auras[i].spellId)
        {
            data << uint8(i);
            data << auras[i];
        }
    }
    SendPacket(data);
}

void WorldServer::SendSpellFailedOther(ObjectGuid casterGuid, uint32 spellId, uint32 reason)
{
    WorldPacket data(GetOpcode("SMSG_SPELL_FAILED_OTHER"), (8 + 4));
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        data << casterGuid;
    else
        data << casterGuid.WriteAsPacked();
    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        data << uint8(0); // cast count
    data << uint32(spellId);
    if (GetClientBuild() > CLIENT_BUILD_3_0_2)
        data << uint8(reason);
    SendPacket(data);
}

void WorldServer::SendSpellChannelStart(ObjectGuid casterGuid, uint32 spellId, int32 duration)
{
    WorldPacket data(GetOpcode("MSG_CHANNEL_START"), (8 + 4 + 4));
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << casterGuid.WriteAsPacked();
    data << uint32(spellId);
    data << int32(duration);
    SendPacket(data);
}

void WorldServer::SendSpellChannelUpdate(ObjectGuid casterGuid, int32 duration)
{
    WorldPacket data(GetOpcode("MSG_CHANNEL_UPDATE"), 8 + 4);
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << casterGuid.WriteAsPacked();
    data << int32(duration);
    SendPacket(data);
}

void WorldServer::SendPlayerMinimapPing(ObjectGuid guid, float x, float y)
{
    WorldPacket data(GetOpcode("MSG_MINIMAP_PING"), 8 + 4 + 4);
    data << ObjectGuid(guid);
    data << float(x);
    data << float(y);
    SendPacket(data);
}

void WorldServer::SendRaidTargetIconUpdate(bool isFullUpdate, std::map<uint8, ObjectGuid> const& iconsMap)
{
    assert(isFullUpdate || iconsMap.size() == 1);

    WorldPacket data(GetOpcode("MSG_RAID_TARGET_UPDATE"), (1 + TARGET_ICON_COUNT * 9));
    data << uint8(isFullUpdate);
    if (!isFullUpdate && GetClientBuild() >= CLIENT_BUILD_3_0_2)
        data << m_clientPlayer->GetObjectGuid();
    for (auto const& itr : iconsMap)
    {
        data << uint8(itr.first);
        data << ObjectGuid(itr.second);
    }
    SendPacket(data);
}

void WorldServer::SendGameObjectDespawnAnim(ObjectGuid guid)
{
    WorldPacket data(GetOpcode("SMSG_GAMEOBJECT_DESPAWN_ANIM"), 8);
    data << ObjectGuid(guid);
    SendPacket(data);
}

void WorldServer::SendGameObjectCustomAnim(ObjectGuid guid, uint32 animId)
{
    WorldPacket data(GetOpcode("SMSG_GAMEOBJECT_CUSTOM_ANIM"), 8 + 4);
    data << ObjectGuid(guid);
    data << uint32(animId);
    SendPacket(data);
}

void WorldServer::SendPlayMusic(uint32 musicId)
{
    WorldPacket data(GetOpcode("SMSG_PLAY_MUSIC"), 4);
    data << uint32(musicId);
    SendPacket(data);
}

void WorldServer::SendPlaySound(uint32 soundId)
{
    WorldPacket data(GetOpcode("SMSG_PLAY_SOUND"), 4);
    data << uint32(soundId);
    SendPacket(data);
}

void WorldServer::SendPlayObjectSound(uint32 soundId, ObjectGuid guid)
{
    WorldPacket data(GetOpcode("SMSG_PLAY_OBJECT_SOUND"), 4 + 8);
    data << uint32(soundId);
    data << guid;
    SendPacket(data);
}

void WorldServer::SendPlaySpellVisual(ObjectGuid guid, uint32 kitId)
{
    WorldPacket data(GetOpcode("SMSG_PLAY_SPELL_VISUAL"), 8 + 4);
    data << guid;
    data << uint32(kitId);
    SendPacket(data);
}

void WorldServer::SendLogXPGain(ObjectGuid victimGuid, uint32 totalXP, uint32 killXP, float groupBonus, bool rafBonus)
{
    WorldPacket data(GetOpcode("SMSG_LOG_XPGAIN"), 21);
    data << (victimGuid.IsEmpty() ? ObjectGuid() : victimGuid);// guid
    data << uint32(totalXP);
    data << uint8(victimGuid.IsEmpty() ? 1 : 0); // 0 = kill, 1 = other
    if (!victimGuid.IsEmpty())
    {
        data << uint32(killXP);
        data << float(groupBonus);
    }
    if (GetClientBuild() >= CLIENT_BUILD_2_4_0)
        data << uint8(rafBonus);
    SendPacket(data);
}

void WorldServer::SendSetFactionStanding(float rafBonus, bool showVisual, int32 reputationListId, int32 standing)
{
    WorldPacket data(GetOpcode("SMSG_SET_FACTION_STANDING"), 16);
    if (GetClientBuild() >= CLIENT_BUILD_2_4_0)
        data << float(rafBonus);
    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        data << uint8(showVisual);
    data << uint32(1); // count
    data << int32(reputationListId);
    data << int32(standing);
    SendPacket(data);
}

void WorldServer::SendTaxiNodeStatus(ObjectGuid guid, bool known)
{
    WorldPacket data(GetOpcode("SMSG_TAXINODE_STATUS"), 9);
    data << guid;
    data << uint8(known);
    SendPacket(data);
}

void WorldServer::SendThreatClear(ObjectGuid creatureGuid)
{
    WorldPacket data(GetOpcode("SMSG_THREAT_CLEAR"), 8);
    data << creatureGuid.WriteAsPacked();
    SendPacket(data);
}

void WorldServer::SendThreatRemove(ObjectGuid creatureGuid, ObjectGuid targetGuid)
{
    WorldPacket data(GetOpcode("SMSG_THREAT_REMOVE"), 8 + 8);
    data << creatureGuid.WriteAsPacked();
    data << targetGuid.WriteAsPacked();
    SendPacket(data);
}

void WorldServer::SendThreatUpdate(ObjectGuid creatureGuid, std::vector<std::pair<ObjectGuid, uint32>> const& threatList)
{
    WorldPacket data(GetOpcode("SMSG_THREAT_UPDATE"), 8 + threatList.size() * 8);
    data << creatureGuid.WriteAsPacked();
    data << uint32(threatList.size());
    for (auto const& itr : threatList)
    {
        data << itr.first.WriteAsPacked();
        data << uint32(itr.second);
    }
    SendPacket(data);
}

void WorldServer::SendTriggerCinematic(uint32 cinematicId)
{
    WorldPacket data(GetOpcode("SMSG_TRIGGER_CINEMATIC"), 4);
    data << uint32(cinematicId);
    SendPacket(data);
    m_sessionData.isWatchingCinematic = true;
}

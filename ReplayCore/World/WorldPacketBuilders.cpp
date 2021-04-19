#include "WorldServer.h"
#include "../Defines//WorldPacket.h"
#include "GameDataMgr.h"
#include "GameDataDefines.h"
#include "../Defines/ClientVersions.h"
#include "../Defines/Utility.h"
#include "ReplayMgr.h"
#include "ChatDefines.h"

#define GLOBAL_CACHE_MASK           0x15
#define PER_CHARACTER_CACHE_MASK    0xEA
#define NUM_ACCOUNT_DATA_TYPES 8

void WorldServer::SendLoginVerifyWorld(WorldLocation const& location)
{
    WorldPacket response(GetOpcode("SMSG_LOGIN_VERIFY_WORLD"), 20);
    response << uint32(location.mapId);
    response << float(location.x);
    response << float(location.y);
    response << float(location.z);
    response << float(location.o);
    SendPacket(response);
}

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

        for (const auto& spell : pInfo->spell)
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
        for (const auto& action_itr : pInfo->action)
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
    for (const auto& guid : activePlayers)
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

    for (const auto& itr : m_players)
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
        data << uint8(0);                                      // CString max length 512, conditional read
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
    WorldPacket data(GetOpcode("SMSG_MOTD"), 50);
    data << uint32(1); // line count
    data << "Sniff Replay Core v0.0";
    SendPacket(data);
}

void WorldServer::SendTimeSyncRequest()
{
    WorldPacket data(GetOpcode("SMSG_TIME_SYNC_REQ"), 4);
    data << uint32(0); // couner
    SendPacket(data);
}

void WorldServer::SendItemQuerySingleResponse(uint32 itemId)
{
    ItemPrototype const* pProto = sGameDataMgr.GetItemPrototype(itemId);
    if (!pProto)
    {
        WorldPacket data(GetOpcode("SMSG_ITEM_QUERY_SINGLE_RESPONSE"), 4);
        data << uint32(itemId | 0x80000000);
        SendPacket(data);
        printf("Client requested info about unknown item id %u!\n", itemId);
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

    for (const auto& itr : pProto->Spells)
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

void WorldServer::SendItemNameQueryResponse(uint32 itemId)
{
    ItemPrototype const* pProto = sGameDataMgr.GetItemPrototype(itemId);
    if (!pProto)
    {
        printf("Client requested info about unknown item id %u!\n", itemId);
        return;
    }

    WorldPacket data(GetOpcode("SMSG_ITEM_NAME_QUERY_RESPONSE"), (4 + 10));
    data << uint32(pProto->ItemId);
    data << pProto->Name1;
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        data << uint32(pProto->InventoryType);
    SendPacket(data);
}
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

void WorldServer::TeleportClient(WorldLocation const& location)
{
    if (!m_clientPlayer)
    {
        printf("[SendMoveTeleportAck] Error: Attempt to teleport client but he is not in world!");
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
        printf("[SendMoveTeleportAck] Error: Attempt to teleport client but he is not in world!");
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
        SendTimeSyncRequest();
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
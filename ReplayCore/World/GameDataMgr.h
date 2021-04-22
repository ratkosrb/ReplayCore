#ifndef __GAME_DATA_MGR_H
#define __GAME_DATA_MGR_H

#include "../Defines/Common.h"
#include "GameDataDefines.h"
#include <unordered_map>
#include "ItemPrototype.h"
#include "PlayerDefines.h"
#include "QuestTemplate.h"

typedef std::unordered_map<uint32, FactionEntry> FactionsMap;
typedef std::unordered_map<uint32, FactionTemplateEntry> FactionTemplatesMap;
typedef std::unordered_map<uint32, ItemPrototype> ItemPrototypeMap;
typedef std::unordered_map<uint32, AreaTableEntry> AreaTableEntryMap;
typedef std::vector<AreaPOIEntry> AreaPOIStore;
typedef std::vector<GameTele> GameTeleStore;
typedef std::unordered_map<uint32, std::unique_ptr<Quest>> QuestMap;

enum GameDataSource
{
    DB_VMANGOS,
    DB_CMANGOS_CLASSIC,
    DB_CMANGOS_TBC,
    DB_CMANGOS_WOTLK,
    DB_TRINITY
};

class GameDataMgr
{
public:
    static GameDataMgr& Instance();
    void SetDataSource(GameDataSource source) { m_dataSource = source; }

    bool IsValidEmote(uint32 id) const;
    bool IsValidRace(uint32 id) const;
    bool IsValidClass(uint32 id) const;
    bool IsValidUnitDisplayId(uint32 id) const;
    uint8 GetMoveSpeedsCount() const;

    void LoadGameTele();
    GameTele const* GetGameTele(std::string name) const;
    GameTeleStore const& GetGameTeleStore() const { return m_GameTeleStore; }

    uint32 GetZoneIdFromCoordinates(uint32 mapId, float x, float y, float z);
    uint32 GetAreaIdFromCoordinates(uint32 mapId, float x, float y, float z);
    AreaPOIEntry const* GetClosestAreaPOIEntry(uint32 mapId, float x, float y, float z) const;
    AreaTableEntry const* GetAreaTableEntry(uint32 id) const
    {
        auto iter = m_areaTableEntryMap.find(id);
        if (iter == m_areaTableEntryMap.end())
            return nullptr;

        return &iter->second;
    }

    void LoadPlayerInfo();
    PlayerClassInfo const* GetPlayerClassInfo(uint32 class_) const
    {
        if (class_ >= MAX_CLASSES) return nullptr;
        return &m_PlayerClassInfo[class_];
    }
    void GetPlayerClassLevelInfo(uint32 class_, uint32 level, PlayerClassLevelInfo* info) const;

    PlayerInfo const* GetPlayerInfo(uint32 race, uint32 class_) const
    {
        if (race >= MAX_RACES)   return nullptr;
        if (class_ >= MAX_CLASSES) return nullptr;
        PlayerInfo const* info = &m_PlayerInfo[race][class_];
        if (info->displayId_m == 0 || info->displayId_f == 0) return nullptr;
        return info;
    }
    void GetPlayerLevelInfo(uint32 race, uint32 class_, uint32 level, PlayerLevelInfo* info) const;

    // Quests
    void LoadQuests();
    Quest const* GetQuestTemplate(uint32 quest_id) const
    {
        auto itr = m_QuestTemplatesMap.find(quest_id);
        return itr != m_QuestTemplatesMap.end() ? itr->second.get() : nullptr;
    }
    QuestMap const& GetQuestTemplates() const { return m_QuestTemplatesMap; }

    // Items
    void LoadItemPrototypes();
    ItemPrototype const* GetItemPrototype(uint32 id) const
    {
        auto iter = m_itemPrototypesMap.find(id);
        if (iter == m_itemPrototypesMap.end())
            return nullptr;

        return &iter->second;
    }
    ItemPrototypeMap const& GetItemPrototypeMap() const
    {
        return m_itemPrototypesMap;
    }

    // Factions
    void LoadFactions();
    bool IsValidFactionTemplate(uint32 id) const;
    FactionEntry const* GetFactionEntry(uint32 id) const
    {
        auto iter = m_FactionsMap.find(id);
        if (iter == m_FactionsMap.end())
            return nullptr;

        return &iter->second;
    }
    FactionsMap const& GetFactionMap() const
    {
        return m_FactionsMap;
    }
    FactionTemplateEntry const* GetFactionTemplateEntry(uint32 id) const
    {
        auto iter = m_FactionTemplatesMap.find(id);
        if (iter == m_FactionTemplatesMap.end())
            return nullptr;

        return &iter->second;
    }
    FactionTemplatesMap const& GetFactionTemplateMap() const
    {
        return m_FactionTemplatesMap;
    }
private:
    GameDataSource m_dataSource = DB_VMANGOS;
    FactionsMap m_FactionsMap;
    FactionTemplatesMap m_FactionTemplatesMap;
    ItemPrototypeMap m_itemPrototypesMap;
    QuestMap m_QuestTemplatesMap;
    PlayerClassInfo m_PlayerClassInfo[MAX_CLASSES];
    void BuildPlayerLevelInfo(uint8 race, uint8 class_, uint8 level, PlayerLevelInfo* plinfo) const;
    PlayerInfo m_PlayerInfo[MAX_RACES][MAX_CLASSES];
    static AreaTableEntryMap m_areaTableEntryMap;
    static AreaPOIStore m_areaPOIStore;
    GameTeleStore m_GameTeleStore;
};

#define sGameDataMgr GameDataMgr::Instance()

#endif
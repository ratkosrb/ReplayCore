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
typedef std::unordered_map<uint32, AreaTriggerTeleportEntry> AreaTriggerTeleportMap;
typedef std::unordered_map<uint32, CreatureTemplate> CreatureTemplateMap;
typedef std::unordered_map<uint32, GameObjectTemplate> GameObjectTemplateMap;
typedef std::unordered_map<uint32, BroadcastTextEntry> BroadcastTextMap;
typedef std::unordered_map<uint32, std::vector<uint32>> QuestRelationsMap;
typedef std::unordered_map<uint32, float> CreatureDisplayScaleMap;
typedef std::unordered_map<uint32, char const*> MapNamesMap;
typedef std::unordered_map<uint32, char const*> LanguageNamesMap;
typedef std::unordered_map<uint32, std::string> SpellNamesMap;

class GameDataMgr
{
public:
    static GameDataMgr& Instance();
    void SetDataSource(GameDataSource source) { m_dataSource = source; }

    bool IsValidEmote(uint32 id) const;
    bool IsValidStandState(uint32 id) const;
    bool IsValidRace(uint32 id) const;
    bool IsValidClass(uint32 id) const;
    bool IsValidUnitDisplayId(uint32 id) const;
    bool IsValidGameObjectDisplayId(uint32 id) const;
    bool IsValidGameObjectType(uint32 type) const;
    bool IsValidSpellId(uint32 id) const;
    uint8 GetMoveSpeedsCount() const;
    uint32 GetTransportMoveFlag() const;
    uint32 ConvertMovementFlags(uint32 moveFlags, bool onTransport) const;
    uint32 ConvertMovementFlagsForBuild(uint32 moveFlags, uint32 clientBuild) const;
    uint32 ConvertWeatherTypeToWeatherState(uint32 type, float grade);
    void ConvertWeatherStateAndGradeForVanilla(uint32& type, float& grade);
    uint32 GetWeatherSoundForVanilla(uint32 type, float grade) const;
    uint32 ConvertChatType(uint32 chatType) const;
    uint32 ConvertVanillaChatType(uint32 chatType) const;
    uint32 ConvertTBCChatType(uint32 chatType) const;
    uint32 ConvertWotLKChatType(uint32 chatType) const;
    uint32 ConvertClassicChatType(uint32 chatType) const;
    void ConvertMoveSplineData(uint8& splineType, uint32& splineFlags, bool& isCyclic, bool& isCatmullrom, float finalOrientation, bool hasDestination);
    uint32 ConvertNpcFlags(uint32 npcFlags);
    uint8 ConvertAuraFlags(uint8 auraFlags, uint8 activeFlags, uint32 slot);
    uint32 ConvertHitInfoFlags(uint32 hitInfo);

    std::string ChatTypeToString(uint32 value) const;
    std::string ChatTypeToVerbString(uint32 value) const;
    std::string HitInfoFlagsToString(uint32 value) const;
    std::string MovementFlagsToString(uint32 value) const;
    std::string SplineFlagsToString(uint32 value) const;
    std::string NpcFlagsToString(uint32 value) const;
    std::string FactionStandingToString(FactionEntry const* factionEntry, int32 standing, uint32 raceMask, uint32 classMask) const;

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
    char const* GetAreaName(uint32 id) const
    {
        auto iter = m_areaTableEntryMap.find(id);
        if (iter == m_areaTableEntryMap.end())
            return "UNKNOWN";

        return iter->second.name.c_str();
    }
    char const* GetMapName(uint32 id) const
    {
        auto iter = m_mapNamesMap.find(id);
        if (iter == m_mapNamesMap.end())
            return "UNKNOWN";

        return iter->second;
    }

    char const* GetLanguageName(uint32 id) const
    {
        auto iter = m_languageNamesMap.find(id);
        if (iter == m_languageNamesMap.end())
            return "UNKNOWN";

        return iter->second;
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

    // Broadcast Text
    void LoadBroadcastTexts();
    BroadcastTextEntry const* GetBroadcastTextEntry(uint32 id) const
    {
        auto itr = m_broadcastTextMap.find(id);
        return itr != m_broadcastTextMap.end() ? &itr->second : nullptr;
    }
    uint32 GetMatchingBroadcastTextId(std::string const& text) const
    {
        for (auto const& itr : m_broadcastTextMap)
            if (itr.second.maleText == text || itr.second.femaleText == text)
                return itr.first;
        return 0;
    }

    // GameObjects
    void LoadGameObjectTemplates();
    GameObjectTemplate const* GetGameObjectTemplate(uint32 id) const
    {
        auto itr = m_gameObjectTemplateMap.find(id);
        return itr != m_gameObjectTemplateMap.end() ? &itr->second : nullptr;
    }

    // Creatures
    void LoadCreatureTemplates();
    CreatureTemplate const* GetCreatureTemplate(uint32 id) const
    {
        auto itr = m_creatureTemplateMap.find(id);
        return itr != m_creatureTemplateMap.end() ? &itr->second : nullptr;
    }
    std::string GetCreatureName(uint32 id) const
    {
        auto itr = m_creatureTemplateMap.find(id);
        return itr != m_creatureTemplateMap.end() ? itr->second.name : "UNKNOWN";
    }
    float GetCreatureDisplayScale(uint32 displayId) const
    {
        auto itr = m_creatureDisplayScalesMap.find(displayId);
        return itr != m_creatureDisplayScalesMap.end() ? itr->second : 1.0f;
    }

    // AreaTriggers
    void LoadAreaTriggerTeleports();
    AreaTriggerTeleportEntry const* GetAreaTriggerTeleportEntry(uint32 id) const
    {
        auto itr = m_areaTriggerTeleportMap.find(id);
        return itr != m_areaTriggerTeleportMap.end() ? &itr->second : nullptr;
    }

    // Quests
    void LoadQuests();
    Quest const* GetQuestTemplate(uint32 id) const
    {
        auto itr = m_QuestTemplatesMap.find(id);
        return itr != m_QuestTemplatesMap.end() ? itr->second.get() : nullptr;
    }
    std::string GetQuestName(uint32 id) const
    {
        auto itr = m_QuestTemplatesMap.find(id);
        return itr != m_QuestTemplatesMap.end() ? itr->second->GetTitle() : "UNKNOWN";
    }
    QuestMap const& GetQuestTemplates() const { return m_QuestTemplatesMap; }
    void LoadQuestRelations();
    std::vector<uint32> const* GetQuestsStartedByCreature(uint32 entry)
    {
        auto itr = m_creatureQuestStarters.find(entry);
        if (itr == m_creatureQuestStarters.end())
            return nullptr;
        return &itr->second;
    }
    std::vector<uint32> const* GetQuestsEndedByCreature(uint32 entry)
    {
        auto itr = m_creatureQuestEnders.find(entry);
        if (itr == m_creatureQuestEnders.end())
            return nullptr;
        return &itr->second;
    }
    std::vector<uint32> const* GetQuestsStartedByGameObject(uint32 entry)
    {
        auto itr = m_gameobjectQuestStarters.find(entry);
        if (itr == m_gameobjectQuestStarters.end())
            return nullptr;
        return &itr->second;
    }
    std::vector<uint32> const* GetQuestsEndedByGameObject(uint32 entry)
    {
        auto itr = m_gameobjectQuestEnders.find(entry);
        if (itr == m_gameobjectQuestEnders.end())
            return nullptr;
        return &itr->second;
    }

    // Items
    void LoadItemPrototypes();
    ItemPrototype const* GetItemPrototype(uint32 id) const
    {
        auto iter = m_itemPrototypesMap.find(id);
        if (iter == m_itemPrototypesMap.end())
            return nullptr;

        return &iter->second;
    }
    std::string GetItemName(uint32 id) const
    {
        auto iter = m_itemPrototypesMap.find(id);
        if (iter == m_itemPrototypesMap.end())
            return "UNKNOWN";

        return iter->second.Name1;
    }
    uint32 GetItemIdWithDisplayId(uint32 displayId) const;
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
    FactionEntry const* GetFactionEntryFromReputationId(uint32 id) const
    {
        for (auto const& itr : m_FactionsMap)
        {
            if (itr.second.reputationListID == id)
                return &itr.second;
        }
        return nullptr;
    }
    std::string GetFactionName(uint32 id) const
    {
        auto iter = m_FactionsMap.find(id);
        if (iter == m_FactionsMap.end())
            return "UNKNOWN";

        return iter->second.name[0];
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
    int32 GetBaseReputation(FactionEntry const* factionEntry, uint32 raceMask, uint32 classMask) const
    {
        if (!factionEntry)
            return 0;

        int idx = factionEntry->GetIndexFitTo(raceMask, classMask);

        return idx >= 0 ? factionEntry->BaseRepValue[idx] : 0;
    }
    std::string GetReputationName(uint32 id) const
    {
        for (auto const& itr : m_FactionTemplatesMap)
        {
            if (FactionEntry const* pFaction = GetFactionEntry(itr.second.faction))
            {
                if (pFaction->reputationListID == id)
                    return pFaction->name[0];
            }
        }
        return "UNKNOWN";
    }
    std::string GetFactionTemplateName(uint32 id) const
    {
        auto iter = m_FactionTemplatesMap.find(id);
        if (iter == m_FactionTemplatesMap.end())
            return "UNKNOWN";

        return GetFactionName(iter->second.faction);
    }
    FactionTemplatesMap const& GetFactionTemplateMap() const
    {
        return m_FactionTemplatesMap;
    }
    
    // Spells
    void LoadSpellNames();
    std::string GetSpellName(uint32 id) const
    {
        auto iter = m_spellNamesMap.find(id);
        if (iter == m_spellNamesMap.end())
            return "UNKNOWN";

        return iter->second;
    }
private:
    GameDataSource m_dataSource = DB_VMANGOS;
    SpellNamesMap m_spellNamesMap;
    FactionsMap m_FactionsMap;
    FactionTemplatesMap m_FactionTemplatesMap;
    ItemPrototypeMap m_itemPrototypesMap;
    QuestMap m_QuestTemplatesMap;
    PlayerClassInfo m_PlayerClassInfo[MAX_CLASSES];
    void BuildPlayerLevelInfo(uint8 race, uint8 class_, uint8 level, PlayerLevelInfo* plinfo) const;
    PlayerInfo m_PlayerInfo[MAX_RACES][MAX_CLASSES];
    static AreaTableEntryMap const m_areaTableEntryMap;
    static AreaPOIStore const m_areaPOIStore;
    GameTeleStore m_GameTeleStore;
    AreaTriggerTeleportMap m_areaTriggerTeleportMap;
    CreatureTemplateMap m_creatureTemplateMap;
    GameObjectTemplateMap m_gameObjectTemplateMap;
    BroadcastTextMap m_broadcastTextMap;
    QuestRelationsMap m_creatureQuestStarters;
    QuestRelationsMap m_creatureQuestEnders;
    QuestRelationsMap m_gameobjectQuestStarters;
    QuestRelationsMap m_gameobjectQuestEnders;
    static CreatureDisplayScaleMap const m_creatureDisplayScalesMap;
    static MapNamesMap const m_mapNamesMap;
    static LanguageNamesMap const m_languageNamesMap;
};

#define sGameDataMgr GameDataMgr::Instance()

#endif
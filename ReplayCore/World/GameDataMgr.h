#ifndef __GAME_DATA_MGR_H
#define __GAME_DATA_MGR_H

#include "../Defines/Common.h"
#include "GameDataDefines.h"
#include <unordered_map>
#include "ItemPrototype.h"

typedef std::unordered_map<uint32, FactionEntry> FactionsMap;
typedef std::unordered_map<uint32, FactionTemplateEntry> FactionTemplatesMap;
typedef std::unordered_map<uint32, ItemPrototype> ItemPrototypeMap;

enum GameDataSource
{
    DB_VMANGOS,
    DB_CMANGOS,
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
};

#define sGameDataMgr GameDataMgr::Instance()

#endif
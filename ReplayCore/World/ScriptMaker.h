#ifndef __SCRIPT_MAKER_H
#define __SCRIPT_MAKER_H

#include "../Defines/Common.h"
#include "ObjectGuid.h"
#include "SniffedEvents.h"
#include "ScriptCommands.h"
#include <set>
#include <memory>

class ScriptMaker
{
public:
    void MakeScript(uint32 defaultScriptId, uint32 genericScriptStartId, std::string tableName, std::string commentPrefix, ObjectGuid defaultSource, ObjectGuid defaultTarget, bool saveGoSpawnsToDb, std::vector<std::pair<uint64, std::shared_ptr<SniffedEvent>>> const& eventsList);
private:
    void CheckGuidsThatNeedSeparateScript(ObjectGuid defaultSource, ObjectGuid defaultTarget, std::vector<std::pair<uint64, std::shared_ptr<SniffedEvent>>> const& eventsList);
    uint32 GetCreatureFieldValueBeforeTime(uint32 guid, uint64 unixtimems, char const* fieldName);
    uint32 GetTemporaryIdForUnknownBroadcastText(std::string text);
    void GetScriptInfoFromSniffedEvent(uint64 unixtimems, std::shared_ptr<SniffedEvent> sniffedEvent, std::vector<std::shared_ptr<ScriptInfo>>& scriptActions);
    void SetScriptTargetParams(ScriptInfo& script, ObjectGuid target);
    void SaveScriptToFile(std::ofstream& log, uint32 scriptId, std::string tableName, std::string commentPrefix, std::vector<std::shared_ptr<ScriptInfo>> const& vScripts, uint32 delayOffset);
    std::pair<uint64 /*unixtimems*/, std::shared_ptr<ScriptInfo>>* GetSpawnScriptForGuid(ObjectGuid guid)
    {
        auto itr = m_spawnScripts.find(guid);
        if (itr == m_spawnScripts.end())
            return nullptr;

        return &itr->second;
    }

    // the main script
    std::vector<std::shared_ptr<ScriptInfo>> m_mainScript;
    
    // guids whose actions need to be in a separate generic script
    std::set<ObjectGuid> m_separateScriptGuids;

    // generic scripts list per source guid
    std::map<ObjectGuid, std::vector<std::shared_ptr<ScriptInfo>>> m_genericScripts;

    // generic scripts that need to be started with initial targets swap
    std::set<ObjectGuid>  m_genericScriptWithSwappedTargets;

    // all guids that need to be targeted by guid because there are multiple with same entry
    std::set<ObjectGuid> m_targetByGuidGuids;

    // the summon script action for a given guid
    std::map<ObjectGuid, std::pair<uint64 /*unixtimems*/, std::shared_ptr<ScriptInfo>>> m_spawnScripts;

    // texts that we couldn't find in broadcast table
    std::vector<std::string> m_unknownScriptTexts;

    // if we generate SCRIPT_COMMAND_RESPAWN_GAMEOBJECT
    bool m_saveGoSpawnsToDb = false;
    std::set<uint32> m_gameObjectGuidsToExport;
};

#endif
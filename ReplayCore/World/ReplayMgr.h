#ifndef __REPLAY_MGR_H
#define __REPLAY_MGR_H

#include "../Defines/Common.h"
#include "ObjectGuid.h"
#include <set>
#include <map>

class ReplayMgr
{
public:
    static ReplayMgr& Instance();
    void LoadEverything()
    {
        LoadPlayers();
        LoadActivePlayers();
    }
    void LoadPlayers();
    void LoadActivePlayers();
    std::set<ObjectGuid> const& GetActivePlayers() const { return m_activePlayers; }
private:
    std::set<ObjectGuid> m_activePlayers;
    std::map<uint32 /*unixtime*/, ObjectGuid> m_activePlayerTimes;
};

#define sReplayMgr ReplayMgr::Instance()

#endif
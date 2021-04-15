#ifndef __REPLAY_MGR_H
#define __REPLAY_MGR_H

#include "../Defines/Common.h"

class ReplayMgr
{
public:
    static ReplayMgr& Instance();
    void LoadPlayers();
};

#define sReplayMgr ReplayMgr::Instance()

#endif
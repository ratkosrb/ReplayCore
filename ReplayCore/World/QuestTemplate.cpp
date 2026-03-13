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

#include "QuestTemplate.h"
#include "Player.h"
#include "GameDataMgr.h"

Quest::Quest(DbField* questRecord, uint32 dbVersion)
{
    if (dbVersion == DB_TRINITY)
    {
        QuestId = questRecord[0].GetUInt32();
        QuestMethod = questRecord[1].GetUInt8();
        QuestLevel = questRecord[2].GetInt16();
        MinLevel = questRecord[3].GetInt16();
        ZoneOrSort = questRecord[4].GetInt16();
        Type = questRecord[5].GetUInt16();
        SuggestedPlayers = questRecord[6].GetUInt8();
        RepObjectiveFaction = questRecord[7].GetUInt16();
        RepObjectiveValue = questRecord[8].GetUInt16();
        RequiredMaxRepFaction = questRecord[9].GetInt32();
        RequiredMaxRepValue = questRecord[10].GetInt32();
        NextQuestId = questRecord[11].GetUInt32();
        RewXP = questRecord[12].GetUInt8();
        RewSpell = questRecord[13].GetUInt32();
        RewSpellCast = questRecord[14].GetInt32();
        RewHonorMultiplier = questRecord[15].GetUInt32();
        RewHonorableKills = questRecord[16].GetFloat();
        SrcItemId = questRecord[17].GetUInt32();
        m_QuestFlags = questRecord[18].GetUInt32();
        //_minimapTargetMark = questRecord[19].GetUInt8();
        CharTitleId = questRecord[20].GetUInt8();
        PlayersSlain = questRecord[21].GetUInt8();
        BonusTalents = questRecord[22].GetUInt8();
        //_rewardArenaPoints = questRecord[23].GetUInt16();
        //_rewardSkillId = questRecord[24].GetUInt16();
        //_rewardSkillPoints = questRecord[25].GetUInt8();
        //_rewardReputationMask = questRecord[26].GetUInt8();
        //_questGiverPortrait = questRecord[27].GetUInt32();
        //_questTurnInPortrait = questRecord[28].GetUInt32();

        for (uint32 i = 0; i < QUEST_REWARDS_COUNT; ++i)
        {
            RewItemId[i] = questRecord[29 + i * 2].GetUInt32();
            RewItemCount[i] = questRecord[30 + i * 2].GetUInt16();
        }

        for (uint32 i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
        {
            RewChoiceItemId[i] = questRecord[37 + i * 2].GetUInt32();
            RewChoiceItemCount[i] = questRecord[38 + i * 2].GetUInt16();
        }

        for (uint32 i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
        {
            RewRepFaction[i] = questRecord[49 + i * 3].GetUInt16();
            RewRepValue[i] = questRecord[50 + i * 3].GetInt32();
            RewRepValueId[i] = questRecord[51 + i * 3].GetInt32();
        }

        PointMapId = questRecord[64].GetUInt16();
        PointX = questRecord[65].GetFloat();
        PointY = questRecord[66].GetFloat();
        PointOpt = questRecord[67].GetUInt32();
        Title = questRecord[68].GetCppString();
        Objectives = questRecord[69].GetCppString();
        Details = questRecord[70].GetCppString();
        EndText = questRecord[71].GetCppString();
        CompletedText = questRecord[72].GetCppString();

        for (uint32 i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
        {
            ReqCreatureOrGOId[i] = questRecord[73 + i].GetInt32();
            ReqCreatureOrGOCount[i] = questRecord[77 + i].GetUInt16();
            ObjectiveText[i] = questRecord[102 + i].GetCppString();
        }

        for (uint32 i = 0; i < QUEST_SOURCE_ITEM_IDS_COUNT; ++i)
        {
            ReqSourceId[i] = questRecord[81 + i].GetUInt32();
            ReqSourceCount[i] = questRecord[85 + i].GetUInt16();
        }

        for (uint32 i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
        {
            ReqItemId[i] = questRecord[89 + i].GetUInt32();
            ReqItemCount[i] = questRecord[95 + i].GetUInt16();
        }

        //int32 VerifiedBuild = questRecord[132].GetInt32();

        for (uint32 i = 0; i < QUEST_EMOTE_COUNT; ++i)
        {
            DetailsEmote[i] = 0;
            DetailsEmoteDelay[i] = 0;
            OfferRewardEmote[i] = 0;
            OfferRewardEmoteDelay[i] = 0;
        }

        ReqSpell[0] = questRecord[101].GetUInt32();

        /*
        for (uint32 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
        {
            RewardCurrencyId[i] = questRecord[106 + i].GetUInt16();
            RewardCurrencyCount[i] = questRecord[110 + i].GetUInt32();

            if (RewardCurrencyId[i])
                ++_rewCurrencyCount;
        }

        for (uint32 i = 0; i < QUEST_REQUIRED_CURRENCY_COUNT; ++i)
        {
            RequiredCurrencyId[i] = questRecord[114 + i].GetUInt16();
            RequiredCurrencyCount[i] = questRecord[118 + i].GetUInt32();

            if (RequiredCurrencyId[i])
                ++_reqCurrencyCount;
        }

        _questGiverTextWindow = questRecord[122].GetCppString();
        _questGiverTargetName = questRecord[123].GetCppString();
        _questTurnTextWindow = questRecord[124].GetCppString();
        _questTurnTargetName = questRecord[125].GetCppString();
        _soundAccept = questRecord[126].GetUInt16();
        _soundTurnIn = questRecord[127].GetUInt16();
        */
    }
    else
    {
        QuestId = questRecord[0].GetUInt32();
        QuestMethod = questRecord[1].GetUInt32();
        ZoneOrSort = questRecord[2].GetInt32();
        MinLevel = questRecord[3].GetUInt32();
        QuestLevel = questRecord[4].GetUInt32();
        Type = questRecord[5].GetUInt32();
        RequiredClasses = questRecord[6].GetUInt32();
        RequiredRaces = questRecord[7].GetUInt32();
        RequiredSkill = questRecord[8].GetUInt32();
        RequiredSkillValue = questRecord[9].GetUInt32();
        RepObjectiveFaction = questRecord[10].GetUInt32();
        RepObjectiveValue = questRecord[11].GetInt32();
        RequiredMinRepFaction = questRecord[12].GetUInt32();
        RequiredMinRepValue = questRecord[13].GetInt32();
        RequiredMaxRepFaction = questRecord[14].GetUInt32();
        RequiredMaxRepValue = questRecord[15].GetInt32();
        SuggestedPlayers = questRecord[16].GetUInt32();
        LimitTime = questRecord[17].GetUInt32();
        m_QuestFlags = questRecord[18].GetUInt16();
        m_SpecialFlags = questRecord[19].GetUInt16();
        CharTitleId = (dbVersion == DB_CMANGOS_TBC || dbVersion == DB_CMANGOS_WOTLK) ? questRecord[124].GetUInt32() : 0;
        PlayersSlain = (dbVersion == DB_CMANGOS_WOTLK) ? questRecord[125].GetUInt32() : 0;
        BonusTalents = (dbVersion == DB_CMANGOS_WOTLK) ? questRecord[126].GetUInt32() : 0;
        PrevQuestId = questRecord[20].GetInt32();
        NextQuestId = questRecord[21].GetInt32();
        RewXPId = (dbVersion == DB_CMANGOS_WOTLK) ? questRecord[128].GetUInt32() : 0;
        ExclusiveGroup = questRecord[22].GetInt32();
        NextQuestInChain = questRecord[23].GetUInt32();
        SrcItemId = questRecord[24].GetUInt32();
        SrcItemCount = questRecord[25].GetUInt32();
        SrcSpell = questRecord[26].GetUInt32();
        Title = questRecord[27].GetCppString();
        Details = questRecord[28].GetCppString();
        Objectives = questRecord[29].GetCppString();
        OfferRewardText = questRecord[30].GetCppString();
        RequestItemsText = questRecord[31].GetCppString();
        EndText = questRecord[32].GetCppString();
        CompletedText = (dbVersion == DB_CMANGOS_WOTLK) ? questRecord[129].GetCppString() : "";

        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
            ObjectiveText[i] = questRecord[33 + i].GetCppString();

        for (int i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
            ReqItemId[i] = questRecord[37 + i].GetUInt32();

        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
            ReqItemCount[i] = questRecord[41 + i].GetUInt32();

        for (int i = 0; i < QUEST_SOURCE_ITEM_IDS_COUNT; ++i)
            ReqSourceId[i] = questRecord[45 + i].GetUInt32();

        for (int i = 0; i < QUEST_SOURCE_ITEM_IDS_COUNT; ++i)
            ReqSourceCount[i] = questRecord[49 + i].GetUInt32();

        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
            ReqCreatureOrGOId[i] = questRecord[53 + i].GetInt32();

        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
            ReqCreatureOrGOCount[i] = questRecord[57 + i].GetUInt32();

        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
            ReqSpell[i] = questRecord[61 + i].GetUInt32();

        for (int i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
            RewChoiceItemId[i] = questRecord[65 + i].GetUInt32();

        for (int i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
            RewChoiceItemCount[i] = questRecord[71 + i].GetUInt32();

        for (int i = 0; i < QUEST_REWARDS_COUNT; ++i)
            RewItemId[i] = questRecord[77 + i].GetUInt32();

        for (int i = 0; i < QUEST_REWARDS_COUNT; ++i)
            RewItemCount[i] = questRecord[81 + i].GetUInt32();

        for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
            RewRepFaction[i] = questRecord[85 + i].GetUInt32();

        for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
            RewRepValue[i] = questRecord[90 + i].GetInt32();

        for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
            RewRepValueId[i] = (dbVersion == DB_CMANGOS_WOTLK) ? questRecord[130 + i].GetInt32() : 0;

        RewXP = CalculateXPFromMoney();
        RewOrReqMoney = questRecord[95].GetInt32();
        RewHonorableKills = (dbVersion == DB_CMANGOS_TBC || dbVersion == DB_CMANGOS_WOTLK) ? questRecord[123].GetUInt32() : 0;
        RewHonorMultiplier = (dbVersion == DB_CMANGOS_WOTLK) ? questRecord[127].GetFloat() : 0;
        RewMoneyMaxLevel = questRecord[96].GetUInt32();
        RewSpell = questRecord[97].GetUInt32();
        RewSpellCast = questRecord[98].GetUInt32();
        RewMailTemplateId = questRecord[99].GetInt32();
        RewMailDelaySecs = questRecord[100].GetUInt32();
        PointMapId = questRecord[101].GetUInt32();
        PointX = questRecord[102].GetFloat();
        PointY = questRecord[103].GetFloat();
        PointOpt = questRecord[104].GetUInt32();

        for (int i = 0; i < QUEST_EMOTE_COUNT; ++i)
            DetailsEmote[i] = questRecord[105 + i].GetUInt32();

        for (int i = 0; i < QUEST_EMOTE_COUNT; ++i)
            DetailsEmoteDelay[i] = questRecord[109 + i].GetUInt32();

        IncompleteEmote = questRecord[113].GetUInt32();
        CompleteEmote = questRecord[114].GetUInt32();

        for (int i = 0; i < QUEST_EMOTE_COUNT; ++i)
            OfferRewardEmote[i] = questRecord[115 + i].GetInt32();

        for (int i = 0; i < QUEST_EMOTE_COUNT; ++i)
            OfferRewardEmoteDelay[i] = questRecord[119 + i].GetInt32();
    }

    m_isActive = true;

    if (QuestMethod & QUEST_METHOD_DISABLED)
    {
        // Leave invalid entries to be caught by ObjectMgr
        if (QuestMethod <= QUEST_METHOD_LIMIT)
            QuestMethod = QUEST_METHOD_DISABLED;

        m_isActive = false;
    }

    m_reqitemscount = 0;
    m_reqCreatureOrGOcount = 0;
    m_rewitemscount = 0;
    m_rewchoiceitemscount = 0;

    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
    {
        if (ReqItemId[i])
            ++m_reqitemscount;
        if (ReqCreatureOrGOId[i])
            ++m_reqCreatureOrGOcount;
    }

    for (uint32 i : RewItemId)
    {
        if (i)
            ++m_rewitemscount;
    }

    for (uint32 i : RewChoiceItemId)
    {
        if (i)
            ++m_rewchoiceitemscount;
    }
}

uint32 Quest::CalculateXPFromMoney() const
{
    uint32 qLevel = QuestLevel;
    float fullxp = 0;

    if (qLevel >= 65)
        fullxp = RewMoneyMaxLevel / 6.0f;
    else if (qLevel == 64)
        fullxp = RewMoneyMaxLevel / 4.8f;
    else if (qLevel == 63)
        fullxp = RewMoneyMaxLevel / 3.6f;
    else if (qLevel == 62)
        fullxp = RewMoneyMaxLevel / 2.4f;
    else if (qLevel == 61)
        fullxp = RewMoneyMaxLevel / 1.2f;
    else if (qLevel > 0 && qLevel <= 60)
        fullxp = RewMoneyMaxLevel / 0.6f;

    return uint32(fullxp);
}

uint32 Quest::XPValue(Player* pPlayer) const
{
    if (pPlayer)
    {
        if (RewXP > 0)
        {
            uint32 pLevel = pPlayer->GetLevel();
            uint32 qLevel = QuestLevel;
            float fullxp = float(RewXP);

            if (pLevel <= qLevel +  5)
                return uint32(ceilf(fullxp));
            else if (pLevel == qLevel +  6)
                return uint32(ceilf(fullxp * 0.8f));
            else if (pLevel == qLevel +  7)
                return uint32(ceilf(fullxp * 0.6f));
            else if (pLevel == qLevel +  8)
                return uint32(ceilf(fullxp * 0.4f));
            else if (pLevel == qLevel +  9)
                return uint32(ceilf(fullxp * 0.2f));
            else
                return uint32(ceilf(fullxp * 0.1f));
        }
    }
    return 0;
}

bool Quest::IsAllowedInRaid() const
{
    if (Type == QUEST_TYPE_RAID)
        return true;
    if (m_QuestFlags & QUEST_FLAGS_RAID)
        return true;

    return false;
}

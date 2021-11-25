#ifndef __PLAYER_H
#define __PLAYER_H

#include "Unit.h"
#include "PlayerDefines.h"
#include <string>

struct PlayerData;
class Quest;

class Player : public Unit
{
public:
    Player(PlayerData const& playerData);
    Player(ObjectGuid guid, std::string name, Player const& otherPlayer);

    void InitializeDefaultPlayerValues();

    char const* GetName() const { return m_name.c_str(); }
    void SetName(std::string name) { m_name = name; }

    uint32 GetPlayerBytes() const;
    void SetPlayerBytes(uint32 bytes1);
    uint32 GetPlayerBytes2() const;
    void SetPlayerBytes2(uint32 bytes2);
    uint32 GetPlayerFlags() const;
    void SetPlayerFlags(uint32 flags);
    int8 GetPvPTitle() const;
    void SetPvPTitle(int8 pvpTitle);
    uint32 GetChosenTitle() const;
    void SetChosenTitle(uint32 title);
    uint8 GetComboPoints() const;
    void SetComboPoints(uint8 points);

    void SetSkinColor(uint8 skin);
    uint8 GetSkinColor() const;
    void SetFace(uint8 face);
    uint8 GetFace() const;
    void SetHairStyle(uint8 hariStyle);
    uint8 GetHairStyle() const;
    void SetHairColor(uint8 hairColo);
    uint8 GetHairColor() const;
    void SetFacialHair(uint8 facialHair);
    uint8 GetFacialHair() const;

    void SetVisibleItemSlot(uint8 slot, uint32 itemId, uint32 enchantId);
    uint32 GetVisibleItemId(uint8 slot) const;
    uint32 GetVisibleItemEnchant(uint8 slot) const;

    bool CanSeeStartQuest(Quest const* pQuest) const;
    uint32 GetQuestStatus(Quest const* pQuest) const;

    uint32 GetZoneId() const final;
    void SetCachedZoneId(uint32 zoneId) { m_cachedZoneId = zoneId; }

protected:
    std::string m_name;
    uint32 m_cachedZoneId = 0;
};

#endif
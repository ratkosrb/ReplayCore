/*
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

#ifndef MANGOS_H_SNIFFEDEVENT
#define MANGOS_H_SNIFFEDEVENT

#include "../Defines/Common.h"
#include "ObjectGuid.h"
#include "Aura.h"
#include "MovementInfo.h"
#include <string>

enum SniffedEventType : uint8
{
    SE_WEATHER_UPDATE,
    SE_WORLD_TEXT,
    SE_WORLD_STATE_UPDATE,
    SE_WORLDOBJECT_CREATE,
    SE_WORLDOBJECT_DESTROY,
    SE_UNIT_ATTACK_LOG,
    SE_UNIT_ATTACK_START,
    SE_UNIT_ATTACK_STOP,
    SE_UNIT_EMOTE,
    SE_UNIT_CLIENTSIDE_MOVEMENT,
    SE_UNIT_SERVERSIDE_MOVEMENT,
    SE_UNIT_UPDATE_ORIENTATION,
    SE_UNIT_UPDATE_ENTRY,
    SE_UNIT_UPDATE_SCALE,
    SE_UNIT_UPDATE_DISPLAY_ID,
    SE_UNIT_UPDATE_MOUNT,
    SE_UNIT_UPDATE_FACTION,
    SE_UNIT_UPDATE_LEVEL,
    SE_UNIT_UPDATE_AURA_STATE,
    SE_UNIT_UPDATE_EMOTE_STATE,
    SE_UNIT_UPDATE_STAND_STATE,
    SE_UNIT_UPDATE_VIS_FLAGS,
    SE_UNIT_UPDATE_SHEATH_STATE,
    SE_UNIT_UPDATE_SHAPESHIFT_FORM,
    SE_UNIT_UPDATE_NPC_FLAGS,
    SE_UNIT_UPDATE_UNIT_FLAGS,
    SE_UNIT_UPDATE_UNIT_FLAGS2,
    SE_UNIT_UPDATE_DYNAMIC_FLAGS,
    SE_UNIT_UPDATE_CURRENT_HEALTH,
    SE_UNIT_UPDATE_MAX_HEALTH,
    SE_UNIT_UPDATE_CURRENT_MANA,
    SE_UNIT_UPDATE_MAX_MANA,
    SE_UNIT_UPDATE_BOUNDING_RADIUS,
    SE_UNIT_UPDATE_COMBAT_REACH,
    SE_UNIT_UPDATE_MAIN_HAND_ATTACK_TIME,
    SE_UNIT_UPDATE_OFF_HAND_ATTACK_TIME,
    SE_UNIT_UPDATE_CHANNEL_SPELL,
    SE_UNIT_UPDATE_GUID_VALUE,
    SE_UNIT_UPDATE_SPEED,
    SE_UNIT_UPDATE_AURAS,
    SE_CREATURE_TEXT,
    SE_CREATURE_EQUIPMENT_UPDATE,
    SE_PLAYER_CHAT,
    SE_PLAYER_EQUIPMENT_UPDATE,
    SE_DYNAMICOBJECT_CREATE,
    SE_GAMEOBJECT_CUSTOM_ANIM,
    SE_GAMEOBJECT_DESPAWN_ANIM,
    SE_GAMEOBJECT_UPDATE_FLAGS,
    SE_GAMEOBJECT_UPDATE_STATE,
    SE_GAMEOBJECT_UPDATE_ARTKIT,
    SE_GAMEOBJECT_UPDATE_DYNAMIC_FLAGS,
    SE_GAMEOBJECT_UPDATE_PATH_PROGRESS,
    SE_PLAY_MUSIC,
    SE_PLAY_SOUND,
    SE_PLAY_SPELL_VISUAL_KIT,
    SE_SPELL_CAST_FAILED,
    SE_SPELL_CAST_START,
    SE_SPELL_CAST_GO,
    SE_SPELL_CHANNEL_START,
    SE_SPELL_CHANNEL_UPDATE,
    SE_CLIENT_QUEST_ACCEPT,
    SE_CLIENT_QUEST_COMPLETE,
    SE_CLIENT_CREATURE_INTERACT,
    SE_CLIENT_GAMEOBJECT_USE,
    SE_CLIENT_ITEM_USE,
    SE_CLIENT_RECLAIM_CORPSE,
    SE_CLIENT_RELEASE_SPIRIT,
    SE_QUEST_UPDATE_COMPLETE,
    SE_QUEST_UPDATE_FAILED,
    SE_XP_GAIN_LOG,
    SE_FACTION_STANDING_UPDATE,
};

inline char const* GetSniffedEventName(SniffedEventType eventType)
{
    switch (eventType)
    {
        case SE_WEATHER_UPDATE:
            return "Weather Update";
        case SE_WORLD_TEXT:
            return "World Text";
        case SE_WORLD_STATE_UPDATE:
            return "World State Update";
        case SE_WORLDOBJECT_CREATE:
            return "WorldObject Create";
        case SE_WORLDOBJECT_DESTROY:
            return "WorldObject Destroy";
        case SE_UNIT_ATTACK_LOG:
            return "Unit Attack Log";
        case SE_UNIT_ATTACK_START:
            return "Unit Attack Start";
        case SE_UNIT_ATTACK_STOP:
            return "Unit Attack Stop";
        case SE_UNIT_EMOTE:
            return "Unit Emote";
        case SE_UNIT_CLIENTSIDE_MOVEMENT:
            return "Unit Client Movement";
        case SE_UNIT_SERVERSIDE_MOVEMENT:
            return "Unit Server-side Movement";
        case SE_UNIT_UPDATE_ORIENTATION:
            return "Unit Update Orientation";
        case SE_UNIT_UPDATE_ENTRY:
            return "Unit Update Entry";
        case SE_UNIT_UPDATE_SCALE:
            return "Unit Update Scale";
        case SE_UNIT_UPDATE_DISPLAY_ID:
            return "Unit Update Display Id";
        case SE_UNIT_UPDATE_MOUNT:
            return "Unit Update Mount";
        case SE_UNIT_UPDATE_FACTION:
            return "Unit Update Faction";
        case SE_UNIT_UPDATE_LEVEL:
            return "Unit Update Level";
        case SE_UNIT_UPDATE_AURA_STATE:
            return "Unit Update Aura State";
        case SE_UNIT_UPDATE_EMOTE_STATE:
            return "Unit Update Emote State";
        case SE_UNIT_UPDATE_STAND_STATE:
            return "Unit Update Stand State";
        case SE_UNIT_UPDATE_VIS_FLAGS:
            return "Unit Update Vis Flags";
        case SE_UNIT_UPDATE_SHEATH_STATE:
            return "Unit Update Sheath State";
        case SE_UNIT_UPDATE_SHAPESHIFT_FORM:
            return "Unit Update Shapeshift Form";
        case SE_UNIT_UPDATE_NPC_FLAGS:
            return "Unit Update NPC Flags";
        case SE_UNIT_UPDATE_UNIT_FLAGS:
            return "Unit Update Unit Flags";
        case SE_UNIT_UPDATE_UNIT_FLAGS2:
            return "Unit Update Unit Flags 2";
        case SE_UNIT_UPDATE_DYNAMIC_FLAGS:
            return "Unit Update Dynamic Flags";
        case SE_UNIT_UPDATE_CURRENT_HEALTH:
            return "Unit Update Current Health";
        case SE_UNIT_UPDATE_MAX_HEALTH:
            return "Unit Update Max Health";
        case SE_UNIT_UPDATE_CURRENT_MANA:
            return "Unit Update Current Mana";
        case SE_UNIT_UPDATE_MAX_MANA:
            return "Unit Update Max Mana";
        case SE_UNIT_UPDATE_BOUNDING_RADIUS:
            return "Unit Update Bounding Radius";
        case SE_UNIT_UPDATE_COMBAT_REACH:
            return "Unit Update Combat Reach";
        case SE_UNIT_UPDATE_MAIN_HAND_ATTACK_TIME:
            return "Unit Update Main Hand Speed";
        case SE_UNIT_UPDATE_OFF_HAND_ATTACK_TIME:
            return "Unit Update Off Hand Speed";
        case SE_UNIT_UPDATE_CHANNEL_SPELL:
            return "Unit Update Channel Spell";
        case SE_UNIT_UPDATE_GUID_VALUE:
            return "Unit Update GUID Value";
        case SE_UNIT_UPDATE_SPEED:
            return "Unit Update Speed";
        case SE_UNIT_UPDATE_AURAS:
            return "Unit Update Auras";
        case SE_CREATURE_TEXT:
            return "Creature Text";
        case SE_CREATURE_EQUIPMENT_UPDATE:
            return "Creature Equipment Update";
        case SE_PLAYER_CHAT:
            return "Player Chat";
        case SE_PLAYER_EQUIPMENT_UPDATE:
            return "Player Equipment Update";
        case SE_DYNAMICOBJECT_CREATE:
            return "DynamicObject Create";
        case SE_GAMEOBJECT_CUSTOM_ANIM:
            return "GameObject Custom Anim";
        case SE_GAMEOBJECT_DESPAWN_ANIM:
            return "GameObject Despawn Anim";
        case SE_GAMEOBJECT_UPDATE_FLAGS:
            return "GameObject Update Flags";
        case SE_GAMEOBJECT_UPDATE_STATE:
            return "GameObject Update State";
        case SE_GAMEOBJECT_UPDATE_ARTKIT:
            return "GameObject Update ArtKit";
        case SE_GAMEOBJECT_UPDATE_DYNAMIC_FLAGS:
            return "GameObject Update Dynamic Flags";
        case SE_GAMEOBJECT_UPDATE_PATH_PROGRESS:
            return "GameObject Update Path Progress";
        case SE_PLAY_MUSIC:
            return "Play Music";
        case SE_PLAY_SOUND:
            return "Play Sound";
        case SE_PLAY_SPELL_VISUAL_KIT:
            return "Play Spell Visual Kit";
        case SE_SPELL_CAST_FAILED:
            return "Spell Cast Failed";
        case SE_SPELL_CAST_START:
            return "Spell Cast Start";
        case SE_SPELL_CAST_GO:
            return "Spell Cast Go";
        case SE_SPELL_CHANNEL_START:
            return "Spell Channel Start";
        case SE_SPELL_CHANNEL_UPDATE:
            return "Spell Channel Update";
        case SE_CLIENT_QUEST_ACCEPT:
            return "Client Quest Accept";
        case SE_CLIENT_QUEST_COMPLETE:
            return "Client Quest Complete";
        case SE_CLIENT_CREATURE_INTERACT:
            return "Client Creature Interact";
        case SE_CLIENT_GAMEOBJECT_USE:
            return "Client GameObject Use";
        case SE_CLIENT_ITEM_USE:
            return "Client Item Use";
        case SE_CLIENT_RECLAIM_CORPSE:
            return "Client Reclaim Corpse";
        case SE_CLIENT_RELEASE_SPIRIT:
            return "Client Release Spirit";
        case SE_QUEST_UPDATE_COMPLETE:
            return "Quest Completed";
        case SE_QUEST_UPDATE_FAILED:
            return "Quest Failed";
        case SE_XP_GAIN_LOG:
            return "XP Gain Log";
        case SE_FACTION_STANDING_UPDATE:
            return "Faction Standing Update";
    }
    return "Unknown Event";
}

struct SniffedEvent
{
    bool m_disabled = false;
    virtual void Execute() const = 0;
    virtual void PepareForCurrentClient() { };
    virtual SniffedEventType GetType() const = 0;
    virtual ObjectGuid GetSourceGuid() const { return ObjectGuid(); };
    virtual ObjectGuid GetTargetGuid() const { return ObjectGuid(); };
    virtual std::shared_ptr<SniffedEvent> clone() const = 0;
};

template <class Derived>
struct SniffedEventCRTP : SniffedEvent
{
    virtual std::shared_ptr<SniffedEvent> clone() const
    {
        return std::make_shared<Derived>(static_cast<const Derived&>(*this));
    }
};

struct SniffedEvent_WeatherUpdate : SniffedEventCRTP<SniffedEvent_WeatherUpdate>
{
    SniffedEvent_WeatherUpdate(uint32 mapId, uint32 zoneId, uint32 weatherType, float grade, uint32 soundId, bool instant) :
        m_mapId(mapId), m_zoneId(zoneId), m_type(weatherType), m_grade(grade), m_soundId(soundId), m_instant(instant) {};
    uint32 m_mapId = 0;
    uint32 m_zoneId = 0;
    uint32 m_type = 0;
    float m_grade = 0.0f;
    uint32 m_soundId = 0;
    bool m_instant = false;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_WEATHER_UPDATE;
    }
};

struct SniffedEvent_WorldText : SniffedEventCRTP<SniffedEvent_WorldText>
{
    SniffedEvent_WorldText(std::string text, uint32 chatType, uint32 language) :
        m_text(text), m_chatType(chatType), m_language(language) {};
    std::string m_text;
    uint32 m_chatType = 0;
    uint32 m_language = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_WORLD_TEXT;
    }
};

struct SniffedEvent_WorldStateUpdate : SniffedEventCRTP<SniffedEvent_WorldStateUpdate>
{
    SniffedEvent_WorldStateUpdate(uint32 variable, uint32 value) :
        m_variable(variable), m_value(value) {};
    uint32 m_variable = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_WORLD_STATE_UPDATE;
    }
};

template <class Derived>
struct SniffedEvent_WorldObjectCreate_Base : SniffedEventCRTP<Derived>
{
    SniffedEvent_WorldObjectCreate_Base(ObjectGuid objectGuid, bool isSpawn, uint32 mapId, float x, float y, float z, float o, ObjectGuid transportGuid, float transportX, float transportY, float transportZ, float transportO) :
        m_objectGuid(objectGuid), m_isSpawn(isSpawn), m_location(mapId, x, y, z, o), m_transportGuid(transportGuid), m_transportPosition(transportX, transportY, transportZ, transportO) {};
    ObjectGuid m_objectGuid;
    bool m_isSpawn = false;
    WorldLocation m_location;
    ObjectGuid m_transportGuid;
    Position m_transportPosition;
    void Execute() const override;
    SniffedEventType GetType() const final
    {
        return SE_WORLDOBJECT_CREATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_WorldObjectCreate : SniffedEvent_WorldObjectCreate_Base<SniffedEvent_WorldObjectCreate>
{
    SniffedEvent_WorldObjectCreate(ObjectGuid objectGuid, bool isSpawn, uint32 mapId, float x, float y, float z, float o, ObjectGuid transportGuid, float transportX, float transportY, float transportZ, float transportO) :
        SniffedEvent_WorldObjectCreate_Base(objectGuid, isSpawn, mapId, x, y, z, o, transportGuid, transportX, transportY, transportZ, transportO) {};
};

struct SniffedEvent_GameObjectCreate : SniffedEvent_WorldObjectCreate_Base<SniffedEvent_GameObjectCreate>
{
    SniffedEvent_GameObjectCreate(ObjectGuid objectGuid, bool isSpawn, uint32 mapId, float x, float y, float z, float o, ObjectGuid transportGuid, float transportX, float transportY, float transportZ, float transportO, uint32 transportPathTimer) :
        SniffedEvent_WorldObjectCreate_Base(objectGuid, isSpawn, mapId, x, y, z, o, transportGuid, transportX, transportY, transportZ, transportO), m_transportPathTimer(transportPathTimer) {};
    uint32 m_transportPathTimer = 0;
    void Execute() const final;
};

struct SniffedEvent_UnitCreate : SniffedEvent_WorldObjectCreate_Base<SniffedEvent_UnitCreate>
{
    SniffedEvent_UnitCreate(ObjectGuid objectGuid, bool isSpawn, uint32 mapId, float x, float y, float z, float o, ObjectGuid transportGuid, float transportX, float transportY, float transportZ, float transportO, uint32 moveTime, uint32 moveFlags, uint32 moveFlags2, float swimPitch, uint32 fallTime, float jumpSpeedXY, float jumpSpeedZ, float jumpCosAngle, float jumpSinAngle, float splineElevation) :
        SniffedEvent_WorldObjectCreate_Base(objectGuid, isSpawn, mapId, x, y, z, o, transportGuid, transportX, transportY, transportZ, transportO), m_moveTime(moveTime), m_moveFlags(moveFlags), m_moveFlags2(m_moveFlags2), m_swimPitch(swimPitch), m_fallTime(fallTime), m_jumpInfo(jumpSpeedZ, jumpCosAngle, jumpSinAngle, jumpSpeedXY), m_splineElevation(splineElevation) {};
    uint32 m_moveTime = 0;
    uint32 m_moveFlags = 0;
    uint32 m_moveFlags2 = 0;
    float m_swimPitch = 0;
    uint32 m_fallTime = 0;
    JumpInfo m_jumpInfo;
    float m_splineElevation = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
};

struct SniffedEvent_WorldObjectDestroy : SniffedEventCRTP<SniffedEvent_WorldObjectDestroy>
{
    SniffedEvent_WorldObjectDestroy(ObjectGuid objectGuid) :
        m_objectGuid(objectGuid) {};
    ObjectGuid m_objectGuid;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_WORLDOBJECT_DESTROY;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitAttackStart : SniffedEventCRTP<SniffedEvent_UnitAttackStart>
{
    SniffedEvent_UnitAttackStart(ObjectGuid attackerGuid, ObjectGuid victimGuid) :
        m_attackerGuid(attackerGuid), m_victimGuid(victimGuid) {};
    ObjectGuid m_attackerGuid;
    ObjectGuid m_victimGuid;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_ATTACK_START;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_attackerGuid;
    }
    ObjectGuid GetTargetGuid() const final
    {
        return m_victimGuid;
    }
};

struct SniffedEvent_UnitAttackStop : SniffedEventCRTP<SniffedEvent_UnitAttackStop>
{
    SniffedEvent_UnitAttackStop(ObjectGuid attackerGuid, ObjectGuid victimGuid) :
        m_attackerGuid(attackerGuid), m_victimGuid(victimGuid) {};
    ObjectGuid m_attackerGuid;
    ObjectGuid m_victimGuid;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_ATTACK_STOP;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_attackerGuid;
    }
    ObjectGuid GetTargetGuid() const final
    {
        return m_victimGuid;
    }
};

struct SniffedEvent_UnitAttackLog : SniffedEventCRTP<SniffedEvent_UnitAttackLog>
{
    SniffedEvent_UnitAttackLog(ObjectGuid attackerGuid, ObjectGuid victimGuid, uint32 hitInfo, uint32 damage, uint32 originalDamage, int32 overkillDamage, uint32 totalSchoolMask, uint32 totalAbsorbedDamage, uint32 totalResistedDamage, int32 blockedDamage, uint32 victimState, int32 attackerState, uint32 spellId) :
        m_attackerGuid(attackerGuid), m_victimGuid(victimGuid), m_hitInfo(hitInfo), m_damage(damage), m_originalDamage(originalDamage), m_overkillDamage(overkillDamage), m_totalSchoolMask(totalSchoolMask), m_totalAbsorbedDamage(totalAbsorbedDamage), m_totalResistedDamage(totalResistedDamage), m_blockedDamage(blockedDamage), m_victimState(victimState), m_attackerState(attackerState), m_spellId(spellId) {};
    ObjectGuid m_attackerGuid;
    ObjectGuid m_victimGuid;
    uint32 m_hitInfo = 0;
    uint32 m_damage = 0;
    uint32 m_originalDamage = 0;
    int32 m_overkillDamage = 0;
    uint32 m_totalSchoolMask = 0;
    uint32 m_totalAbsorbedDamage = 0;
    uint32 m_totalResistedDamage = 0;
    int32 m_blockedDamage = 0;
    uint32 m_victimState = 0;
    int32 m_attackerState = 0;
    uint32 m_spellId = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_ATTACK_LOG;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_attackerGuid;
    }
    ObjectGuid GetTargetGuid() const final
    {
        return m_victimGuid;
    }
};

struct SniffedEvent_UnitEmote : SniffedEventCRTP<SniffedEvent_UnitEmote>
{
    SniffedEvent_UnitEmote(ObjectGuid objectGuid, uint32 emoteId) :
        m_objectGuid(objectGuid), m_emoteId(emoteId) {};
    ObjectGuid m_objectGuid;
    uint32 m_emoteId = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_EMOTE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_ClientSideMovement : SniffedEventCRTP<SniffedEvent_ClientSideMovement>
{
    SniffedEvent_ClientSideMovement(ObjectGuid moverGuid, std::string opcodeName, uint32 moveTime, uint32 moveFlags, uint32 moveFlags2, uint16 mapId, float x, float y, float z, float o, ObjectGuid transportGuid, float transportX, float transportY, float transportZ, float transportO, float swimPitch, uint32 fallTime, float jumpSpeedXY, float jumpSpeedZ, float jumpCosAngle, float jumpSinAngle, float splineElevation) :
        m_moverGuid(moverGuid), m_opcodeName(opcodeName), m_moveTime(moveTime), m_moveFlags(moveFlags), m_moveFlags2(moveFlags2), m_location(mapId, x, y, z, o), m_transportGuid(transportGuid), m_transportPosition(transportX, transportY, transportZ, transportO), m_swimPitch(swimPitch), m_fallTime(fallTime), m_jumpInfo(jumpSpeedZ, jumpCosAngle, jumpSinAngle, jumpSpeedXY), m_splineElevation(splineElevation) {};

    ObjectGuid m_moverGuid;
    uint32 m_opcode = 0;
    std::string m_opcodeName;
    uint32 m_moveTime = 0;
    uint32 m_moveFlags = 0;
    uint32 m_moveFlags2 = 0;
    WorldLocation m_location;
    ObjectGuid m_transportGuid;
    Position m_transportPosition;
    float m_swimPitch = 0;
    uint32 m_fallTime = 0;
    JumpInfo m_jumpInfo;
    float m_splineElevation = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_CLIENTSIDE_MOVEMENT;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_moverGuid;
    }
};

struct SniffedEvent_ServerSideMovement : SniffedEventCRTP<SniffedEvent_ServerSideMovement>
{
    SniffedEvent_ServerSideMovement(ObjectGuid moverGuid, Vector3 const& startPosition, uint32 moveTime, uint32 splineFlags, float finalOrientation, std::vector<Vector3> const& splines, ObjectGuid transportGuid) :
        m_moverGuid(moverGuid), m_startPosition(startPosition), m_moveTime(moveTime), m_splineFlags(splineFlags), m_finalOrientation(finalOrientation), m_splines(splines), m_transportGuid(transportGuid) {};
    
    ObjectGuid m_moverGuid;
    Vector3 m_startPosition;
    uint32 m_moveTime = 0;
    uint8 m_splineType = 0;
    uint32 m_splineFlags = 0;
    float m_finalOrientation = 0.0f;
    std::vector<Vector3> const m_splines;
    ObjectGuid m_transportGuid;
    bool m_cyclic = false;
    bool m_catmullrom = false;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_SERVERSIDE_MOVEMENT;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_moverGuid;
    }
};

struct SniffedEvent_UnitUpdate_entry : SniffedEventCRTP<SniffedEvent_UnitUpdate_entry>
{
    SniffedEvent_UnitUpdate_entry(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_ENTRY;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_scale : SniffedEventCRTP<SniffedEvent_UnitUpdate_scale>
{
    SniffedEvent_UnitUpdate_scale(ObjectGuid objectGuid, float value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    float m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_SCALE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_display_id : SniffedEventCRTP<SniffedEvent_UnitUpdate_display_id>
{
    SniffedEvent_UnitUpdate_display_id(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_DISPLAY_ID;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_mount : SniffedEventCRTP<SniffedEvent_UnitUpdate_mount>
{
    SniffedEvent_UnitUpdate_mount(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_MOUNT;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_faction : SniffedEventCRTP<SniffedEvent_UnitUpdate_faction>
{
    SniffedEvent_UnitUpdate_faction(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_FACTION;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_level : SniffedEventCRTP<SniffedEvent_UnitUpdate_level>
{
    SniffedEvent_UnitUpdate_level(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_LEVEL;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_aura_state : SniffedEventCRTP<SniffedEvent_UnitUpdate_aura_state>
{
    SniffedEvent_UnitUpdate_aura_state(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_AURA_STATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_emote_state : SniffedEventCRTP<SniffedEvent_UnitUpdate_emote_state>
{
    SniffedEvent_UnitUpdate_emote_state(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_EMOTE_STATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_stand_state : SniffedEventCRTP<SniffedEvent_UnitUpdate_stand_state>
{
    SniffedEvent_UnitUpdate_stand_state(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_STAND_STATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_vis_flags : SniffedEventCRTP<SniffedEvent_UnitUpdate_vis_flags>
{
    SniffedEvent_UnitUpdate_vis_flags(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_VIS_FLAGS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_sheath_state : SniffedEventCRTP<SniffedEvent_UnitUpdate_sheath_state>
{
    SniffedEvent_UnitUpdate_sheath_state(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_SHEATH_STATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_shapeshift_form : SniffedEventCRTP<SniffedEvent_UnitUpdate_shapeshift_form>
{
    SniffedEvent_UnitUpdate_shapeshift_form(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_SHAPESHIFT_FORM;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_npc_flags : SniffedEventCRTP<SniffedEvent_UnitUpdate_npc_flags>
{
    SniffedEvent_UnitUpdate_npc_flags(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_NPC_FLAGS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_unit_flags : SniffedEventCRTP<SniffedEvent_UnitUpdate_unit_flags>
{
    SniffedEvent_UnitUpdate_unit_flags(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_UNIT_FLAGS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_unit_flags2 : SniffedEventCRTP<SniffedEvent_UnitUpdate_unit_flags2>
{
    SniffedEvent_UnitUpdate_unit_flags2(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_UNIT_FLAGS2;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_dynamic_flags : SniffedEventCRTP<SniffedEvent_UnitUpdate_dynamic_flags>
{
    SniffedEvent_UnitUpdate_dynamic_flags(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_DYNAMIC_FLAGS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_current_health : SniffedEventCRTP<SniffedEvent_UnitUpdate_current_health>
{
    SniffedEvent_UnitUpdate_current_health(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_CURRENT_HEALTH;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_max_health : SniffedEventCRTP<SniffedEvent_UnitUpdate_max_health>
{
    SniffedEvent_UnitUpdate_max_health(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_MAX_HEALTH;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_current_mana : SniffedEventCRTP<SniffedEvent_UnitUpdate_current_mana>
{
    SniffedEvent_UnitUpdate_current_mana(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_CURRENT_MANA;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_max_mana : SniffedEventCRTP<SniffedEvent_UnitUpdate_max_mana>
{
    SniffedEvent_UnitUpdate_max_mana(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_MAX_MANA;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_bounding_radius : SniffedEventCRTP<SniffedEvent_UnitUpdate_bounding_radius>
{
    SniffedEvent_UnitUpdate_bounding_radius(ObjectGuid objectGuid, float value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    float m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_BOUNDING_RADIUS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_combat_reach : SniffedEventCRTP<SniffedEvent_UnitUpdate_combat_reach>
{
    SniffedEvent_UnitUpdate_combat_reach(ObjectGuid objectGuid, float value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    float m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_COMBAT_REACH;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_main_hand_attack_time : SniffedEventCRTP<SniffedEvent_UnitUpdate_main_hand_attack_time>
{
    SniffedEvent_UnitUpdate_main_hand_attack_time(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_MAIN_HAND_ATTACK_TIME;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_off_hand_attack_time : SniffedEventCRTP<SniffedEvent_UnitUpdate_off_hand_attack_time>
{
    SniffedEvent_UnitUpdate_off_hand_attack_time(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_OFF_HAND_ATTACK_TIME;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_channel_spell : SniffedEventCRTP<SniffedEvent_UnitUpdate_channel_spell>
{
    SniffedEvent_UnitUpdate_channel_spell(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_CHANNEL_SPELL;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_guid_value : SniffedEventCRTP<SniffedEvent_UnitUpdate_guid_value>
{
    SniffedEvent_UnitUpdate_guid_value(ObjectGuid sourceGuid, ObjectGuid targetGuid, char const* updateField) :
        m_sourceGuid(sourceGuid), m_targetGuid(targetGuid), m_updateField(updateField) {};
    ObjectGuid m_sourceGuid;
    ObjectGuid m_targetGuid;
    char const* m_updateField;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_GUID_VALUE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_sourceGuid;
    }
    ObjectGuid GetTargetGuid() const final
    {
        return m_targetGuid;
    }
};

struct SniffedEvent_UnitUpdate_speed : SniffedEventCRTP<SniffedEvent_UnitUpdate_speed>
{
    SniffedEvent_UnitUpdate_speed(ObjectGuid objectGuid, uint32 speedType, float speedRate) :
        m_objectGuid(objectGuid), m_speedType(speedType), m_speedRate(speedRate) {};
    ObjectGuid m_objectGuid;
    uint32 m_speedType = 0;
    float m_speedRate = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_SPEED;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_UnitUpdate_auras : SniffedEventCRTP<SniffedEvent_UnitUpdate_auras>
{
    SniffedEvent_UnitUpdate_auras(ObjectGuid objectGuid, uint32 slot, Aura aura) :
        m_objectGuid(objectGuid), m_slot(slot), m_aura(aura) {};
    ObjectGuid m_objectGuid;
    uint32 m_slot = 0;
    Aura m_aura;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_AURAS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_CreatureText : SniffedEventCRTP<SniffedEvent_CreatureText>
{
    SniffedEvent_CreatureText(ObjectGuid senderGuid, std::string creatureName, std::string text, uint32 chatType, uint32 language) :
        m_senderGuid(senderGuid), m_creatureName(creatureName), m_text(text), m_chatType(chatType), m_language(language) {};
    ObjectGuid m_senderGuid;
    std::string m_creatureName;
    std::string m_text;
    uint32 m_chatType = 0;
    uint32 m_language = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_TEXT;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_senderGuid;
    }
};

struct SniffedEvent_CreatureEquipmentUpdate : SniffedEventCRTP<SniffedEvent_CreatureEquipmentUpdate>
{
    SniffedEvent_CreatureEquipmentUpdate(ObjectGuid objectGuid, uint32 slot, uint32 itemId) :
        m_objectGuid(objectGuid), m_slot(slot), m_itemId(itemId) {};
    ObjectGuid m_objectGuid;
    uint32 m_slot = 0;
    uint32 m_itemId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_EQUIPMENT_UPDATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_PlayerChat : SniffedEventCRTP<SniffedEvent_PlayerChat>
{
    SniffedEvent_PlayerChat(ObjectGuid senderGuid, std::string senderName, std::string text, uint8 chatType, std::string channelName) :
        m_senderGuid(senderGuid), m_senderName(senderName), m_text(text), m_chatType(chatType), m_channelName(channelName) {};
    ObjectGuid m_senderGuid;
    std::string m_senderName;
    std::string m_text;
    uint8 m_chatType = 0;
    std::string m_channelName;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_PLAYER_CHAT;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_senderGuid;
    }
};

struct SniffedEvent_PlayerEquipmentUpdate : SniffedEventCRTP<SniffedEvent_PlayerEquipmentUpdate>
{
    SniffedEvent_PlayerEquipmentUpdate(ObjectGuid objectGuid, uint32 slot, uint32 itemId) :
        m_objectGuid(objectGuid), m_slot(slot), m_itemId(itemId) {};
    ObjectGuid m_objectGuid;
    uint32 m_slot = 0;
    uint32 m_itemId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAYER_EQUIPMENT_UPDATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_GameObjectCustomAnim : SniffedEventCRTP<SniffedEvent_GameObjectCustomAnim>
{
    SniffedEvent_GameObjectCustomAnim(ObjectGuid objectGuid, uint32 animId) :
        m_objectGuid(objectGuid), m_animId(animId) {};
    ObjectGuid m_objectGuid;
    uint32 m_animId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_CUSTOM_ANIM;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_GameObjectDespawnAnim : SniffedEventCRTP<SniffedEvent_GameObjectDespawnAnim>
{
    SniffedEvent_GameObjectDespawnAnim(ObjectGuid objectGuid) :
        m_objectGuid(objectGuid) {};
    ObjectGuid m_objectGuid;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_DESPAWN_ANIM;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_GameObjectUpdate_flags : SniffedEventCRTP<SniffedEvent_GameObjectUpdate_flags>
{
    SniffedEvent_GameObjectUpdate_flags(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_FLAGS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_GameObjectUpdate_state : SniffedEventCRTP<SniffedEvent_GameObjectUpdate_state>
{
    SniffedEvent_GameObjectUpdate_state(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_STATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_GameObjectUpdate_artkit : SniffedEventCRTP<SniffedEvent_GameObjectUpdate_artkit>
{
    SniffedEvent_GameObjectUpdate_artkit(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_ARTKIT;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_GameObjectUpdate_dynamic_flags : SniffedEventCRTP<SniffedEvent_GameObjectUpdate_dynamic_flags>
{
    SniffedEvent_GameObjectUpdate_dynamic_flags(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_DYNAMIC_FLAGS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_GameObjectUpdate_path_progress : SniffedEventCRTP<SniffedEvent_GameObjectUpdate_path_progress>
{
    SniffedEvent_GameObjectUpdate_path_progress(ObjectGuid objectGuid, uint32 value) :
        m_objectGuid(objectGuid), m_value(value) {};
    ObjectGuid m_objectGuid;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_PATH_PROGRESS;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_objectGuid;
    }
};

struct SniffedEvent_PlayMusic : SniffedEventCRTP<SniffedEvent_PlayMusic>
{
    SniffedEvent_PlayMusic(uint32 musicId) :
        m_musicId(musicId) {};
    uint32 m_musicId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAY_MUSIC;
    }
};

struct SniffedEvent_PlaySound : SniffedEventCRTP<SniffedEvent_PlaySound>
{
    SniffedEvent_PlaySound(ObjectGuid sourceGuid, uint32 soundId) :
        m_sourceGuid(sourceGuid), m_soundId(soundId) {};
    ObjectGuid m_sourceGuid;
    uint32 m_soundId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAY_SOUND;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_sourceGuid;
    }
};

struct SniffedEvent_PlaySpellVisualKit : SniffedEventCRTP<SniffedEvent_PlaySpellVisualKit>
{
    SniffedEvent_PlaySpellVisualKit(ObjectGuid casterGuid, uint32 kitId) :
        m_casterGuid(casterGuid), m_kitId(kitId) {};
    ObjectGuid m_casterGuid;
    uint32 m_kitId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAY_SPELL_VISUAL_KIT;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_casterGuid;
    }
};

struct SniffedEvent_SpellCastFailed : SniffedEventCRTP<SniffedEvent_SpellCastFailed>
{
    SniffedEvent_SpellCastFailed(ObjectGuid casterGuid, uint32 spellId, uint32 reason) :
        m_casterGuid(casterGuid), m_spellId(spellId), m_reason(reason) {};
    ObjectGuid m_casterGuid;
    uint32 m_spellId = 0;
    uint32 m_reason = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CAST_FAILED;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_casterGuid;
    }
};

struct SniffedEvent_SpellCastStart : SniffedEventCRTP<SniffedEvent_SpellCastStart>
{
    SniffedEvent_SpellCastStart(ObjectGuid casterGuid, ObjectGuid casterUnitGuid, ObjectGuid targetGuid, uint32 spellId, uint32 castTime, uint32 castFlags, uint32 ammoDisplayId, uint32 ammoInventoryType) :
        m_casterGuid(casterGuid), m_casterUnitGuid(casterUnitGuid), m_targetGuid(targetGuid), m_spellId(spellId), m_castTime(castTime), m_castFlags(castFlags), m_ammoDisplayId(ammoDisplayId), m_ammoInventoryType(ammoInventoryType) {};
    ObjectGuid m_casterGuid;
    ObjectGuid m_casterUnitGuid;
    ObjectGuid m_targetGuid;
    uint32 m_spellId = 0;
    uint32 m_castTime = 0;
    uint32 m_castFlags = 0;
    uint32 m_ammoDisplayId = 0;
    uint32 m_ammoInventoryType = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CAST_START;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_casterGuid;
    }
    ObjectGuid GetTargetGuid() const final
    {
        return m_targetGuid;
    }
};

struct SniffedEvent_SpellCastGo : SniffedEventCRTP<SniffedEvent_SpellCastGo>
{
    SniffedEvent_SpellCastGo(ObjectGuid casterGuid, ObjectGuid casterUnitGuid, uint32 spellId, uint32 castFlags, uint32 ammoDisplayId, uint32 ammoInventoryType, ObjectGuid mainTargetGuid, std::vector<ObjectGuid> hitTargets, std::vector<ObjectGuid> missTargets, Vector3 sourcePosition, Vector3 destinationPosition) :
        m_casterGuid(casterGuid), m_casterUnitGuid(casterUnitGuid), m_spellId(spellId), m_castFlags(castFlags), m_ammoDisplayId(ammoDisplayId), m_ammoInventoryType(ammoInventoryType), m_mainTargetGuid(mainTargetGuid), m_hitTargets(hitTargets), m_missTargets(missTargets), m_sourcePosition(sourcePosition), m_destinationPosition(destinationPosition) {};
    uint32 m_spellId = 0;
    uint32 m_castFlags = 0;
    uint32 m_ammoDisplayId = 0;
    uint32 m_ammoInventoryType = 0;
    ObjectGuid m_casterGuid;
    ObjectGuid m_casterUnitGuid;
    ObjectGuid m_mainTargetGuid;
    std::vector<ObjectGuid> m_hitTargets;
    std::vector<ObjectGuid> m_missTargets;
    Vector3 m_sourcePosition;
    Vector3 m_destinationPosition;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CAST_GO;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_casterGuid;
    }
    ObjectGuid GetTargetGuid() const final
    {
        return m_mainTargetGuid;
    }
};

struct SniffedEvent_SpellChannelStart : SniffedEventCRTP<SniffedEvent_SpellChannelStart>
{
    SniffedEvent_SpellChannelStart(ObjectGuid casterGuid, uint32 spellId, int32 duration) :
        m_casterGuid(casterGuid), m_spellId(spellId), m_duration(duration) {};
    ObjectGuid m_casterGuid;
    uint32 m_spellId = 0;
    int32 m_duration = 0;
    void Execute() const final;
    void PepareForCurrentClient() final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CHANNEL_START;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_casterGuid;
    }
};

struct SniffedEvent_SpellChannelUpdate : SniffedEventCRTP<SniffedEvent_SpellChannelUpdate>
{
    SniffedEvent_SpellChannelUpdate(ObjectGuid casterGuid, int32 duration) :
        m_casterGuid(casterGuid), m_duration(duration) {};
    ObjectGuid m_casterGuid;
    int32 m_duration = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CHANNEL_UPDATE;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_casterGuid;
    }
};

struct SniffedEvent_Client_QuestAccept : SniffedEventCRTP<SniffedEvent_Client_QuestAccept>
{
    SniffedEvent_Client_QuestAccept(uint32 questId, ObjectGuid questStarterGuid) :
        m_questId(questId), m_questStarterGuid(questStarterGuid) {};
    uint32 m_questId = 0;
    ObjectGuid m_questStarterGuid;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_QUEST_ACCEPT;
    }
};

struct SniffedEvent_Client_QuestComplete : SniffedEventCRTP<SniffedEvent_Client_QuestComplete>
{
    SniffedEvent_Client_QuestComplete(uint32 questId, ObjectGuid questEnderGuid) :
        m_questId(questId), m_questEnderGuid(questEnderGuid) {};
    uint32 m_questId = 0;
    ObjectGuid m_questEnderGuid;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_QUEST_COMPLETE;
    }
};

struct SniffedEvent_Client_CreatureInteract : SniffedEventCRTP<SniffedEvent_Client_CreatureInteract>
{
    SniffedEvent_Client_CreatureInteract(ObjectGuid creatureGuid) :
        m_creatureGuid(creatureGuid) {};
    ObjectGuid m_creatureGuid;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_CREATURE_INTERACT;
    }
};

struct SniffedEvent_Client_GameObjectUse : SniffedEventCRTP<SniffedEvent_Client_GameObjectUse>
{
    SniffedEvent_Client_GameObjectUse(ObjectGuid objectGuid) :
        m_objectGuid(objectGuid) {};
    ObjectGuid m_objectGuid;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_GAMEOBJECT_USE;
    }
};

struct SniffedEvent_Client_ItemUse : SniffedEventCRTP<SniffedEvent_Client_ItemUse>
{
    SniffedEvent_Client_ItemUse(uint32 itemId) :
        m_itemId(itemId) {};
    uint32 m_itemId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_ITEM_USE;
    }
};

struct SniffedEvent_Client_ReclaimCorpse : SniffedEventCRTP<SniffedEvent_Client_ReclaimCorpse>
{
    SniffedEvent_Client_ReclaimCorpse() {};
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_RECLAIM_CORPSE;
    }
};

struct SniffedEvent_Client_ReleaseSpirit : SniffedEventCRTP<SniffedEvent_Client_ReleaseSpirit>
{
    SniffedEvent_Client_ReleaseSpirit() {};
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_RELEASE_SPIRIT;
    }
};

struct SniffedEvent_QuestUpdateComplete : SniffedEventCRTP<SniffedEvent_QuestUpdateComplete>
{
    SniffedEvent_QuestUpdateComplete(uint32 questId) : m_questId(questId) {};
    uint32 m_questId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_QUEST_UPDATE_COMPLETE;
    }
};

struct SniffedEvent_QuestUpdateFailed : SniffedEventCRTP<SniffedEvent_QuestUpdateFailed>
{
    SniffedEvent_QuestUpdateFailed(uint32 questId) : m_questId(questId) {};
    uint32 m_questId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_QUEST_UPDATE_FAILED;
    }
};

struct SniffedEvent_XPGainLog : SniffedEventCRTP<SniffedEvent_XPGainLog>
{
    SniffedEvent_XPGainLog(ObjectGuid victimGuid, uint32 originalAmount, uint32 amount, float groupBonus, bool rafBonus) :
        m_victimGuid(victimGuid), m_originalAmount(originalAmount), m_amount(amount), m_groupBonus(groupBonus), m_rafBonus(rafBonus) {};
    ObjectGuid m_victimGuid;
    uint32 m_originalAmount = 0;
    uint32 m_amount = 0;
    float m_groupBonus = 0.0f;
    bool m_rafBonus = false;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_XP_GAIN_LOG;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_victimGuid;
    }
};

struct SniffedEvent_FactionStandingUpdate : SniffedEventCRTP<SniffedEvent_FactionStandingUpdate>
{
    SniffedEvent_FactionStandingUpdate(uint32 reputationListId, uint32 standing, float rafBonus, bool showVisual) :
        m_reputationListId(reputationListId), m_standing(standing), m_rafBonus(rafBonus), m_showVisual(showVisual) {};
    uint32 m_reputationListId = 0;
    uint32 m_standing = 0;
    float m_rafBonus = 0.0f;
    bool m_showVisual = false;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_FACTION_STANDING_UPDATE;
    }
};

#endif

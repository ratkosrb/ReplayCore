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
#include <string>

enum SniffedEventType : uint8
{
    SE_WEATHER_UPDATE,
    SE_WORLD_TEXT,
    SE_WORLD_STATE_UPDATE,
    SE_CREATURE_TEXT,
    SE_CREATURE_EQUIPMENT_UPDATE,
    SE_UNIT_ATTACK_LOG,
    SE_UNIT_ATTACK_START,
    SE_UNIT_ATTACK_STOP,
    SE_WORLDOBJECT_CREATE1,
    SE_WORLDOBJECT_CREATE2,
    SE_WORLDOBJECT_DESTROY,
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
    SE_UNIT_UPDATE_CURRENT_HEALTH,
    SE_UNIT_UPDATE_MAX_HEALTH,
    SE_UNIT_UPDATE_CURRENT_MANA,
    SE_UNIT_UPDATE_MAX_MANA,
    SE_UNIT_UPDATE_BOUNDING_RADIUS,
    SE_UNIT_UPDATE_COMBAT_REACH,
    SE_UNIT_UPDATE_MAIN_HAND_ATTACK_TIME,
    SE_UNIT_UPDATE_OFF_HAND_ATTACK_TIME,
    SE_UNIT_UPDATE_GUID_VALUE,
    SE_UNIT_UPDATE_SPEED,
    SE_UNIT_UPDATE_AURAS,
    SE_DYNAMICOBJECT_CREATE,
    SE_GAMEOBJECT_CREATE1,
    SE_GAMEOBJECT_CREATE2,
    SE_GAMEOBJECT_CUSTOM_ANIM,
    SE_GAMEOBJECT_DESPAWN_ANIM,
    SE_GAMEOBJECT_DESTROY,
    SE_GAMEOBJECT_UPDATE_FLAGS,
    SE_GAMEOBJECT_UPDATE_STATE,
    SE_GAMEOBJECT_UPDATE_ARTKIT,
    SE_PLAYER_CHAT,
    SE_PLAYER_EQUIPMENT_UPDATE,
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
        case SE_WORLDOBJECT_CREATE1:
            return "WorldObject Create 1";
        case SE_WORLDOBJECT_CREATE2:
            return "WorldObject Create 2";
        case SE_WORLDOBJECT_DESTROY:
            return "WorldObject Destroy";
        case SE_CREATURE_TEXT:
            return "Creature Text";
        case SE_CREATURE_EQUIPMENT_UPDATE:
            return "Creature Equipment Update";
        case SE_UNIT_EMOTE:
            return "Unit Emote";
        case SE_UNIT_ATTACK_LOG:
            return "Unit Attack Log";
        case SE_UNIT_ATTACK_START:
            return "Unit Attack Start";
        case SE_UNIT_ATTACK_STOP:
            return "Unit Attack Stop";
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
        case SE_UNIT_UPDATE_GUID_VALUE:
            return "Unit Update GUID Value";
        case SE_UNIT_UPDATE_SPEED:
            return "Unit Update Speed";
        case SE_UNIT_UPDATE_AURAS:
            return "Unit Update Auras";
        case SE_DYNAMICOBJECT_CREATE:
            return "DynamicObject Create";
        case SE_GAMEOBJECT_CREATE1:
            return "GameObject Create 1";
        case SE_GAMEOBJECT_CREATE2:
            return "GameObject Create 2";
        case SE_GAMEOBJECT_CUSTOM_ANIM:
            return "GameObject Custom Anim";
        case SE_GAMEOBJECT_DESPAWN_ANIM:
            return "GameObject Despawn Anim";
        case SE_GAMEOBJECT_DESTROY:
            return "GameObject Destroy";
        case SE_GAMEOBJECT_UPDATE_FLAGS:
            return "GameObject Update Flags";
        case SE_GAMEOBJECT_UPDATE_STATE:
            return "GameObject Update State";
        case SE_GAMEOBJECT_UPDATE_ARTKIT:
            return "GameObject Update ArtKit";
        case SE_PLAYER_CHAT:
            return "Player Chat";
        case SE_PLAYER_EQUIPMENT_UPDATE:
            return "Player Equipment Update";
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
    virtual void Execute() const = 0;
    virtual void PepareForCurrentClient() { };
    virtual SniffedEventType GetType() const = 0;
    virtual ObjectGuid GetSourceGuid() const { return ObjectGuid(); };
    virtual ObjectGuid GetTargetGuid() const { return ObjectGuid(); };
};

struct SniffedEvent_WeatherUpdate : SniffedEvent
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

struct SniffedEvent_WorldText : SniffedEvent
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

struct SniffedEvent_WorldStateUpdate : SniffedEvent
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

struct SniffedEvent_WorldObjectCreate1 : SniffedEvent
{
    SniffedEvent_WorldObjectCreate1(ObjectGuid source, uint32 mapId, float x, float y, float z, float o) :
        m_source(source), m_location(mapId, x, y, z, o) {};
    ObjectGuid m_source;
    WorldLocation m_location;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_WORLDOBJECT_CREATE1;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_source;
    }
};

struct SniffedEvent_WorldObjectCreate2 : SniffedEvent
{
    SniffedEvent_WorldObjectCreate2(ObjectGuid source, uint32 mapId, float x, float y, float z, float o) :
        m_source(source), m_location(mapId, x, y, z, o) {};
    ObjectGuid m_source;
    WorldLocation m_location;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_WORLDOBJECT_CREATE2;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_source;
    }
};

struct SniffedEvent_WorldObjectDestroy : SniffedEvent
{
    SniffedEvent_WorldObjectDestroy(ObjectGuid source) : m_source(source) {};
    ObjectGuid m_source;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_WORLDOBJECT_DESTROY;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_source;
    }
};

struct SniffedEvent_ClientSideMovement : SniffedEvent
{
    SniffedEvent_ClientSideMovement(ObjectGuid source, std::string opcodeName, uint32 moveTime, uint32 moveFlags, uint16 mapId, float x, float y, float z, float o) :
        m_source(source), m_opcodeName(opcodeName), m_moveTime(moveTime), m_moveFlags(moveFlags), m_location(mapId, x, y, z, o) {};

    ObjectGuid m_source;
    uint32 m_opcode = 0;
    std::string m_opcodeName;
    uint32 m_moveTime = 0;
    uint32 m_moveFlags = 0;
    WorldLocation m_location;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_CLIENTSIDE_MOVEMENT;
    }
    ObjectGuid GetSourceGuid() const final
    {
        return m_source;
    }
};

/*

struct SniffedEvent_UnitDestroy : SniffedEvent
{
    SniffedEvent_UnitDestroy(uint32 guid, uint32 entry, uint32 type) : m_guid(guid), m_entry(entry), m_type(type) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_DESTROY;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_ServerSideMovement : SniffedEvent
{
    SniffedEvent_ServerSideMovement(uint32 guid, uint32 entry, uint32 typeId, uint32 moveTime, uint32 splineFlags, float x, float y, float z, float o, std::vector<G3D::Vector3> const* splines) :
        m_guid(guid), m_entry(entry), m_typeId(typeId), m_moveTime(moveTime), m_splineFlags(splineFlags), m_x(x), m_y(y), m_z(z), m_o(o), m_splines(splines) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_typeId = 0;
    uint32 m_moveTime = 0;
    uint32 m_splineFlags = 0;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_o = 0.0f;
    std::vector<G3D::Vector3> const* m_splines;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_SERVERSIDE_MOVEMENT;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_typeId));
    }
};

struct SniffedEvent_UnitUpdate_orientation : SniffedEvent
{
    SniffedEvent_UnitUpdate_orientation(uint32 guid, uint32 entry, uint32 typeId, float o) :
        m_guid(guid), m_entry(entry), m_typeId(typeId), m_o(o) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_typeId = 0;
    float m_o = 0.0f;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_ORIENTATION;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_typeId));
    }
};

struct SniffedEvent_CreatureText : SniffedEvent
{
    SniffedEvent_CreatureText(uint32 guid, uint32 entry, std::string text, uint32 chatType) : 
        m_guid(guid), m_entry(entry), m_chatType(chatType), m_text(text) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_chatType = 0;
    std::string m_text;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_TEXT;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_UNIT);
    }
};

struct SniffedEvent_CreatureEquipmentUpdate : SniffedEvent
{
    SniffedEvent_CreatureEquipmentUpdate(uint32 guid, uint32 entry, uint32 slot, uint32 itemId) :
        m_guid(guid), m_entry(entry), m_slot(slot), m_itemId(itemId) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_slot = 0;
    uint32 m_itemId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CREATURE_EQUIPMENT_UPDATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_UNIT);
    }
};

struct SniffedEvent_UnitEmote : SniffedEvent
{
    SniffedEvent_UnitEmote(uint32 guid, uint32 entry, uint32 type, uint32 emoteId) : 
        m_guid(guid), m_entry(entry), m_type(type), m_emoteId(emoteId) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_emoteId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_EMOTE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitAttackLog : SniffedEvent
{
    SniffedEvent_UnitAttackLog(uint32 guid, uint32 entry, uint32 type, uint32 victimGuid, uint32 victimId, uint32 victimType, uint32 hitInfo, uint32 damage, int32 blockedDamage, uint32 victimState, int32 attackerState, uint32 spellId) :
        m_guid(guid), m_entry(entry), m_type(type), m_victimGuid(victimGuid), m_victimId(victimId), m_victimType(victimType), m_hitInfo(hitInfo), m_damage(damage), m_blockedDamage(blockedDamage), m_victimState(victimState), m_attackerState(attackerState), m_spellId(spellId) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_victimGuid = 0;
    uint32 m_victimId = 0;
    uint32 m_victimType = 0;
    uint32 m_hitInfo = 0;
    uint32 m_damage = 0;
    int32 m_blockedDamage = 0;
    uint32 m_victimState = 0;
    int32 m_attackerState = 0;
    uint32 m_spellId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_ATTACK_START;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_victimGuid, m_victimId, TypeID(m_victimType));
    }
};

struct SniffedEvent_UnitAttackStart : SniffedEvent
{
    SniffedEvent_UnitAttackStart(uint32 guid, uint32 entry, uint32 type, uint32 victimGuid, uint32 victimId, uint32 victimType) :
        m_guid(guid), m_entry(entry), m_type(type), m_victimGuid(victimGuid), m_victimId(victimId), m_victimType(victimType) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_victimGuid = 0;
    uint32 m_victimId = 0;
    uint32 m_victimType = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_ATTACK_START;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_victimGuid, m_victimId, TypeID(m_victimType));
    }
};

struct SniffedEvent_UnitAttackStop : SniffedEvent
{
    SniffedEvent_UnitAttackStop(uint32 guid, uint32 entry, uint32 type, uint32 victimGuid, uint32 victimId, uint32 victimType) :
        m_guid(guid), m_entry(entry), m_type(type), m_victimGuid(victimGuid), m_victimId(victimId), m_victimType(victimType) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_victimGuid = 0;
    uint32 m_victimId = 0;
    uint32 m_victimType;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_ATTACK_STOP;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_victimGuid, m_victimId, TypeID(m_victimType));
    }
};

struct SniffedEvent_UnitUpdate_entry : SniffedEvent
{
    SniffedEvent_UnitUpdate_entry(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_ENTRY;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_scale : SniffedEvent
{
    SniffedEvent_UnitUpdate_scale(uint32 guid, uint32 entry, uint32 type, float value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    float m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_SCALE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_display_id : SniffedEvent
{
    SniffedEvent_UnitUpdate_display_id(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_DISPLAY_ID;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_mount : SniffedEvent
{
    SniffedEvent_UnitUpdate_mount(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_MOUNT;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_faction : SniffedEvent
{
    SniffedEvent_UnitUpdate_faction(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_FACTION;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_level : SniffedEvent
{
    SniffedEvent_UnitUpdate_level(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_LEVEL;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_aura_state : SniffedEvent
{
    SniffedEvent_UnitUpdate_aura_state(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_AURA_STATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};


struct SniffedEvent_UnitUpdate_emote_state : SniffedEvent
{
    SniffedEvent_UnitUpdate_emote_state(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_EMOTE_STATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_stand_state : SniffedEvent
{
    SniffedEvent_UnitUpdate_stand_state(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_STAND_STATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_vis_flags : SniffedEvent
{
    SniffedEvent_UnitUpdate_vis_flags(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_VIS_FLAGS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_sheath_state : SniffedEvent
{
    SniffedEvent_UnitUpdate_sheath_state(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_SHEATH_STATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_shapeshift_form : SniffedEvent
{
    SniffedEvent_UnitUpdate_shapeshift_form(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_SHAPESHIFT_FORM;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_npc_flags : SniffedEvent
{
    SniffedEvent_UnitUpdate_npc_flags(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_NPC_FLAGS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_unit_flags : SniffedEvent
{
    SniffedEvent_UnitUpdate_unit_flags(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_UNIT_FLAGS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_current_health : SniffedEvent
{
    SniffedEvent_UnitUpdate_current_health(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_CURRENT_HEALTH;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_max_health : SniffedEvent
{
    SniffedEvent_UnitUpdate_max_health(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_MAX_HEALTH;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_current_mana : SniffedEvent
{
    SniffedEvent_UnitUpdate_current_mana(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_CURRENT_MANA;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_max_mana : SniffedEvent
{
    SniffedEvent_UnitUpdate_max_mana(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_MAX_MANA;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_bounding_radius : SniffedEvent
{
    SniffedEvent_UnitUpdate_bounding_radius(uint32 guid, uint32 entry, uint32 type, float value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    float m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_BOUNDING_RADIUS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_combat_reach : SniffedEvent
{
    SniffedEvent_UnitUpdate_combat_reach(uint32 guid, uint32 entry, uint32 type, float value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    float m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_COMBAT_REACH;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_main_hand_attack_time : SniffedEvent
{
    SniffedEvent_UnitUpdate_main_hand_attack_time(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_MAIN_HAND_ATTACK_TIME;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_off_hand_attack_time : SniffedEvent
{
    SniffedEvent_UnitUpdate_off_hand_attack_time(uint32 guid, uint32 entry, uint32 type, uint32 value) :
        m_guid(guid), m_entry(entry), m_type(type), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_OFF_HAND_ATTACK_TIME;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_guid_value : SniffedEvent
{
    SniffedEvent_UnitUpdate_guid_value(uint32 guid, uint32 entry, uint32 type, uint32 objectGuid, uint32 objectId, uint32 objectType, uint32 updateField) :
        m_guid(guid), m_entry(entry), m_type(type), m_objectGuid(objectGuid), m_objectId(objectId), m_objectType(objectType), m_updateField(updateField) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_objectGuid = 0;
    uint32 m_objectId = 0;
    uint32 m_objectType;
    uint32 m_updateField;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_GUID_VALUE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_objectGuid, m_objectId, TypeID(m_objectType));
    }
};

struct SniffedEvent_UnitUpdate_speed : SniffedEvent
{
    SniffedEvent_UnitUpdate_speed(uint32 guid, uint32 entry, uint32 type, uint32 speedType, float speedRate) :
        m_guid(guid), m_entry(entry), m_type(type), m_speedType(speedType), m_speedRate(speedRate) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_speedType = 0;
    float m_speedRate = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_SPEED;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct SniffedEvent_UnitUpdate_auras : SniffedEvent
{
    SniffedEvent_UnitUpdate_auras(uint32 guid, uint32 entry, uint32 type, uint32 updateId, uint32 slot, uint32 spellId, uint32 level, uint32 charges) :
        m_guid(guid), m_entry(entry), m_type(type), m_updateId(updateId), m_slot(slot), m_spellId(spellId), m_level(level), m_charges(charges) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_type = 0;
    uint32 m_updateId = 0;
    uint32 m_slot = 0;
    uint32 m_spellId = 0;
    uint32 m_level = 0;
    uint32 m_charges = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_UNIT_UPDATE_AURAS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TypeID(m_type));
    }
};

struct DynamicObjectSpawn
{
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    uint32 m_casterType;
    uint32 m_map = 0;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_o = 0.0f;
    uint32 m_spellId = 0;
    float m_radius = 0.0f;
    uint32 m_type = 0;
};

struct SniffedEvent_DynamicObjectCreate : SniffedEvent
{
    SniffedEvent_DynamicObjectCreate(DynamicObjectSpawn objectData, uint32 duration) :
        m_objectData(objectData), m_duration(duration) {};
    DynamicObjectSpawn m_objectData;
    uint32 m_duration = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_DYNAMICOBJECT_CREATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_objectData.m_casterGuid, m_objectData.m_casterId, TypeID(m_objectData.m_casterType));
    }
};

struct SniffedEvent_GameObjectCreate1 : SniffedEvent
{
    SniffedEvent_GameObjectCreate1(uint32 guid, uint32 entry, float x, float y, float z, float o) :
        m_guid(guid), m_entry(entry), m_x(x), m_y(y), m_z(z), m_o(o) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_o = 0.0f;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_CREATE1;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_GAMEOBJECT);
    }
};

struct SniffedEvent_GameObjectCreate2 : SniffedEvent
{
    SniffedEvent_GameObjectCreate2(uint32 guid, uint32 entry, float x, float y, float z, float o) :
        m_guid(guid), m_entry(entry), m_x(x), m_y(y), m_z(z), m_o(o) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;
    float m_o = 0.0f;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_CREATE2;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_GAMEOBJECT);
    }
};

struct SniffedEvent_GameObjectCustomAnim : SniffedEvent
{
    SniffedEvent_GameObjectCustomAnim(uint32 guid, uint32 entry, uint32 animId) : m_guid(guid), m_entry(entry), m_animId(animId) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_animId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_CUSTOM_ANIM;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_GAMEOBJECT);
    }
};

struct SniffedEvent_GameObjectDespawnAnim : SniffedEvent
{
    SniffedEvent_GameObjectDespawnAnim(uint32 guid, uint32 entry) : m_guid(guid), m_entry(entry) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_DESPAWN_ANIM;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_GAMEOBJECT);
    }
};

struct SniffedEvent_GameObjectDestroy : SniffedEvent
{
    SniffedEvent_GameObjectDestroy(uint32 guid, uint32 entry) : m_guid(guid), m_entry(entry) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_DESTROY;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_GAMEOBJECT);
    }
};

struct SniffedEvent_GameObjectUpdate_flags : SniffedEvent
{
    SniffedEvent_GameObjectUpdate_flags(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_FLAGS;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_GAMEOBJECT);
    }
};

struct SniffedEvent_GameObjectUpdate_state : SniffedEvent
{
    SniffedEvent_GameObjectUpdate_state(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_STATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_GAMEOBJECT);
    }
};

struct SniffedEvent_GameObjectUpdate_artkit : SniffedEvent
{
    SniffedEvent_GameObjectUpdate_artkit(uint32 guid, uint32 entry, uint32 value) :
        m_guid(guid), m_entry(entry), m_value(value) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    uint32 m_value = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_GAMEOBJECT_UPDATE_ARTKIT;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, m_entry, TYPEID_GAMEOBJECT);
    }
};

struct SniffedEvent_SpellCastFailed : SniffedEvent
{
    SniffedEvent_SpellCastFailed(uint32 spellId, uint32 casterGuid, uint32 casterId, uint32 casterType) :
        m_spellId(spellId), m_casterGuid(casterGuid), m_casterId(casterId), m_casterType(casterType) {};
    uint32 m_spellId = 0;
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    uint32 m_casterType = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CAST_FAILED;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_casterGuid, m_casterId, TypeID(m_casterType));
    }
};

struct SniffedEvent_SpellCastStart : SniffedEvent
{
    SniffedEvent_SpellCastStart(uint32 spellId, uint32 castTime, uint32 castFlags, uint32 ammoDisplayId, uint32 ammoInventoryType, uint32 casterGuid, uint32 casterId, uint32 casterType, uint32 targetGuid, uint32 targetId, uint32 targetType) :
        m_spellId(spellId), m_castTime(castTime), m_castFlags(castFlags), m_ammoDisplayId(ammoDisplayId), m_ammoInventoryType(ammoInventoryType), m_casterGuid(casterGuid), m_casterId(casterId), m_casterType(casterType), m_targetGuid(targetGuid), m_targetId(targetId), m_targetType(targetType) {};
    uint32 m_spellId = 0;
    uint32 m_castTime = 0;
    uint32 m_castFlags = 0;
    uint32 m_ammoDisplayId = 0;
    uint32 m_ammoInventoryType = 0;
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    uint32 m_casterType = 0;
    uint32 m_targetGuid = 0;
    uint32 m_targetId = 0;
    uint32 m_targetType = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CAST_START;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_casterGuid, m_casterId, TypeID(m_casterType));
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_targetGuid, m_targetId, TypeID(m_targetType));
    }
};

struct SniffedEvent_SpellCastGo : SniffedEvent
{
    SniffedEvent_SpellCastGo(uint32 spellId, uint32 castFlags, uint32 ammoDisplayId, uint32 ammoInventoryType, uint32 casterGuid, uint32 casterId, uint32 casterType, uint32 targetGuid, uint32 targetId, uint32 targetType, uint32 hitTargetsCount, uint32 hitTargetsListId, uint32 missTargetsCount, uint32 missTargetsListId, uint32 srcPositionId, uint32 dstPositionId) :
        m_spellId(spellId), m_castFlags(castFlags), m_ammoDisplayId(ammoDisplayId), m_ammoInventoryType(ammoInventoryType), m_casterGuid(casterGuid), m_casterId(casterId), m_casterType(casterType), m_targetGuid(targetGuid), m_targetId(targetId), m_targetType(targetType), m_hitTargetsCount(hitTargetsCount), m_hitTargetsListId(hitTargetsListId), m_missTargetsCount(missTargetsCount), m_missTargetsListId(missTargetsListId), m_srcPositionId(srcPositionId), m_dstPositionId(dstPositionId) {};
    uint32 m_spellId = 0;
    uint32 m_castFlags = 0;
    uint32 m_ammoDisplayId = 0;
    uint32 m_ammoInventoryType = 0;
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    uint32 m_casterType = 0;
    uint32 m_targetGuid = 0;
    uint32 m_targetId = 0;
    uint32 m_targetType = 0;
    uint32 m_hitTargetsCount = 0;
    uint32 m_hitTargetsListId = 0;
    uint32 m_missTargetsCount = 0;
    uint32 m_missTargetsListId = 0;
    uint32 m_srcPositionId = 0;
    uint32 m_dstPositionId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CAST_GO;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_casterGuid, m_casterId, TypeID(m_casterType));
    }
    KnownObject GetTargetObject() const final
    {
        return KnownObject(m_targetGuid, m_targetId, TypeID(m_targetType));
    }
};

struct SniffedEvent_SpellChannelStart : SniffedEvent
{
    SniffedEvent_SpellChannelStart(uint32 spellId, int32 duration, uint32 casterGuid, uint32 casterId, uint32 casterType) :
        m_spellId(spellId), m_duration(duration), m_casterGuid(casterGuid), m_casterId(casterId), m_casterType(casterType) {};
    uint32 m_spellId = 0;
    int32 m_duration = 0;
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    uint32 m_casterType = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CHANNEL_START;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_casterGuid, m_casterId, TypeID(m_casterType));
    }
};

struct SniffedEvent_SpellChannelUpdate : SniffedEvent
{
    SniffedEvent_SpellChannelUpdate(int32 duration, uint32 casterGuid, uint32 casterId, uint32 casterType) :
        m_duration(duration), m_casterGuid(casterGuid), m_casterId(casterId), m_casterType(casterType) {};
    int32 m_duration = 0;
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    uint32 m_casterType = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_SPELL_CHANNEL_UPDATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_casterGuid, m_casterId, TypeID(m_casterType));
    }
};

struct SniffedEvent_PlayerChat : SniffedEvent
{
    SniffedEvent_PlayerChat(uint32 guid, std::string senderName, std::string text, uint8 chatType, std::string channelName) :
        m_guid(guid), m_senderName(senderName), m_text(text), m_chatType(chatType), m_channelName(channelName) {};
    uint32 m_guid = 0;
    std::string m_senderName;
    std::string m_text;
    uint8 m_chatType = 0;
    std::string m_channelName;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAYER_CHAT;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, 0, TYPEID_PLAYER);
    }
};

struct SniffedEvent_PlayerEquipmentUpdate : SniffedEvent
{
    SniffedEvent_PlayerEquipmentUpdate(uint32 guid, uint32 slot, uint32 itemId) :
        m_guid(guid), m_slot(slot), m_itemId(itemId) {};
    uint32 m_guid = 0;
    uint32 m_slot = 0;
    uint32 m_itemId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAYER_EQUIPMENT_UPDATE;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_guid, 0, TYPEID_PLAYER);
    }
};

struct SniffedEvent_PlayMusic : SniffedEvent
{
    SniffedEvent_PlayMusic(uint32 music) :
        m_music(music) {};
    uint32 m_music = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAY_MUSIC;
    }
};

struct SniffedEvent_PlaySound : SniffedEvent
{
    SniffedEvent_PlaySound(uint32 sound, uint32 sourceGuid, uint32 sourceId, uint32 sourceType) :
        m_sound(sound), m_sourceGuid(sourceGuid), m_sourceId(sourceId), m_sourceType(sourceType) {};
    uint32 m_sound = 0;
    uint32 m_sourceGuid = 0;
    uint32 m_sourceId = 0;
    uint32 m_sourceType = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAY_SOUND;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_sourceGuid, m_sourceId, TypeID(m_sourceType));
    }
};

struct SniffedEvent_PlaySpellVisualKit : SniffedEvent
{
    SniffedEvent_PlaySpellVisualKit(uint32 kitId, uint32 casterGuid, uint32 casterId, uint32 casterType) :
        m_kitId(kitId), m_casterGuid(casterGuid), m_casterId(casterId), m_casterType(casterType) {};
    uint32 m_kitId = 0;
    uint32 m_casterGuid = 0;
    uint32 m_casterId = 0;
    uint32 m_casterType;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_PLAY_SPELL_VISUAL_KIT;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_casterGuid, m_casterId, TypeID(m_casterType));
    }
};

struct SniffedEvent_QuestAccept : SniffedEvent
{
    SniffedEvent_QuestAccept(uint32 questId, uint32 objectGuid, uint32 objectId, std::string objectType) :
        m_questId(questId), m_objectGuid(objectGuid), m_objectId(objectId), m_objectType(objectType) {};
    uint32 m_questId = 0;
    uint32 m_objectGuid = 0;
    uint32 m_objectId = 0;
    std::string m_objectType;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_QUEST_ACCEPT;
    }
};

struct SniffedEvent_QuestComplete : SniffedEvent
{
    SniffedEvent_QuestComplete(uint32 questId, uint32 objectGuid, uint32 objectId, std::string objectType) :
        m_questId(questId), m_objectGuid(objectGuid), m_objectId(objectId), m_objectType(objectType) {};
    uint32 m_questId = 0;
    uint32 m_objectGuid = 0;
    uint32 m_objectId = 0;
    std::string m_objectType;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_QUEST_COMPLETE;
    }
};

struct SniffedEvent_CreatureInteract : SniffedEvent
{
    SniffedEvent_CreatureInteract(uint32 guid, uint32 entry) :
        m_guid(guid), m_entry(entry) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_CREATURE_INTERACT;
    }
};

struct SniffedEvent_GameObjectUse : SniffedEvent
{
    SniffedEvent_GameObjectUse(uint32 guid, uint32 entry) :
        m_guid(guid), m_entry(entry) {};
    uint32 m_guid = 0;
    uint32 m_entry = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_GAMEOBJECT_USE;
    }
};

struct SniffedEvent_ItemUse : SniffedEvent
{
    SniffedEvent_ItemUse(uint32 itemId) :
        m_itemId(itemId) {};
    uint32 m_itemId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_ITEM_USE;
    }
};

struct SniffedEvent_ReclaimCorpse : SniffedEvent
{
    SniffedEvent_ReclaimCorpse() {};
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_RECLAIM_CORPSE;
    }
};

struct SniffedEvent_ReleaseSpirit : SniffedEvent
{
    SniffedEvent_ReleaseSpirit() {};
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_CLIENT_RELEASE_SPIRIT;
    }
};

struct SniffedEvent_QuestUpdateComplete : SniffedEvent
{
    SniffedEvent_QuestUpdateComplete(uint32 questId) : m_questId(questId) {};
    uint32 m_questId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_QUEST_UPDATE_COMPLETE;
    }
};

struct SniffedEvent_QuestUpdateFailed : SniffedEvent
{
    SniffedEvent_QuestUpdateFailed(uint32 questId) : m_questId(questId) {};
    uint32 m_questId = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_QUEST_UPDATE_FAILED;
    }
};

struct SniffedEvent_XPGainLog : SniffedEvent
{
    SniffedEvent_XPGainLog(uint32 victimGuid, uint32 victimId, uint32 victimType, uint32 originalAmount, uint32 amount, float groupBonus) :
        m_victimGuid(victimGuid), m_victimId(victimId), m_victimType(victimType), m_originalAmount(originalAmount), m_amount(amount), m_groupBonus(groupBonus) {};
    uint32 m_victimGuid = 0;
    uint32 m_victimId = 0;
    uint32 m_victimType = 0;
    uint32 m_originalAmount = 0;
    uint32 m_amount = 0;
    float m_groupBonus = 0.0f;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_XP_GAIN_LOG;
    }
    KnownObject GetSourceObject() const final
    {
        return KnownObject(m_victimGuid, m_victimId, TypeID(m_victimType));
    }
};

struct SniffedEvent_FactionStandingUpdate : SniffedEvent
{
    SniffedEvent_FactionStandingUpdate(uint32 reputationListId, uint32 standing) :
        m_reputationListId(reputationListId), m_standing(standing) {};
    uint32 m_reputationListId = 0;
    uint32 m_standing = 0;
    void Execute() const final;
    SniffedEventType GetType() const final
    {
        return SE_FACTION_STANDING_UPDATE;
    }
};

*/

#endif

#include "GUIFilters.h"
#include "../World/SniffedEvents.h"
#include "../World/WorldServer.h"

bool IsGuidFitForObjectTypeFilter(ObjectGuid guid, GUIObjectTypeFilters filter)
{
    switch (filter)
    {
        case FILTER_GAMEOBJECT:
        {
            return guid.IsGameObject();
        }
        case FILTER_TRANSPORT:
        {
            if (!guid.IsGameObject() && !guid.IsTransport() && !guid.IsMOTransport())
                return false;

            GameObject* pGo = sWorld.FindGameObject(guid);
            if (!pGo)
                return false;

            return pGo->IsTransport();
        }
        case FILTER_UNIT:
        {
            return guid.IsUnit();
        }
        case FITLER_CREATURE:
        {
            return guid.IsCreature();
        }
        case FILTER_PET:
        {
            return guid.IsPet();
        }
        case FILTER_PLAYER:
        {
            return guid.IsPlayer();
        }
    }

    return true;
}

bool ObjectFilterEntry::IsEventFitForFilter(SniffedEvent const* pEvent) const
{
    ObjectGuid sourceGuid = pEvent->GetSourceGuid();
    if (guid && guid != sourceGuid.GetCounter())
        return false;

    if (id && id != sourceGuid.GetEntry())
        return false;

    if (!IsGuidFitForObjectTypeFilter(sourceGuid, GUIObjectTypeFilters(type)))
        return false;

    return eventTypes.find(pEvent->GetType()) != eventTypes.end();
}
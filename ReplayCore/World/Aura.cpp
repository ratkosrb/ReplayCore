#include "Aura.h"
#include "SpellDefines.h"
#include "WorldServer.h"
#include "../Defines/ByteBuffer.h"
#include "../Defines/ClientVersions.h"

void Aura::Write(ByteBuffer &data) const
{
    data << uint32(spellId);

    if (sWorld.GetClientBuild() <= CLIENT_BUILD_3_3_5a)
        data << uint8(auraFlags);
    else
        data << uint16(auraFlags);

    data << uint8(level);
    data << uint8(stacks);

    if (!(auraFlags & WotLK::AFLAG_NO_CASTER))
    {
        data << casterGuid.WriteAsPacked();
    }

    if (auraFlags & WotLK::AFLAG_DURATION)
    {
        data << uint32(durationMax);
        data << uint32(duration);
    }

    if ((auraFlags & WotLK::AFLAG_SCALABLE) &&
        sWorld.GetClientBuild() > CLIENT_BUILD_3_3_5a)
    {
        if (auraFlags & WotLK::AFLAG_EFF_INDEX_0)
            data << int32(0);
        if (auraFlags & WotLK::AFLAG_EFF_INDEX_1)
            data << int32(0);
        if (auraFlags & WotLK::AFLAG_EFF_INDEX_2)
            data << int32(0);
    }
}

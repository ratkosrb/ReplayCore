#include "Aura.h"
#include "SpellDefines.h"
#include "../Defines/ByteBuffer.h"

void Aura::Write(ByteBuffer &data) const
{
    data << uint32(spellId);

    data << uint8(auraFlags);
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
}

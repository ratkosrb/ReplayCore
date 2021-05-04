#ifndef __SPELL_AURA_H
#define __SPELL_AURA_H

#include "../Defines/Common.h"
#include "ObjectGuid.h"

class ByteBuffer;

struct Aura
{
    void Write(ByteBuffer &data) const;
    uint32 spellId = 0;
    uint8 auraFlags = 0;
    uint8 activeFlags = 0; // part of the regular aura flags in wotlk
    uint8 level = 0;
    uint8 stacks = 0;
    ObjectGuid casterGuid;
    uint32 durationMax = 0;
    uint32 duration = 0;
};

inline ByteBuffer& operator<< (ByteBuffer& buf, Aura const& aura)
{
    aura.Write(buf);
    return buf;
}

#endif
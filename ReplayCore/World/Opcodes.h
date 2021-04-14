#ifndef _OPCODE_DEFS_H
#define _OPCODE_DEFS_H

#include "../Defines/Common.h"
#include <map>
#include <string>

namespace Opcodes
{
    extern std::map<std::string, uint16> g_opcodeValues5875;
    extern std::map<std::string, uint16> g_opcodeValues8606;
    extern std::map<std::string, uint16> g_opcodeValues12340;

    std::map<std::string, uint16>* GetOpcodesMapForBuild(uint16 build);
    uint16 GetOpcodeValue(std::string name, uint16 build);
    std::string GetOpcodeName(uint16 opcode, uint16 build);
}

#endif
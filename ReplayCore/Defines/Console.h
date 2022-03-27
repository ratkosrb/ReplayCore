#ifndef _CONSOLE_HELPERS_H
#define _CONSOLE_HELPERS_H

#include "Common.h"
#include <iostream>
#include <string>

namespace Console
{
    inline uint32 GetUInt32()
    {
        uint32 value = 0;
        
        #ifdef _WIN32
        scanf_s("%u", &value);
        #else
        scanf("%u", &value);
        #endif

        return value;
    }

    inline char GetChar()
    {
        fseek(stdin, 0, SEEK_END);
        char const chr = getchar();
        fseek(stdin, 0, SEEK_END);
        return chr;
    }

    inline std::string GetString(std::string defaultText)
    {
        std::string text;
        fseek(stdin, 0, SEEK_END);
        getline(std::cin, text);
        fseek(stdin, 0, SEEK_END);
        if (text.empty())
            return defaultText;
        return text;
    }
}

#endif
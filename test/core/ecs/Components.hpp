#pragma once

#include <string>

namespace test
{
    struct BoolComponent
    {
        bool value = false;
    };

    struct NumberComponent
    {
        int value = 0;
    };

    struct TextComponent
    {
        std::string value;
    };
}
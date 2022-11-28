#pragma once

#include <string>
#include <vector>

namespace ecs
{
    struct BoolComponent
    {
        bool value = false;

        //BoolComponent() = default;
        //BoolComponent(bool value) : value(value) {}
    };

    struct NumberComponent
    {
        int value = 0;

        //NumberComponent() = default;
        //NumberComponent(int value) : value(value) {}
    };

    struct TextComponent
    {
        std::string value;

        //TextComponent() = default;
        //TextComponent(std::string value) : value(value) {}
    };
}
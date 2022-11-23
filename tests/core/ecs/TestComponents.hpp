#pragma once

#include <core/ecs/IComponent.hpp>

#include <string>
#include <vector>

namespace ecs
{
    struct BoolComponent : public IComponent
    {
        bool value = false;

        BoolComponent() = default;
        BoolComponent(bool value) : value(value) {}
    };

    struct NumberComponent : public IComponent
    {
        int value = 0;

        NumberComponent() = default;
        NumberComponent(int value) : value(value) {}
    };

    struct TextComponent : public IComponent
    {
        std::string value;

        TextComponent() = default;
        TextComponent(std::string value) : value(value) {}
    };
}
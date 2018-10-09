#pragma once

#include <component/IComponent.hpp>

#include <string>
#include <vector>

namespace eng
{
    struct BoolComponent : public IComponent
    {
        bool boolean = false;

        BoolComponent(bool value) : boolean(value) {}
    };

    struct NumberComponent : public IComponent
    {
        int number = 0;

        NumberComponent(int value) : number(value) {}
    };

    struct TextComponent : public IComponent
    {
        std::string text;

        TextComponent(std::string value) : text(value) {}
    };

    struct ListComponent : public IComponent
    {
        std::vector<std::string> list;
    };

    struct FieldComponent : public IComponent
    {
        bool boolean = false;
        int number = 10;
        double decimal = 5.15f;
        std::string text = "text";
        std::vector<std::string> list = { "item1", "item2", "item3" };
    };
}
#pragma once

#include <system/IComponent.hpp>
#include <core/Defines.hpp>
#include <ui/InputBindings.hpp>

namespace eng
{
    class InputListener : public IComponent
    {
    public:
        std::shared_ptr<const InputActions*> input;
    };
}
#pragma once

#include <core/Core.hpp>
#include <core/ecs/IComponent.hpp>
#include <ui/InputBindings.hpp>

namespace eng
{
    class InputListener : public IComponent
    {
    public:
        std::shared_ptr<const InputActions*> input;
    };
}
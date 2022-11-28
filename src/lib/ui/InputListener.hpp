#pragma once

#include <core/Core.hpp>
#include <ui/InputBindings.hpp>

namespace ecs
{
    struct InputListener
    {
        std::shared_ptr<const InputActions*> input;
    };
}
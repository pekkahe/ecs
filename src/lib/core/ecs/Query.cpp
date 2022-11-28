#include <core/ecs/Query.hpp>

#include <core/Core.hpp>

using namespace ecs;

ecs::Query<> ecs::query(const Database& database)
{
    return Query<>(database);
}

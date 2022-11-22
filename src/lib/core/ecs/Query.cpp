#include <Precompiled.hpp>
#include <core/ecs/Query.hpp>

using namespace ecs;

ecs::Query<> ecs::query(const Database& database)
{
    return Query<>(database);
}

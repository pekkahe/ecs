#include <Precompiled.hpp>
#include <core/ecs/Query.hpp>

using namespace eng;

eng::Query<> eng::query(const Database& database)
{
    return Query<>(database);
}

#include <Precompiled.hpp>
#include <component/Query.hpp>

using namespace eng;

eng::Query<> eng::query(const Database& database)
{
    return Query<>(database);
}

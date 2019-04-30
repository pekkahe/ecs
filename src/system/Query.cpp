#include <Precompiled.hpp>
#include <system/Query.hpp>

using namespace eng;

eng::Query<> eng::query(const Database& database)
{
    return Query<>(database);
}

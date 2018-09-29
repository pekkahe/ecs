#include <Precompiled.hpp>
#include <component/Query.hpp>

using namespace eng;

Query<> query(const Database& database)
{
    return Query<>(database);
}

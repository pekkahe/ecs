#include <Precompiled.hpp>
#include <component/Query.hpp>

using namespace eng;

Query<> query(Database& database)
{
	return Query<>(database);
}

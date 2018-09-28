#include <Precompiled.hpp>
#include <component/Database.hpp>

using namespace eng;

EntityId Database::createEntity()
{
	auto id = m_nextEntityId;
	m_nextEntityId++;
	return id;
}

#include <Precompiled.hpp>
#include <scene/TransformSystem.hpp>

using namespace eng;

TransformSystem::TransformSystem(Database& db) :
    System::System(db),
    m_transforms(createTable<Transform>(db))
{
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::update()
{
}

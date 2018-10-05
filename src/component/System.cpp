#include <Precompiled.hpp>
#include <component/System.hpp>

#include <scene/Scene.hpp>

using namespace eng;

void System::onRegistered(const Scene& scene)
{
    m_database = &scene.database();
}

void System::commitUpdated(Database& database)
{
    auto& updated = database.table<Updated>();

    m_updated.forEach([&](EntityId id, Updated&) 
    {
        updated.assign(id, Updated());
    });
    m_updated.clear();
}

void System::commitDeleted(Database& database)
{
    auto& deleted = database.table<Deleted>();

    m_deleted.forEach([&](EntityId id, Deleted&)
    {
        deleted.assign(id, Deleted());
    });
    m_deleted.clear();
}

void System::markUpdated(EntityId id)
{
    m_updated.assign(id, Updated());
}

void System::markDeleted(EntityId id)
{
    m_deleted.assign(id, Deleted());
}

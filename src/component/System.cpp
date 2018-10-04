#include <Precompiled.hpp>
#include <component/System.hpp>

#include <scene/Scene.hpp>

using namespace eng;

void System::onRegistered(const Scene& scene)
{
    m_database = &scene.database();
}
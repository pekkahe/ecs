#include <Precompiled.hpp>
#include <scene/Scene.hpp>

#include <component/Table.hpp>
#include <component/Query.hpp>

#include <scene/Transform.hpp>
#include <graphics/Mesh.hpp>
#include <ui/Gizmo.hpp>

using namespace eng;

Scene::Scene(std::shared_ptr<Window> window) :
    m_transformSystem(m_database),
    m_renderSystem(m_database),
    m_cameraSystem(m_database),
    m_cameraControlSystem(std::make_shared<CameraControlSystem>(m_database)),
    m_gizmoSystem(std::make_shared<GizmoSystem>(m_database))
{
    registerSystem(*m_cameraControlSystem);
    registerSystem(*m_gizmoSystem);
    registerSystem(m_transformSystem);
    registerSystem(m_cameraSystem);
    registerSystem(m_renderSystem);

    window->addEventListener(m_cameraControlSystem);
    window->addEventListener(m_gizmoSystem);

    window->onWindowResize([&](int2 size) 
    {
        m_cameraSystem.setAspectRatio(static_cast<float>(size.x) / size.y);
    });
}

Scene::~Scene()
{
}

void Scene::registerSystem(ISystem& system)
{
    m_systems.emplace_back(&system);

    system.onRegistered(*this);
}

void Scene::update()
{
    // todo: unit test

    for (auto system : m_systems)
    {
        system->commitUpdated(m_database);
    }

    // todo: multithreading; within system update or between updates?
    // causality scheduling (const, non-const) for individual queries?
    for (auto system : m_systems)
    {
        system->update(*this);
    }

    for (auto system : m_systems)
    {
        system->commitDeleted(m_database);
    }

    m_database.purgeDeleted();
    m_database.clearTags();
}

EntityId Scene::createEntity()
{
    auto id = m_database.createEntity();

    return id;
}

// Test scene setup code
void Scene::createTestEntities()
{
    Mesh mesh;
    mesh.vertices = std::vector<vec3>
    {
        vec3(0.5f,   0.5f, -0.5f),
        vec3(0.5f,  -0.5f, -0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(-0.5f,  0.5f, -0.5f),

        vec3(0.5f,   0.5f,  0.5f),
        vec3(0.5f,  -0.5f,  0.5f),
        vec3(-0.5f, -0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f)
    };
    mesh.indices = std::vector<unsigned>
    {
        0, 1, 3, // front
        1, 2, 3,

        4, 5, 7, // back
        5, 6, 7,

        4, 0, 7, // top
        0, 3, 7,

        5, 1, 6, // bottom
        1, 2, 6,

        3, 2, 7, // left
        2, 6, 7,

        4, 5, 0, // right
        5, 1, 0
    };

    auto meshId = createEntity();

    m_renderSystem.addMesh(meshId, std::move(mesh));
    m_transformSystem.addTransform(meshId, Transform(vec3(0.f, 0.f, -3.f)));
    m_gizmoSystem->addGizmo(meshId, Gizmo());

    m_database.table<Added>().assign(meshId, Added());
    m_database.table<Updated>().assign(meshId, Updated());

    auto cameraId = createEntity();

    m_cameraSystem.addCamera(cameraId, Camera());
    m_cameraControlSystem->addCameraControl(cameraId, CameraControl());
    m_transformSystem.addTransform(cameraId, Transform());

    m_database.table<Added>().assign(cameraId, Added());
    m_database.table<Updated>().assign(cameraId, Updated());
}
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
    registerSystem(m_transformSystem);
    registerSystem(m_renderSystem);
    registerSystem(m_cameraSystem);
    registerSystem(*m_cameraControlSystem);
    registerSystem(*m_gizmoSystem);

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
    // sync()

    for (auto system : m_systems)
    {
        system->update(*this);
    }

    // sync()
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
    m_transformSystem.addTransform(meshId, Transform());
    m_gizmoSystem->addGizmo(meshId, Gizmo());

    auto cameraId = createEntity();
    m_cameraSystem.addCamera(cameraId, Camera());
    m_transformSystem.addTransform(cameraId, Transform());
}